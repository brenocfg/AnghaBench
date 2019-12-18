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
struct loop {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEIL_DIV_EXPR ; 
 int /*<<< orphan*/  EXACT_DIV_EXPR ; 
 int /*<<< orphan*/  GT_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_SIZE (scalar_t__) ; 
 scalar_t__ boolean_false_node ; 
 scalar_t__ boolean_true_node ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ evolution_part_in_loop_num (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ initial_condition (scalar_t__) ; 
 scalar_t__ integer_one_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  record_estimate (struct loop*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  unsigned_type_node ; 

__attribute__((used)) static void
estimate_niter_from_size_of_data (struct loop *loop, 
				  tree opnd0, 
				  tree access_fn, 
				  tree stmt)
{
  tree estimation = NULL_TREE;
  tree array_size, data_size, element_size;
  tree init, step;

  init = initial_condition (access_fn);
  step = evolution_part_in_loop_num (access_fn, loop->num);

  array_size = TYPE_SIZE (TREE_TYPE (opnd0));
  element_size = TYPE_SIZE (TREE_TYPE (TREE_TYPE (opnd0)));
  if (array_size == NULL_TREE 
      || TREE_CODE (array_size) != INTEGER_CST
      || TREE_CODE (element_size) != INTEGER_CST)
    return;

  data_size = fold_build2 (EXACT_DIV_EXPR, integer_type_node,
			   array_size, element_size);

  if (init != NULL_TREE
      && step != NULL_TREE
      && TREE_CODE (init) == INTEGER_CST
      && TREE_CODE (step) == INTEGER_CST)
    {
      tree i_plus_s = fold_build2 (PLUS_EXPR, integer_type_node, init, step);
      tree sign = fold_binary (GT_EXPR, boolean_type_node, i_plus_s, init);

      if (sign == boolean_true_node)
	estimation = fold_build2 (CEIL_DIV_EXPR, integer_type_node,
				  fold_build2 (MINUS_EXPR, integer_type_node,
					       data_size, init), step);

      /* When the step is negative, as in PR23386: (init = 3, step =
	 0ffffffff, data_size = 100), we have to compute the
	 estimation as ceil_div (init, 0 - step) + 1.  */
      else if (sign == boolean_false_node)
	estimation = 
	  fold_build2 (PLUS_EXPR, integer_type_node,
		       fold_build2 (CEIL_DIV_EXPR, integer_type_node,
				    init,
				    fold_build2 (MINUS_EXPR, unsigned_type_node,
						 integer_zero_node, step)),
		       integer_one_node);

      if (estimation)
	record_estimate (loop, estimation, boolean_true_node, stmt);
    }
}