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

/* Variables and functions */
 int /*<<< orphan*/  INDIRECT_REF ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type_for_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_type_variant (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ host_integerp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  integer_minus_one_node ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omit_two_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_mode ; 
 int strncmp (char const*,char const*,int) ; 
 int tree_int_cst_sgn (int /*<<< orphan*/ ) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unsigned_char_type_node ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_strncmp (tree arglist)
{
  tree arg1, arg2, len;
  const char *p1, *p2;

  if (!validate_arglist (arglist,
			 POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return 0;

  arg1 = TREE_VALUE (arglist);
  arg2 = TREE_VALUE (TREE_CHAIN (arglist));
  len = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));

  /* If the LEN parameter is zero, return zero.  */
  if (integer_zerop (len))
    return omit_two_operands (integer_type_node, integer_zero_node,
			      arg1, arg2);

  /* If ARG1 and ARG2 are the same (and not volatile), return zero.  */
  if (operand_equal_p (arg1, arg2, 0))
    return omit_one_operand (integer_type_node, integer_zero_node, len);

  p1 = c_getstr (arg1);
  p2 = c_getstr (arg2);

  if (host_integerp (len, 1) && p1 && p2)
    {
      const int i = strncmp (p1, p2, tree_low_cst (len, 1));
      if (i > 0)
	return integer_one_node;
      else if (i < 0)
	return integer_minus_one_node;
      else
	return integer_zero_node;
    }

  /* If the second arg is "", and the length is greater than zero,
     return *(const unsigned char*)arg1.  */
  if (p2 && *p2 == '\0'
      && TREE_CODE (len) == INTEGER_CST
      && tree_int_cst_sgn (len) == 1)
    {
      tree cst_uchar_node = build_type_variant (unsigned_char_type_node, 1, 0);
      tree cst_uchar_ptr_node
	= build_pointer_type_for_mode (cst_uchar_node, ptr_mode, true);

      return fold_convert (integer_type_node,
			   build1 (INDIRECT_REF, cst_uchar_node,
				   fold_convert (cst_uchar_ptr_node,
						 arg1)));
    }

  /* If the first arg is "", and the length is greater than zero,
     return -*(const unsigned char*)arg2.  */
  if (p1 && *p1 == '\0'
      && TREE_CODE (len) == INTEGER_CST
      && tree_int_cst_sgn (len) == 1)
    {
      tree cst_uchar_node = build_type_variant (unsigned_char_type_node, 1, 0);
      tree cst_uchar_ptr_node
	= build_pointer_type_for_mode (cst_uchar_node, ptr_mode, true);

      tree temp = fold_convert (integer_type_node,
				build1 (INDIRECT_REF, cst_uchar_node,
					fold_convert (cst_uchar_ptr_node,
						      arg2)));
      return fold_build1 (NEGATE_EXPR, integer_type_node, temp);
    }

  /* If len parameter is one, return an expression corresponding to
     (*(const unsigned char*)arg1 - (const unsigned char*)arg2).  */
  if (host_integerp (len, 1) && tree_low_cst (len, 1) == 1)
    {
      tree cst_uchar_node = build_type_variant (unsigned_char_type_node, 1, 0);
      tree cst_uchar_ptr_node
	= build_pointer_type_for_mode (cst_uchar_node, ptr_mode, true);

      tree ind1 = fold_convert (integer_type_node,
				build1 (INDIRECT_REF, cst_uchar_node,
					fold_convert (cst_uchar_ptr_node,
						      arg1)));
      tree ind2 = fold_convert (integer_type_node,
				build1 (INDIRECT_REF, cst_uchar_node,
					fold_convert (cst_uchar_ptr_node,
						      arg2)));
      return fold_build2 (MINUS_EXPR, integer_type_node, ind1, ind2);
    }

  return 0;
}