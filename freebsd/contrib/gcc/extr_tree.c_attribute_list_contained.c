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
 int /*<<< orphan*/  IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_LIST ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/ * TREE_VALUE (scalar_t__) ; 
 scalar_t__ lookup_attribute (int /*<<< orphan*/ ,scalar_t__) ; 
 int simple_cst_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int simple_cst_list_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
attribute_list_contained (tree l1, tree l2)
{
  tree t1, t2;

  /* First check the obvious, maybe the lists are identical.  */
  if (l1 == l2)
    return 1;

  /* Maybe the lists are similar.  */
  for (t1 = l1, t2 = l2;
       t1 != 0 && t2 != 0
        && TREE_PURPOSE (t1) == TREE_PURPOSE (t2)
        && TREE_VALUE (t1) == TREE_VALUE (t2);
       t1 = TREE_CHAIN (t1), t2 = TREE_CHAIN (t2));

  /* Maybe the lists are equal.  */
  if (t1 == 0 && t2 == 0)
    return 1;

  for (; t2 != 0; t2 = TREE_CHAIN (t2))
    {
      tree attr;
      for (attr = lookup_attribute (IDENTIFIER_POINTER (TREE_PURPOSE (t2)), l1);
	   attr != NULL_TREE;
	   attr = lookup_attribute (IDENTIFIER_POINTER (TREE_PURPOSE (t2)),
				    TREE_CHAIN (attr)))
	{
	  if (TREE_VALUE (t2) != NULL
	      && TREE_CODE (TREE_VALUE (t2)) == TREE_LIST
	      && TREE_VALUE (attr) != NULL
	      && TREE_CODE (TREE_VALUE (attr)) == TREE_LIST)
	    {
	      if (simple_cst_list_equal (TREE_VALUE (t2),
					 TREE_VALUE (attr)) == 1)
		break;
	    }
	  else if (simple_cst_equal (TREE_VALUE (t2), TREE_VALUE (attr)) == 1)
	    break;
	}

      if (attr == 0)
	return 0;
    }

  return 1;
}