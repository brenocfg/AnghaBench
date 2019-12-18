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
 int BIND_EXPR ; 
 int BLOCK ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int SAVE_EXPR ; 
 int TARGET_EXPR ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  copy_tree_r (int /*<<< orphan*/ *,int*,void*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ tcc_constant ; 
 scalar_t__ tcc_declaration ; 
 scalar_t__ tcc_type ; 

__attribute__((used)) static tree
mostly_copy_tree_r (tree *tp, int *walk_subtrees, void *data)
{
  enum tree_code code = TREE_CODE (*tp);
  /* Don't unshare types, decls, constants and SAVE_EXPR nodes.  */
  if (TREE_CODE_CLASS (code) == tcc_type
      || TREE_CODE_CLASS (code) == tcc_declaration
      || TREE_CODE_CLASS (code) == tcc_constant
      || code == SAVE_EXPR || code == TARGET_EXPR
      /* We can't do anything sensible with a BLOCK used as an expression,
	 but we also can't just die when we see it because of non-expression
	 uses.  So just avert our eyes and cross our fingers.  Silly Java.  */
      || code == BLOCK)
    *walk_subtrees = 0;
  else
    {
      gcc_assert (code != BIND_EXPR);
      copy_tree_r (tp, walk_subtrees, data);
    }

  return NULL_TREE;
}