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
 size_t BUILT_IN_MEMCPY ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_strlen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * implicit_built_in_decls ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize_size ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssize_int (int) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_builtin_strcpy (tree fndecl, tree arglist, tree len)
{
  tree dest, src, fn;

  if (!validate_arglist (arglist,
			 POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    return 0;

  dest = TREE_VALUE (arglist);
  src = TREE_VALUE (TREE_CHAIN (arglist));

  /* If SRC and DEST are the same (and not volatile), return DEST.  */
  if (operand_equal_p (src, dest, 0))
    return fold_convert (TREE_TYPE (TREE_TYPE (fndecl)), dest);

  if (optimize_size)
    return 0;

  fn = implicit_built_in_decls[BUILT_IN_MEMCPY];
  if (!fn)
    return 0;

  if (!len)
    {
      len = c_strlen (src, 1);
      if (! len || TREE_SIDE_EFFECTS (len))
	return 0;
    }

  len = size_binop (PLUS_EXPR, len, ssize_int (1));
  arglist = build_tree_list (NULL_TREE, len);
  arglist = tree_cons (NULL_TREE, src, arglist);
  arglist = tree_cons (NULL_TREE, dest, arglist);
  return fold_convert (TREE_TYPE (TREE_TYPE (fndecl)),
		       build_function_call_expr (fn, arglist));
}