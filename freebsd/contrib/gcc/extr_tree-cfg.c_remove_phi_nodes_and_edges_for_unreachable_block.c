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
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  succs; } ;

/* Variables and functions */
 scalar_t__ EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_SUCC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 scalar_t__ phi_nodes (TYPE_1__*) ; 
 int /*<<< orphan*/  remove_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_phi_node (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_phi_nodes_and_edges_for_unreachable_block (basic_block bb)
{
  tree phi;

  /* Since this block is no longer reachable, we can just delete all
     of its PHI nodes.  */
  phi = phi_nodes (bb);
  while (phi)
    {
      tree next = PHI_CHAIN (phi);
      remove_phi_node (phi, NULL_TREE);
      phi = next;
    }

  /* Remove edges to BB's successors.  */
  while (EDGE_COUNT (bb->succs) > 0)
    remove_edge (EDGE_SUCC (bb, 0));
}