#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ t_bool ;
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHI_ARG_DEF (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* PHI_ARG_EDGE (int /*<<< orphan*/ ,int) ; 
 int PHI_NUM_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_not_analyzed_yet ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  flow_bb_inside_loop_p (struct loop*,int /*<<< orphan*/ ) ; 
 scalar_t__ follow_ssa_edge (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 struct loop* loop_containing_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ t_false ; 
 scalar_t__ t_true ; 

__attribute__((used)) static tree
analyze_evolution_in_loop (tree loop_phi_node, 
			   tree init_cond)
{
  int i;
  tree evolution_function = chrec_not_analyzed_yet;
  struct loop *loop = loop_containing_stmt (loop_phi_node);
  basic_block bb;
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "(analyze_evolution_in_loop \n");
      fprintf (dump_file, "  (loop_phi_node = ");
      print_generic_expr (dump_file, loop_phi_node, 0);
      fprintf (dump_file, ")\n");
    }
  
  for (i = 0; i < PHI_NUM_ARGS (loop_phi_node); i++)
    {
      tree arg = PHI_ARG_DEF (loop_phi_node, i);
      tree ssa_chain, ev_fn;
      t_bool res;

      /* Select the edges that enter the loop body.  */
      bb = PHI_ARG_EDGE (loop_phi_node, i)->src;
      if (!flow_bb_inside_loop_p (loop, bb))
	continue;
      
      if (TREE_CODE (arg) == SSA_NAME)
	{
	  ssa_chain = SSA_NAME_DEF_STMT (arg);

	  /* Pass in the initial condition to the follow edge function.  */
	  ev_fn = init_cond;
	  res = follow_ssa_edge (loop, ssa_chain, loop_phi_node, &ev_fn, 0);
	}
      else
	res = t_false;
	      
      /* When it is impossible to go back on the same
	 loop_phi_node by following the ssa edges, the
	 evolution is represented by a peeled chrec, i.e. the
	 first iteration, EV_FN has the value INIT_COND, then
	 all the other iterations it has the value of ARG.  
	 For the moment, PEELED_CHREC nodes are not built.  */
      if (res != t_true)
	ev_fn = chrec_dont_know;
      
      /* When there are multiple back edges of the loop (which in fact never
	 happens currently, but nevertheless), merge their evolutions.  */
      evolution_function = chrec_merge (evolution_function, ev_fn);
    }
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  (evolution_function = ");
      print_generic_expr (dump_file, evolution_function, 0);
      fprintf (dump_file, "))\n");
    }
  
  return evolution_function;
}