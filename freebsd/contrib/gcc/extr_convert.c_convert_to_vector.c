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
#define  INTEGER_TYPE 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ ) ; 
#define  VECTOR_TYPE 128 
 int /*<<< orphan*/  VIEW_CONVERT_EXPR ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
convert_to_vector (tree type, tree expr)
{
  switch (TREE_CODE (TREE_TYPE (expr)))
    {
    case INTEGER_TYPE:
    case VECTOR_TYPE:
      if (!tree_int_cst_equal (TYPE_SIZE (type), TYPE_SIZE (TREE_TYPE (expr))))
	{
	  error ("can't convert between vector values of different size");
	  return error_mark_node;
	}
      return build1 (VIEW_CONVERT_EXPR, type, expr);

    default:
      error ("can't convert value to a vector");
      return error_mark_node;
    }
}