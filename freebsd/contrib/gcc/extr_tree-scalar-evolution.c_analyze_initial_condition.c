#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  src; } ;
struct TYPE_3__ {struct loop* loop_father; } ;

/* Variables and functions */
 scalar_t__ PHI_ARG_DEF (scalar_t__,int) ; 
 TYPE_2__* PHI_ARG_EDGE (scalar_t__,int) ; 
 int PHI_NUM_ARGS (scalar_t__) ; 
 scalar_t__ SSA_NAME ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 TYPE_1__* bb_for_stmt (scalar_t__) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ chrec_merge (scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_not_analyzed_yet ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ flow_bb_inside_loop_p (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree 
analyze_initial_condition (tree loop_phi_node)
{
  int i;
  tree init_cond = chrec_not_analyzed_yet;
  struct loop *loop = bb_for_stmt (loop_phi_node)->loop_father;
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "(analyze_initial_condition \n");
      fprintf (dump_file, "  (loop_phi_node = \n");
      print_generic_expr (dump_file, loop_phi_node, 0);
      fprintf (dump_file, ")\n");
    }
  
  for (i = 0; i < PHI_NUM_ARGS (loop_phi_node); i++)
    {
      tree branch = PHI_ARG_DEF (loop_phi_node, i);
      basic_block bb = PHI_ARG_EDGE (loop_phi_node, i)->src;
      
      /* When the branch is oriented to the loop's body, it does
     	 not contribute to the initial condition.  */
      if (flow_bb_inside_loop_p (loop, bb))
       	continue;

      if (init_cond == chrec_not_analyzed_yet)
	{
	  init_cond = branch;
	  continue;
	}

      if (TREE_CODE (branch) == SSA_NAME)
	{
	  init_cond = chrec_dont_know;
      	  break;
	}

      init_cond = chrec_merge (init_cond, branch);
    }

  /* Ooops -- a loop without an entry???  */
  if (init_cond == chrec_not_analyzed_yet)
    init_cond = chrec_dont_know;

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  (init_cond = ");
      print_generic_expr (dump_file, init_cond, 0);
      fprintf (dump_file, "))\n");
    }
  
  return init_cond;
}