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
#define  IMAGPART_EXPR 130 
 int /*<<< orphan*/  IS_TYPE_OR_DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  REALPART_EXPR 129 
#define  SSA_NAME 128 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_uninit (int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static tree
warn_uninitialized_var (tree *tp, int *walk_subtrees, void *data)
{
  tree t = *tp;

  switch (TREE_CODE (t))
    {
    case SSA_NAME:
      /* We only do data flow with SSA_NAMEs, so that's all we
	 can warn about.  */
      warn_uninit (t, "%H%qD is used uninitialized in this function", data);
      *walk_subtrees = 0;
      break;

    case REALPART_EXPR:
    case IMAGPART_EXPR:
      /* The total store transformation performed during gimplification
	 creates uninitialized variable uses.  If all is well, these will
	 be optimized away, so don't warn now.  */
      if (TREE_CODE (TREE_OPERAND (t, 0)) == SSA_NAME)
	*walk_subtrees = 0;
      break;

    default:
      if (IS_TYPE_OR_DECL_P (t))
	*walk_subtrees = 0;
      break;
    }

  return NULL_TREE;
}