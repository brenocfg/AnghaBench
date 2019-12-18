#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct deps {int dummy; } ;
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* ddg_ptr ;
typedef  TYPE_2__* ddg_node_ptr ;
struct TYPE_13__ {int /*<<< orphan*/  successors; int /*<<< orphan*/  insn; } ;
struct TYPE_12__ {int num_nodes; TYPE_2__* nodes; int /*<<< orphan*/  bb; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_DEPEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LOG_LINKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_BIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  add_forw_dep (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  add_inter_loop_mem_dep (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  create_ddg_dependence (TYPE_1__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_deps_global () ; 
 int /*<<< orphan*/  free_deps (struct deps*) ; 
 int /*<<< orphan*/  get_ebb_head_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 TYPE_2__* get_node_of_insn (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  init_deps (struct deps*) ; 
 int /*<<< orphan*/  init_deps_global () ; 
 scalar_t__ mem_access_insn_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_analyze (struct deps*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
build_intra_loop_deps (ddg_ptr g)
{
  int i;
  /* Hold the dependency analysis state during dependency calculations.  */
  struct deps tmp_deps;
  rtx head, tail, link;

  /* Build the dependence information, using the sched_analyze function.  */
  init_deps_global ();
  init_deps (&tmp_deps);

  /* Do the intra-block data dependence analysis for the given block.  */
  get_ebb_head_tail (g->bb, g->bb, &head, &tail);
  sched_analyze (&tmp_deps, head, tail);

  /* Build intra-loop data dependencies using the scheduler dependency
     analysis.  */
  for (i = 0; i < g->num_nodes; i++)
    {
      ddg_node_ptr dest_node = &g->nodes[i];

      if (! INSN_P (dest_node->insn))
	continue;

      for (link = LOG_LINKS (dest_node->insn); link; link = XEXP (link, 1))
	{
	  ddg_node_ptr src_node = get_node_of_insn (g, XEXP (link, 0));

	  if (!src_node)
	    continue;

      	  add_forw_dep (dest_node->insn, link);
	  create_ddg_dependence (g, src_node, dest_node,
				 INSN_DEPEND (src_node->insn));
	}

      /* If this insn modifies memory, add an edge to all insns that access
	 memory.  */
      if (mem_access_insn_p (dest_node->insn))
	{
	  int j;

	  for (j = 0; j <= i; j++)
	    {
	      ddg_node_ptr j_node = &g->nodes[j];
	      if (mem_access_insn_p (j_node->insn))
 		/* Don't bother calculating inter-loop dep if an intra-loop dep
		   already exists.  */
	      	  if (! TEST_BIT (dest_node->successors, j))
		    add_inter_loop_mem_dep (g, dest_node, j_node);
            }
        }
    }

  /* Free the INSN_LISTs.  */
  finish_deps_global ();
  free_deps (&tmp_deps);
}