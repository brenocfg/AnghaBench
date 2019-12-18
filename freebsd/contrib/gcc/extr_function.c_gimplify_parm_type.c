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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_CONSTANT (scalar_t__) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_SIZES_GIMPLIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_type_sizes (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static tree
gimplify_parm_type (tree *tp, int *walk_subtrees, void *data)
{
  tree t = *tp;

  *walk_subtrees = 0;
  if (TYPE_P (t))
    {
      if (POINTER_TYPE_P (t))
	*walk_subtrees = 1;
      else if (TYPE_SIZE (t) && !TREE_CONSTANT (TYPE_SIZE (t))
	       && !TYPE_SIZES_GIMPLIFIED (t))
	{
	  gimplify_type_sizes (t, (tree *) data);
	  *walk_subtrees = 1;
	}
    }

  return NULL;
}