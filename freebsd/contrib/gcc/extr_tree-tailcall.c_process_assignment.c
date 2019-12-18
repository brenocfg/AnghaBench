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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 scalar_t__ FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
#define  MULT_EXPR 129 
#define  PLUS_EXPR 128 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  flag_unsafe_math_optimizations ; 
 int /*<<< orphan*/  independent_of_stmt_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcc_binary ; 

__attribute__((used)) static bool
process_assignment (tree ass, tree stmt, block_stmt_iterator call, tree *m,
		    tree *a, tree *ass_var)
{
  tree op0, op1, non_ass_var;
  tree dest = TREE_OPERAND (ass, 0);
  tree src = TREE_OPERAND (ass, 1);
  enum tree_code code = TREE_CODE (src);
  tree src_var = src;

  /* See if this is a simple copy operation of an SSA name to the function
     result.  In that case we may have a simple tail call.  Ignore type
     conversions that can never produce extra code between the function
     call and the function return.  */
  STRIP_NOPS (src_var);
  if (TREE_CODE (src_var) == SSA_NAME)
    {
      if (src_var != *ass_var)
	return false;

      *ass_var = dest;
      return true;
    }

  if (TREE_CODE_CLASS (code) != tcc_binary)
    return false;

  /* Accumulator optimizations will reverse the order of operations.
     We can only do that for floating-point types if we're assuming
     that addition and multiplication are associative.  */
  if (!flag_unsafe_math_optimizations)
    if (FLOAT_TYPE_P (TREE_TYPE (DECL_RESULT (current_function_decl))))
      return false;

  /* We only handle the code like

     x = call ();
     y = m * x;
     z = y + a;
     return z;

     TODO -- Extend it for cases where the linear transformation of the output
     is expressed in a more complicated way.  */

  op0 = TREE_OPERAND (src, 0);
  op1 = TREE_OPERAND (src, 1);

  if (op0 == *ass_var
      && (non_ass_var = independent_of_stmt_p (op1, stmt, call)))
    ;
  else if (op1 == *ass_var
	   && (non_ass_var = independent_of_stmt_p (op0, stmt, call)))
    ;
  else
    return false;

  switch (code)
    {
    case PLUS_EXPR:
      /* There should be no previous addition.  TODO -- it should be fairly
	 straightforward to lift this restriction -- just allow storing
	 more complicated expressions in *A, and gimplify it in
	 adjust_accumulator_values.  */
      if (*a)
	return false;
      *a = non_ass_var;
      *ass_var = dest;
      return true;

    case MULT_EXPR:
      /* Similar remark applies here.  Handling multiplication after addition
	 is just slightly more complicated -- we need to multiply both *A and
	 *M.  */
      if (*a || *m)
	return false;
      *m = non_ass_var;
      *ass_var = dest;
      return true;

      /* TODO -- Handle other codes (NEGATE_EXPR, MINUS_EXPR).  */

    default:
      return false;
    }
}