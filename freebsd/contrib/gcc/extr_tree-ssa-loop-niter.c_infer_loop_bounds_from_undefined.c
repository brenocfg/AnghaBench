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
typedef  int /*<<< orphan*/  tree ;
struct loop {unsigned int num_nodes; int /*<<< orphan*/  num; int /*<<< orphan*/  latch; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int ARRAY_REF ; 
#define  CALL_EXPR 129 
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  CEIL_DIV_EXPR ; 
 int INTEGER_CST ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
#define  MODIFY_EXPR 128 
 int /*<<< orphan*/  NULL_TREE ; 
 int SSA_NAME ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_WRAPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analyze_scalar_evolution (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_ref_contains_indirect_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boolean_true_node ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_contains_undetermined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_estimated_nb_iterations (struct loop*) ; 
 int /*<<< orphan*/  dominated_by_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  estimate_iters_using_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evolution_part_in_loop_num (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_wrapv ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_loop_body (struct loop*) ; 
 int /*<<< orphan*/  initial_condition_in_loop_num (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_parameters (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_nonzerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  record_estimate (struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_int_cst_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsigned_type_for (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
infer_loop_bounds_from_undefined (struct loop *loop)
{
  unsigned i;
  basic_block bb, *bbs;
  block_stmt_iterator bsi;
  
  bbs = get_loop_body (loop);

  for (i = 0; i < loop->num_nodes; i++)
    {
      bb = bbs[i];

      /* If BB is not executed in each iteration of the loop, we cannot
	 use the operations in it to infer reliable upper bound on the
	 # of iterations of the loop.  */
      if (!dominated_by_p (CDI_DOMINATORS, loop->latch, bb))
	continue;

      for (bsi = bsi_start (bb); !bsi_end_p (bsi); bsi_next (&bsi))
        {
	  tree stmt = bsi_stmt (bsi);

	  switch (TREE_CODE (stmt))
	    {
	    case MODIFY_EXPR:
	      {
		tree op0 = TREE_OPERAND (stmt, 0);
		tree op1 = TREE_OPERAND (stmt, 1);

		/* For each array access, analyze its access function
		   and record a bound on the loop iteration domain.  */
		if (TREE_CODE (op1) == ARRAY_REF 
		    && !array_ref_contains_indirect_ref (op1))
		  estimate_iters_using_array (stmt, op1);

		if (TREE_CODE (op0) == ARRAY_REF 
		    && !array_ref_contains_indirect_ref (op0))
		  estimate_iters_using_array (stmt, op0);

		/* For each signed type variable in LOOP, analyze its
		   scalar evolution and record a bound of the loop
		   based on the type's ranges.  */
		else if (!flag_wrapv && TREE_CODE (op0) == SSA_NAME)
		  {
		    tree init, step, diff, estimation;
		    tree scev = instantiate_parameters 
		      (loop, analyze_scalar_evolution (loop, op0));
		    tree type = chrec_type (scev);

		    if (chrec_contains_undetermined (scev)
			|| TYPE_OVERFLOW_WRAPS (type))
		      break;

		    init = initial_condition_in_loop_num (scev, loop->num);
		    step = evolution_part_in_loop_num (scev, loop->num);

		    if (init == NULL_TREE
			|| step == NULL_TREE
			|| TREE_CODE (init) != INTEGER_CST
			|| TREE_CODE (step) != INTEGER_CST
			|| TYPE_MIN_VALUE (type) == NULL_TREE
			|| TYPE_MAX_VALUE (type) == NULL_TREE)
		      break;

		    if (integer_nonzerop (step))
		      {
			tree utype;

			if (tree_int_cst_lt (step, integer_zero_node))
			  diff = fold_build2 (MINUS_EXPR, type, init,
					      TYPE_MIN_VALUE (type));
			else
			  diff = fold_build2 (MINUS_EXPR, type,
					      TYPE_MAX_VALUE (type), init);

			utype = unsigned_type_for (type);
			estimation = fold_build2 (CEIL_DIV_EXPR, type, diff,
						  step);
			record_estimate (loop,
					 fold_convert (utype, estimation),
					 boolean_true_node, stmt);
		      }
		  }

		break;
	      }

	    case CALL_EXPR:
	      {
		tree args;

		for (args = TREE_OPERAND (stmt, 1); args;
		     args = TREE_CHAIN (args))
		  if (TREE_CODE (TREE_VALUE (args)) == ARRAY_REF
		      && !array_ref_contains_indirect_ref (TREE_VALUE (args)))
		    estimate_iters_using_array (stmt, TREE_VALUE (args));

		break;
	      }

	    default:
	      break;
	    }
	}
    }

  compute_estimated_nb_iterations (loop);
  free (bbs);
}