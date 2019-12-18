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
 int /*<<< orphan*/  NEGATE_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type_for_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_type_variant (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_minus_one_node ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_mode ; 
 int strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  unsigned_char_type_node ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_strcmp (tree arglist)
{
  tree arg1, arg2;
  const char *p1, *p2;

  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    return 0;

  arg1 = TREE_VALUE (arglist);
  arg2 = TREE_VALUE (TREE_CHAIN (arglist));

  /* If ARG1 and ARG2 are the same (and not volatile), return zero.  */
  if (operand_equal_p (arg1, arg2, 0))
    return integer_zero_node;

  p1 = c_getstr (arg1);
  p2 = c_getstr (arg2);

  if (p1 && p2)
    {
      const int i = strcmp (p1, p2);
      if (i < 0)
	return integer_minus_one_node;
      else if (i > 0)
	return integer_one_node;
      else
	return integer_zero_node;
    }

  /* If the second arg is "", return *(const unsigned char*)arg1.  */
  if (p2 && *p2 == '\0')
    {
      tree cst_uchar_node = build_type_variant (unsigned_char_type_node, 1, 0);
      tree cst_uchar_ptr_node
	= build_pointer_type_for_mode (cst_uchar_node, ptr_mode, true);

      return fold_convert (integer_type_node,
			   build1 (INDIRECT_REF, cst_uchar_node,
				   fold_convert (cst_uchar_ptr_node,
						 arg1)));
    }

  /* If the first arg is "", return -*(const unsigned char*)arg2.  */
  if (p1 && *p1 == '\0')
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

  return 0;
}