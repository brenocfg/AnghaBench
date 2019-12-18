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

/* Variables and functions */
 size_t BUILT_IN_MEMCPY ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ c_strlen (scalar_t__,int) ; 
 scalar_t__ fold_convert (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* implicit_built_in_decls ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 scalar_t__ omit_one_operand (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssize_int (int) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_builtin_strncpy (tree fndecl, tree arglist, tree slen)
{
  tree dest, src, len, fn;

  if (!validate_arglist (arglist,
			 POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return 0;

  dest = TREE_VALUE (arglist);
  src = TREE_VALUE (TREE_CHAIN (arglist));
  len = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));

  /* If the LEN parameter is zero, return DEST.  */
  if (integer_zerop (len))
    return omit_one_operand (TREE_TYPE (TREE_TYPE (fndecl)), dest, src);

  /* We can't compare slen with len as constants below if len is not a
     constant.  */
  if (len == 0 || TREE_CODE (len) != INTEGER_CST)
    return 0;

  if (!slen)
    slen = c_strlen (src, 1);

  /* Now, we must be passed a constant src ptr parameter.  */
  if (slen == 0 || TREE_CODE (slen) != INTEGER_CST)
    return 0;

  slen = size_binop (PLUS_EXPR, slen, ssize_int (1));

  /* We do not support simplification of this case, though we do
     support it when expanding trees into RTL.  */
  /* FIXME: generate a call to __builtin_memset.  */
  if (tree_int_cst_lt (slen, len))
    return 0;

  /* OK transform into builtin memcpy.  */
  fn = implicit_built_in_decls[BUILT_IN_MEMCPY];
  if (!fn)
    return 0;
  return fold_convert (TREE_TYPE (TREE_TYPE (fndecl)),
		       build_function_call_expr (fn, arglist));
}