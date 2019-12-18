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
struct loop {int /*<<< orphan*/  num; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  BINARY_CLASS_P (scalar_t__) ; 
 scalar_t__ INTEGER_CST ; 
#define  MINUS_EXPR 130 
 int MIN_EXPR ; 
#define  MULT_EXPR 129 
 scalar_t__ NULL_TREE ; 
#define  PLUS_EXPR 128 
 scalar_t__ SSA_VAR_P (scalar_t__) ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ analyze_scalar_evolution (struct loop*,scalar_t__) ; 
 scalar_t__ chrec_dont_know ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 scalar_t__ evolution_part_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr_invariant_in_loop_p (struct loop*,scalar_t__) ; 
 scalar_t__ fold_build2 (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  highest_pow2_factor (scalar_t__) ; 
 scalar_t__ initial_condition_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ size_binop (int const,scalar_t__,scalar_t__) ; 
 scalar_t__ ssize_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssizetype ; 
 scalar_t__ strip_conversion (scalar_t__) ; 

__attribute__((used)) static bool
analyze_offset_expr (tree expr, 
		     struct loop *loop, 
		     tree *initial_offset,
		     tree *misalign,
		     tree *aligned_to,
		     tree *step)
{
  tree oprnd0;
  tree oprnd1;
  tree left_offset = ssize_int (0);
  tree right_offset = ssize_int (0);
  tree left_misalign = ssize_int (0);
  tree right_misalign = ssize_int (0);
  tree left_step = ssize_int (0);
  tree right_step = ssize_int (0);
  enum tree_code code;
  tree init, evolution;
  tree left_aligned_to = NULL_TREE, right_aligned_to = NULL_TREE;

  *step = NULL_TREE;
  *misalign = NULL_TREE;
  *aligned_to = NULL_TREE;  
  *initial_offset = NULL_TREE;

  /* Strip conversions that don't narrow the mode.  */
  expr = strip_conversion (expr);
  if (!expr)
    return false;

  /* Stop conditions:
     1. Constant.  */
  if (TREE_CODE (expr) == INTEGER_CST)
    {
      *initial_offset = fold_convert (ssizetype, expr);
      *misalign = fold_convert (ssizetype, expr);      
      *step = ssize_int (0);
      return true;
    }

  /* 2. Variable. Try to substitute with initial_condition of the corresponding
     access_fn in the current loop.  */
  if (SSA_VAR_P (expr))
    {
      tree access_fn = analyze_scalar_evolution (loop, expr);

      if (access_fn == chrec_dont_know)
	/* No access_fn.  */
	return false;

      init = initial_condition_in_loop_num (access_fn, loop->num);
      if (!expr_invariant_in_loop_p (loop, init))
	/* Not enough information: may be not loop invariant.  
	   E.g., for a[b[i]], we get a[D], where D=b[i]. EXPR is D, its 
	   initial_condition is D, but it depends on i - loop's induction
	   variable.  */	  
	return false;

      evolution = evolution_part_in_loop_num (access_fn, loop->num);
      if (evolution && TREE_CODE (evolution) != INTEGER_CST)
	/* Evolution is not constant.  */
	return false;

      if (TREE_CODE (init) == INTEGER_CST)
	*misalign = fold_convert (ssizetype, init);
      else
	/* Not constant, misalignment cannot be calculated.  */
	*misalign = NULL_TREE;

      *initial_offset = fold_convert (ssizetype, init); 

      *step = evolution ? fold_convert (ssizetype, evolution) : ssize_int (0);
      return true;      
    }

  /* Recursive computation.  */
  if (!BINARY_CLASS_P (expr))
    {
      /* We expect to get binary expressions (PLUS/MINUS and MULT).  */
      if (dump_file && (dump_flags & TDF_DETAILS))
        {
	  fprintf (dump_file, "\nNot binary expression ");
          print_generic_expr (dump_file, expr, TDF_SLIM);
	  fprintf (dump_file, "\n");
	}
      return false;
    }
  oprnd0 = TREE_OPERAND (expr, 0);
  oprnd1 = TREE_OPERAND (expr, 1);

  if (!analyze_offset_expr (oprnd0, loop, &left_offset, &left_misalign, 
			    &left_aligned_to, &left_step)
      || !analyze_offset_expr (oprnd1, loop, &right_offset, &right_misalign, 
			       &right_aligned_to, &right_step))
    return false;

  /* The type of the operation: plus, minus or mult.  */
  code = TREE_CODE (expr);
  switch (code)
    {
    case MULT_EXPR:
      if (TREE_CODE (right_offset) != INTEGER_CST)
	/* RIGHT_OFFSET can be not constant. For example, for arrays of variable 
	   sized types. 
	   FORNOW: We don't support such cases.  */
	return false;

      /* Strip conversions that don't narrow the mode.  */
      left_offset = strip_conversion (left_offset);      
      if (!left_offset)
	return false;      
      /* Misalignment computation.  */
      if (SSA_VAR_P (left_offset))
	{
	  /* If the left side contains variables that can't be substituted with 
	     constants, the misalignment is unknown. However, if the right side 
	     is a multiple of some alignment, we know that the expression is
	     aligned to it. Therefore, we record such maximum possible value.
	   */
	  *misalign = NULL_TREE;
	  *aligned_to = ssize_int (highest_pow2_factor (right_offset));
	}
      else 
	{
	  /* The left operand was successfully substituted with constant.  */	  
	  if (left_misalign)
	    {
	      /* In case of EXPR '(i * C1 + j) * C2', LEFT_MISALIGN is 
		 NULL_TREE.  */
	      *misalign  = size_binop (code, left_misalign, right_misalign);
	      if (left_aligned_to && right_aligned_to)
		*aligned_to = size_binop (MIN_EXPR, left_aligned_to, 
					  right_aligned_to);
	      else 
		*aligned_to = left_aligned_to ? 
		  left_aligned_to : right_aligned_to;
	    }
	  else
	    *misalign = NULL_TREE; 
	}

      /* Step calculation.  */
      /* Multiply the step by the right operand.  */
      *step  = size_binop (MULT_EXPR, left_step, right_offset);
      break;
   
    case PLUS_EXPR:
    case MINUS_EXPR:
      /* Combine the recursive calculations for step and misalignment.  */
      *step = size_binop (code, left_step, right_step);

      /* Unknown alignment.  */
      if ((!left_misalign && !left_aligned_to)
	  || (!right_misalign && !right_aligned_to))
	{
	  *misalign = NULL_TREE;
	  *aligned_to = NULL_TREE;
	  break;
	}

      if (left_misalign && right_misalign)
	*misalign = size_binop (code, left_misalign, right_misalign);
      else
	*misalign = left_misalign ? left_misalign : right_misalign;

      if (left_aligned_to && right_aligned_to)
	*aligned_to = size_binop (MIN_EXPR, left_aligned_to, right_aligned_to);
      else 
	*aligned_to = left_aligned_to ? left_aligned_to : right_aligned_to;

      break;

    default:
      gcc_unreachable ();
    }

  /* Compute offset.  */
  *initial_offset = fold_convert (ssizetype, 
				  fold_build2 (code, TREE_TYPE (left_offset), 
					       left_offset, 
					       right_offset));
  return true;
}