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
 int /*<<< orphan*/  INTEGER_TYPE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_builtin_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  sizetype ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static tree
fold_builtin_bzero (tree arglist, bool ignore)
{
  tree dest, size, newarglist;

  if (!validate_arglist (arglist, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
    return 0;

  if (!ignore)
    return 0;

  dest = TREE_VALUE (arglist);
  size = TREE_VALUE (TREE_CHAIN (arglist));

  /* New argument list transforming bzero(ptr x, int y) to
     memset(ptr x, int 0, size_t y).   This is done this way
     so that if it isn't expanded inline, we fallback to
     calling bzero instead of memset.  */

  newarglist = build_tree_list (NULL_TREE, fold_convert (sizetype, size));
  newarglist = tree_cons (NULL_TREE, integer_zero_node, newarglist);
  newarglist = tree_cons (NULL_TREE, dest, newarglist);
  return fold_builtin_memset (newarglist, void_type_node, ignore);
}