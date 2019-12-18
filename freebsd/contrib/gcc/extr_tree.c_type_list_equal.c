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
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int simple_cst_equal (scalar_t__,scalar_t__) ; 

int
type_list_equal (tree l1, tree l2)
{
  tree t1, t2;

  for (t1 = l1, t2 = l2; t1 && t2; t1 = TREE_CHAIN (t1), t2 = TREE_CHAIN (t2))
    if (TREE_VALUE (t1) != TREE_VALUE (t2)
	|| (TREE_PURPOSE (t1) != TREE_PURPOSE (t2)
	    && ! (1 == simple_cst_equal (TREE_PURPOSE (t1), TREE_PURPOSE (t2))
		  && (TREE_TYPE (TREE_PURPOSE (t1))
		      == TREE_TYPE (TREE_PURPOSE (t2))))))
      return 0;

  return t1 == t2;
}