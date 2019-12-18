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

/* Variables and functions */
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ MINUS_EXPR ; 
 int MULT_EXPR ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CONSTANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 scalar_t__ VOID_TYPE ; 
 int /*<<< orphan*/  build_binary_op (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c_common_type_for_size (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_defer_overflow_warnings () ; 
 int /*<<< orphan*/  fold_undefer_and_ignore_overflow_warnings () ; 
 int /*<<< orphan*/  integer_one_node ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizetype ; 
 scalar_t__ warn_pointer_arith ; 

tree
pointer_int_sum (enum tree_code resultcode, tree ptrop, tree intop)
{
  tree size_exp, ret;

  /* The result is a pointer of the same type that is being added.  */

  tree result_type = TREE_TYPE (ptrop);

  if (TREE_CODE (TREE_TYPE (result_type)) == VOID_TYPE)
    {
      if (pedantic || warn_pointer_arith)
	pedwarn ("pointer of type %<void *%> used in arithmetic");
      size_exp = integer_one_node;
    }
  else if (TREE_CODE (TREE_TYPE (result_type)) == FUNCTION_TYPE)
    {
      if (pedantic || warn_pointer_arith)
	pedwarn ("pointer to a function used in arithmetic");
      size_exp = integer_one_node;
    }
  else if (TREE_CODE (TREE_TYPE (result_type)) == METHOD_TYPE)
    {
      if (pedantic || warn_pointer_arith)
	pedwarn ("pointer to member function used in arithmetic");
      size_exp = integer_one_node;
    }
  else
    size_exp = size_in_bytes (TREE_TYPE (result_type));

  /* We are manipulating pointer values, so we don't need to warn
     about relying on undefined signed overflow.  We disable the
     warning here because we use integer types so fold won't know that
     they are really pointers.  */
  fold_defer_overflow_warnings ();

  /* If what we are about to multiply by the size of the elements
     contains a constant term, apply distributive law
     and multiply that constant term separately.
     This helps produce common subexpressions.  */

  if ((TREE_CODE (intop) == PLUS_EXPR || TREE_CODE (intop) == MINUS_EXPR)
      && !TREE_CONSTANT (intop)
      && TREE_CONSTANT (TREE_OPERAND (intop, 1))
      && TREE_CONSTANT (size_exp)
      /* If the constant comes from pointer subtraction,
	 skip this optimization--it would cause an error.  */
      && TREE_CODE (TREE_TYPE (TREE_OPERAND (intop, 0))) == INTEGER_TYPE
      /* If the constant is unsigned, and smaller than the pointer size,
	 then we must skip this optimization.  This is because it could cause
	 an overflow error if the constant is negative but INTOP is not.  */
      && (!TYPE_UNSIGNED (TREE_TYPE (intop))
	  || (TYPE_PRECISION (TREE_TYPE (intop))
	      == TYPE_PRECISION (TREE_TYPE (ptrop)))))
    {
      enum tree_code subcode = resultcode;
      tree int_type = TREE_TYPE (intop);
      if (TREE_CODE (intop) == MINUS_EXPR)
	subcode = (subcode == PLUS_EXPR ? MINUS_EXPR : PLUS_EXPR);
      /* Convert both subexpression types to the type of intop,
	 because weird cases involving pointer arithmetic
	 can result in a sum or difference with different type args.  */
      ptrop = build_binary_op (subcode, ptrop,
			       convert (int_type, TREE_OPERAND (intop, 1)), 1);
      intop = convert (int_type, TREE_OPERAND (intop, 0));
    }

  /* Convert the integer argument to a type the same size as sizetype
     so the multiply won't overflow spuriously.  */

  if (TYPE_PRECISION (TREE_TYPE (intop)) != TYPE_PRECISION (sizetype)
      || TYPE_UNSIGNED (TREE_TYPE (intop)) != TYPE_UNSIGNED (sizetype))
    intop = convert (c_common_type_for_size (TYPE_PRECISION (sizetype),
					     TYPE_UNSIGNED (sizetype)), intop);

  /* Replace the integer argument with a suitable product by the object size.
     Do this multiplication as signed, then convert to the appropriate
     pointer type (actually unsigned integral).  */

  intop = convert (result_type,
		   build_binary_op (MULT_EXPR, intop,
				    convert (TREE_TYPE (intop), size_exp), 1));

  /* Create the sum or difference.  */
  ret = fold_build2 (resultcode, result_type, ptrop, intop);

  fold_undefer_and_ignore_overflow_warnings ();

  return ret;
}