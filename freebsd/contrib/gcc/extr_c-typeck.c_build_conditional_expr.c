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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int ARRAY_TYPE ; 
 int BLOCK_POINTER_TYPE ; 
 int COMPLEX_TYPE ; 
 int /*<<< orphan*/  COND_EXPR ; 
 scalar_t__ ERROR_MARK ; 
 scalar_t__ FUNCTION_TYPE ; 
 int INTEGER_TYPE ; 
 int POINTER_TYPE ; 
 int REAL_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_READONLY (scalar_t__) ; 
 scalar_t__ TREE_THIS_VOLATILE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ VOID_TYPE ; 
 scalar_t__ VOID_TYPE_P (scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_type_variant (scalar_t__,int,int) ; 
 scalar_t__ c_common_type (scalar_t__,scalar_t__) ; 
 scalar_t__ common_pointer_type (scalar_t__,scalar_t__) ; 
 scalar_t__ comp_target_types (scalar_t__,scalar_t__) ; 
 scalar_t__ convert (scalar_t__,scalar_t__) ; 
 scalar_t__ convert_and_check (scalar_t__,scalar_t__) ; 
 scalar_t__ default_conversion (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ flag_cond_mismatch ; 
 scalar_t__ fold_build3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ null_pointer_constant_p (scalar_t__) ; 
 scalar_t__ null_pointer_node ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 scalar_t__ qualify_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skip_evaluation ; 
 scalar_t__ tree_expr_nonnegative_warnv_p (scalar_t__,int*) ; 
 scalar_t__ void_type_node ; 
 scalar_t__ warn_sign_compare ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

tree
build_conditional_expr (tree ifexp, tree op1, tree op2)
{
  tree type1;
  tree type2;
  enum tree_code code1;
  enum tree_code code2;
  tree result_type = NULL;
  tree orig_op1 = op1, orig_op2 = op2;

  /* Promote both alternatives.  */

  if (TREE_CODE (TREE_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  if (TREE_CODE (TREE_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  if (TREE_CODE (ifexp) == ERROR_MARK
      || TREE_CODE (TREE_TYPE (op1)) == ERROR_MARK
      || TREE_CODE (TREE_TYPE (op2)) == ERROR_MARK)
    return error_mark_node;

  type1 = TREE_TYPE (op1);
  code1 = TREE_CODE (type1);
  type2 = TREE_TYPE (op2);
  code2 = TREE_CODE (type2);

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  if (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error ("non-lvalue array in conditional expression");
      return error_mark_node;
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  if (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      if (type1 == type2)
	result_type = type1;
      else
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  else if ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE))
    {
      result_type = c_common_type (type1, type2);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      if (warn_sign_compare && !skip_evaluation)
	{
	  int unsigned_op1 = TYPE_UNSIGNED (TREE_TYPE (orig_op1));
	  int unsigned_op2 = TYPE_UNSIGNED (TREE_TYPE (orig_op2));

	  if (unsigned_op1 ^ unsigned_op2)
	    {
	      bool ovf;

	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      if (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      /* Do not warn if the signed quantity is an unsuffixed
		 integer literal (or some static constant expression
		 involving such literals) and it is non-negative.  */
	      else if ((unsigned_op2
			&& tree_expr_nonnegative_warnv_p (op1, &ovf))
		       || (unsigned_op1
			   && tree_expr_nonnegative_warnv_p (op2, &ovf)))
		/* OK */;
	      else
		warning (0, "signed and unsigned type in conditional expression");
	    }
	}
    }
  else if (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      if (pedantic && (code1 != VOID_TYPE || code2 != VOID_TYPE))
	pedwarn ("ISO C forbids conditional expr with only one void side");
      result_type = void_type_node;
    }
  /* APPLE LOCAL begin blocks 6065211 */
  else if ((code1 == POINTER_TYPE
      || code1 == BLOCK_POINTER_TYPE)
     && (code2 == POINTER_TYPE
	  || code2 == BLOCK_POINTER_TYPE))
  /* APPLE LOCAL end blocks 6065211 */
    {
      if (comp_target_types (type1, type2))
	result_type = common_pointer_type (type1, type2);
      else if (null_pointer_constant_p (orig_op1))
	result_type = qualify_type (type2, type1);
      else if (null_pointer_constant_p (orig_op2))
	result_type = qualify_type (type1, type2);
      /* APPLE LOCAL begin blocks 6065211 */
      else if (code2 == BLOCK_POINTER_TYPE
	   && VOID_TYPE_P (TREE_TYPE (type1)))
	 result_type = type2;
      else if (code1 == BLOCK_POINTER_TYPE
	   && VOID_TYPE_P (TREE_TYPE (type2)))
	 result_type = type1;
      /* APPLE LOCAL end blocks 6065211 */
      else if (VOID_TYPE_P (TREE_TYPE (type1)))
	{
	  if (pedantic && TREE_CODE (TREE_TYPE (type2)) == FUNCTION_TYPE)
	    pedwarn ("ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  result_type = build_pointer_type (qualify_type (TREE_TYPE (type1),
							  TREE_TYPE (type2)));
	}
      else if (VOID_TYPE_P (TREE_TYPE (type2)))
	{
	  if (pedantic && TREE_CODE (TREE_TYPE (type1)) == FUNCTION_TYPE)
	    pedwarn ("ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  result_type = build_pointer_type (qualify_type (TREE_TYPE (type2),
							  TREE_TYPE (type1)));
	}
      else
	{
	  pedwarn ("pointer type mismatch in conditional expression");
	  result_type = build_pointer_type (void_type_node);
	}
    }
  else if (code1 == POINTER_TYPE && code2 == INTEGER_TYPE)
    {
      if (!null_pointer_constant_p (orig_op2))
	pedwarn ("pointer/integer type mismatch in conditional expression");
      else
	{
	  op2 = null_pointer_node;
	}
      result_type = type1;
    }
  else if (code2 == POINTER_TYPE && code1 == INTEGER_TYPE)
    {
      if (!null_pointer_constant_p (orig_op1))
	pedwarn ("pointer/integer type mismatch in conditional expression");
      else
	{
	  op1 = null_pointer_node;
	}
      result_type = type2;
    }
  /* APPLE LOCAL begin radar 5732232 - blocks (C++ co) */
  /* APPLE LOCAL radar 5957801 */
  else if (code1 == BLOCK_POINTER_TYPE && code2 == INTEGER_TYPE)
    {
      if (!null_pointer_constant_p (orig_op2))
	error ("block pointer/integer type mismatch in conditional expression");
      else
	{
	  op2 = convert (type1, null_pointer_node);
	}
      result_type = type1;
    }
  /* APPLE LOCAL radar 5957801 */
  else if (code2 == BLOCK_POINTER_TYPE && code1 == INTEGER_TYPE)
    {
      if (!null_pointer_constant_p (orig_op1))
	error ("block pointer/integer type mismatch in conditional expression");
      else
	{
	  op1 = convert (type2, null_pointer_node);
	}
      result_type = type2;
    }
  
  /* APPLE LOCAL end radar 5732232 - blocks (C++ co) */
  if (!result_type)
    {
      if (flag_cond_mismatch)
	result_type = void_type_node;
      else
	{
	  error ("type mismatch in conditional expression");
	  return error_mark_node;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  result_type
    = build_type_variant (result_type,
			  TREE_READONLY (op1) || TREE_READONLY (op2),
			  TREE_THIS_VOLATILE (op1) || TREE_THIS_VOLATILE (op2));

  if (result_type != TREE_TYPE (op1))
    op1 = convert_and_check (result_type, op1);
  if (result_type != TREE_TYPE (op2))
    op2 = convert_and_check (result_type, op2);

  return fold_build3 (COND_EXPR, result_type, ifexp, op1, op2);
}