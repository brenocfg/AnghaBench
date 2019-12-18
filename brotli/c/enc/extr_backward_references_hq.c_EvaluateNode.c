#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float cost; int /*<<< orphan*/  shortcut; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_2__ ZopfliNode ;
typedef  int /*<<< orphan*/  ZopfliCostModel ;
struct TYPE_10__ {size_t pos; float cost; float costdiff; int /*<<< orphan*/  distance_cache; } ;
typedef  int /*<<< orphan*/  StartPosQueue ;
typedef  TYPE_3__ PosData ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeDistanceCache (size_t const,int const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComputeDistanceShortcut (size_t const,size_t const,size_t const,size_t const,TYPE_2__*) ; 
 int /*<<< orphan*/  StartPosQueuePush (int /*<<< orphan*/ *,TYPE_3__*) ; 
 float ZopfliCostModelGetLiteralCosts (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static void EvaluateNode(
    const size_t block_start, const size_t pos, const size_t max_backward_limit,
    const size_t gap, const int* starting_dist_cache,
    const ZopfliCostModel* model, StartPosQueue* queue, ZopfliNode* nodes) {
  /* Save cost, because ComputeDistanceCache invalidates it. */
  float node_cost = nodes[pos].u.cost;
  nodes[pos].u.shortcut = ComputeDistanceShortcut(
      block_start, pos, max_backward_limit, gap, nodes);
  if (node_cost <= ZopfliCostModelGetLiteralCosts(model, 0, pos)) {
    PosData posdata;
    posdata.pos = pos;
    posdata.cost = node_cost;
    posdata.costdiff = node_cost -
        ZopfliCostModelGetLiteralCosts(model, 0, pos);
    ComputeDistanceCache(
        pos, starting_dist_cache, nodes, posdata.distance_cache);
    StartPosQueuePush(queue, &posdata);
  }
}