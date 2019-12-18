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
 scalar_t__ BOOLEAN_TYPE ; 
 scalar_t__ ENUMERAL_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  c_common_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_common_type_for_size (int /*<<< orphan*/ ,int) ; 

tree
common_type (tree t1, tree t2)
{
  if (TREE_CODE (t1) == ENUMERAL_TYPE)
    t1 = c_common_type_for_size (TYPE_PRECISION (t1), 1);
  if (TREE_CODE (t2) == ENUMERAL_TYPE)
    t2 = c_common_type_for_size (TYPE_PRECISION (t2), 1);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  if (TREE_CODE (t1) == BOOLEAN_TYPE
      && TREE_CODE (t2) == BOOLEAN_TYPE)
    return boolean_type_node;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  if (TREE_CODE (t1) == BOOLEAN_TYPE)
    return t2;
  if (TREE_CODE (t2) == BOOLEAN_TYPE)
    return t1;

  return c_common_type (t1, t2);
}