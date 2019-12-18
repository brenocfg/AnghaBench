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
typedef  int /*<<< orphan*/  ssa_prop_visit_stmt_fn ;
typedef  int /*<<< orphan*/  ssa_prop_visit_phi_fn ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_blocks_empty_p () ; 
 int /*<<< orphan*/  cfg_blocks_get () ; 
 int /*<<< orphan*/  interesting_ssa_edges ; 
 int /*<<< orphan*/  process_ssa_edge_worklist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simulate_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssa_prop_fini () ; 
 int /*<<< orphan*/  ssa_prop_init () ; 
 int /*<<< orphan*/  ssa_prop_visit_phi ; 
 int /*<<< orphan*/  ssa_prop_visit_stmt ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  varying_ssa_edges ; 

void
ssa_propagate (ssa_prop_visit_stmt_fn visit_stmt,
	       ssa_prop_visit_phi_fn visit_phi)
{
  ssa_prop_visit_stmt = visit_stmt;
  ssa_prop_visit_phi = visit_phi;

  ssa_prop_init ();

  /* Iterate until the worklists are empty.  */
  while (!cfg_blocks_empty_p () 
	 || VEC_length (tree, interesting_ssa_edges) > 0
	 || VEC_length (tree, varying_ssa_edges) > 0)
    {
      if (!cfg_blocks_empty_p ())
	{
	  /* Pull the next block to simulate off the worklist.  */
	  basic_block dest_block = cfg_blocks_get ();
	  simulate_block (dest_block);
	}

      /* In order to move things to varying as quickly as
	 possible,process the VARYING_SSA_EDGES worklist first.  */
      process_ssa_edge_worklist (&varying_ssa_edges);

      /* Now process the INTERESTING_SSA_EDGES worklist.  */
      process_ssa_edge_worklist (&interesting_ssa_edges);
    }

  ssa_prop_fini ();
}