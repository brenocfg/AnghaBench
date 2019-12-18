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
typedef  int /*<<< orphan*/  elem_op_func ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int TYPE_VECTOR_SUBPARTS (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  expand_vector_parallel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_vector_piecewise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
expand_vector_addition (block_stmt_iterator *bsi,
			elem_op_func f, elem_op_func f_parallel,
			tree type, tree a, tree b, enum tree_code code)
{
  int parts_per_word = UNITS_PER_WORD
	  	       / tree_low_cst (TYPE_SIZE_UNIT (TREE_TYPE (type)), 1);

  if (INTEGRAL_TYPE_P (TREE_TYPE (type))
      && parts_per_word >= 4
      && TYPE_VECTOR_SUBPARTS (type) >= 4)
    return expand_vector_parallel (bsi, f_parallel,
				   type, a, b, code);
  else
    return expand_vector_piecewise (bsi, f,
				    type, TREE_TYPE (type),
				    a, b, code);
}