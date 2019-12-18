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
typedef  scalar_t__ tree ;
struct ptr_info_def {int dummy; } ;
struct loop {int /*<<< orphan*/  num; } ;
struct data_reference {int dummy; } ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POINTER_REF_TYPE ; 
 scalar_t__ SSA_NAME ; 
 struct ptr_info_def* SSA_NAME_PTR_INFO (scalar_t__) ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ analyze_scalar_evolution (struct loop*,scalar_t__) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ evolution_part_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr_invariant_in_loop_p (struct loop*,scalar_t__) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 struct data_reference* init_data_ref (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,struct ptr_info_def*,int /*<<< orphan*/ ) ; 
 scalar_t__ initial_condition_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 struct loop* loop_containing_stmt (scalar_t__) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ssize_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssizetype ; 

__attribute__((used)) static struct data_reference *
analyze_indirect_ref (tree stmt, tree ref, bool is_read)
{
  struct loop *loop = loop_containing_stmt (stmt);
  tree ptr_ref = TREE_OPERAND (ref, 0);
  tree access_fn = analyze_scalar_evolution (loop, ptr_ref);
  tree init = initial_condition_in_loop_num (access_fn, loop->num);
  tree base_address = NULL_TREE, evolution, step = NULL_TREE;
  struct ptr_info_def *ptr_info = NULL;

  if (TREE_CODE (ptr_ref) == SSA_NAME)
    ptr_info = SSA_NAME_PTR_INFO (ptr_ref);

  STRIP_NOPS (init);
  if (access_fn == chrec_dont_know || !init || init == chrec_dont_know)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "\nBad access function of ptr: ");
	  print_generic_expr (dump_file, ref, TDF_SLIM);
	  fprintf (dump_file, "\n");
	}
      return NULL;
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "\nAccess function of ptr: ");
      print_generic_expr (dump_file, access_fn, TDF_SLIM);
      fprintf (dump_file, "\n");
    }

  if (!expr_invariant_in_loop_p (loop, init))
    {
    if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "\ninitial condition is not loop invariant.\n");	
    }
  else
    {
      base_address = init;
      evolution = evolution_part_in_loop_num (access_fn, loop->num);
      if (evolution != chrec_dont_know)
	{       
	  if (!evolution)
	    step = ssize_int (0);
	  else  
	    {
	      if (TREE_CODE (evolution) == INTEGER_CST)
		step = fold_convert (ssizetype, evolution);
	      else
		if (dump_file && (dump_flags & TDF_DETAILS))
		  fprintf (dump_file, "\nnon constant step for ptr access.\n");	
	    }
	}
      else
	if (dump_file && (dump_flags & TDF_DETAILS))
	  fprintf (dump_file, "\nunknown evolution of ptr.\n");	
    }
  return init_data_ref (stmt, ref, NULL_TREE, access_fn, is_read, base_address, 
			NULL_TREE, step, NULL_TREE, NULL_TREE, 
			ptr_info, POINTER_REF_TYPE);
}