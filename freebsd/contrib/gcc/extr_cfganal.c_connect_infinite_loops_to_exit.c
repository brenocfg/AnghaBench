#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct depth_first_search_dsS {int dummy; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  EDGE_FAKE ; 
 int /*<<< orphan*/  EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/  flow_dfs_compute_reverse_add_bb (struct depth_first_search_dsS*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_dfs_compute_reverse_execute (struct depth_first_search_dsS*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_dfs_compute_reverse_finish (struct depth_first_search_dsS*) ; 
 int /*<<< orphan*/  flow_dfs_compute_reverse_init (struct depth_first_search_dsS*) ; 
 int /*<<< orphan*/  make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
connect_infinite_loops_to_exit (void)
{
  basic_block unvisited_block = EXIT_BLOCK_PTR;
  struct depth_first_search_dsS dfs_ds;

  /* Perform depth-first search in the reverse graph to find nodes
     reachable from the exit block.  */
  flow_dfs_compute_reverse_init (&dfs_ds);
  flow_dfs_compute_reverse_add_bb (&dfs_ds, EXIT_BLOCK_PTR);

  /* Repeatedly add fake edges, updating the unreachable nodes.  */
  while (1)
    {
      unvisited_block = flow_dfs_compute_reverse_execute (&dfs_ds,
							  unvisited_block);
      if (!unvisited_block)
	break;

      make_edge (unvisited_block, EXIT_BLOCK_PTR, EDGE_FAKE);
      flow_dfs_compute_reverse_add_bb (&dfs_ds, unvisited_block);
    }

  flow_dfs_compute_reverse_finish (&dfs_ds);
  return;
}