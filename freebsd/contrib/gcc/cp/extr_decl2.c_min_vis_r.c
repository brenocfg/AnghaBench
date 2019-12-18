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
 int CLASSTYPE_VISIBILITY (int /*<<< orphan*/ *) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_DECL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ *) ; 
 int VISIBILITY_ANON ; 

__attribute__((used)) static tree
min_vis_r (tree *tp, int *walk_subtrees, void *data)
{
  int *vis_p = (int *)data;
  if (! TYPE_P (*tp))
    {
      *walk_subtrees = 0;
    }
  else if (CLASS_TYPE_P (*tp))
    {
      if (!TREE_PUBLIC (TYPE_MAIN_DECL (*tp)))
	{
	  *vis_p = VISIBILITY_ANON;
	  return *tp;
	}
      else if (CLASSTYPE_VISIBILITY (*tp) > *vis_p)
	*vis_p = CLASSTYPE_VISIBILITY (*tp);
    }
  return NULL;
}