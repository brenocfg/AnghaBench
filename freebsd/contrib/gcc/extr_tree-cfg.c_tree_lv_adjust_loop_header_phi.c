#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  dest_idx; } ;

/* Variables and functions */
 scalar_t__ PHI_ARG_DEF (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  add_phi_arg (scalar_t__,scalar_t__,TYPE_1__*) ; 
 TYPE_1__* find_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tree_lv_adjust_loop_header_phi (basic_block first, basic_block second,
				basic_block new_head, edge e)
{
  tree phi1, phi2;
  edge e2 = find_edge (new_head, second);

  /* Because NEW_HEAD has been created by splitting SECOND's incoming
     edge, we should always have an edge from NEW_HEAD to SECOND.  */
  gcc_assert (e2 != NULL);

  /* Browse all 'second' basic block phi nodes and add phi args to
     edge 'e' for 'first' head. PHI args are always in correct order.  */

  for (phi2 = phi_nodes (second), phi1 = phi_nodes (first);
       phi2 && phi1;
       phi2 = PHI_CHAIN (phi2),  phi1 = PHI_CHAIN (phi1))
    {
      tree def = PHI_ARG_DEF (phi2, e2->dest_idx);
      add_phi_arg (phi1, def, e);
    }
}