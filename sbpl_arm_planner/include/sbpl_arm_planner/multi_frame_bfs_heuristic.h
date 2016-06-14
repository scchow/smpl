////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016, Andrew Dornbush
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     1. Redistributions of source code must retain the above copyright notice
//        this list of conditions and the following disclaimer.
//     2. Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//     3. Neither the name of the copyright holder nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////

/// \author Andrew Dornbush

#ifndef sbpl_manip_multi_frame_bfs_heuristic_h
#define sbpl_manip_multi_frame_bfs_heuristic_h

// standard includes
#include <memory>

// system includes
#include <visualization_msgs/MarkerArray.h>

// project includes
#include <sbpl_arm_planner/manip_heuristic.h>

namespace sbpl {
namespace manip {

class BFS_3D;

class MultiFrameBfsHeuristic : public ManipHeuristic
{
public:

    MultiFrameBfsHeuristic(
        ManipLattice* env,
        const OccupancyGrid* grid,
        const PlanningParams* params);

    virtual ~MultiFrameBfsHeuristic();

    bool setGoal(const GoalConstraint& goal);

    visualization_msgs::MarkerArray getWallsVisualization() const;
    visualization_msgs::MarkerArray getValuesVisualization() const;

    /// \sa ManipHeuristic::getMetricStartDistance
    double getMetricStartDistance(double x, double y, double z);

    /// \brief Return the metric distance of the planning link.
    double getMetricGoalDistance(double x, double y, double z);

    int GetGoalHeuristic(int state_id);
    int GetStartHeuristic(int state_id);
    int GetFromToHeuristic(int from_id, int to_id);

private:

    std::unique_ptr<BFS_3D> m_bfs;
    std::unique_ptr<BFS_3D> m_ee_bfs;

    int getGoalHeuristic(int state_id, bool use_ee) const;

    void syncGridAndBfs();
    int getBfsCostToGoal(const BFS_3D& bfs, int x, int y, int z) const;

    inline
    int combine_costs(int c1, int c2) const;
};

} // namespace manip
} // namespace sbpl

#endif
