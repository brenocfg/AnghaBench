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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  expand_builtin_memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizetype ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_bcopy (tree exp)
{
  tree arglist = TREE_OPERAND (exp, 1);
  tree type = TREE_TYPE (exp);
  tree src, dest, size, newarglist;

  if (!validate_arglist (arglist,
			 POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return NULL_RTX;

  src = TREE_VALUE (arglist);
  dest = TREE_VALUE (TREE_CHAIN (arglist));
  size = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));

  /* New argument list transforming bcopy(ptr x, ptr y, int z) to
     memmove(ptr y, ptr x, size_t z).   This is done this way
     so that if it isn't expanded inline, we fallback to
     calling bcopy instead of memmove.  */

  newarglist = build_tree_list (NULL_TREE, fold_convert (sizetype, size));
  newarglist = tree_cons (NULL_TREE, src, newarglist);
  newarglist = tree_cons (NULL_TREE, dest, newarglist);

  return expand_builtin_memmove (newarglist, type, const0_rtx, VOIDmode, exp);
}