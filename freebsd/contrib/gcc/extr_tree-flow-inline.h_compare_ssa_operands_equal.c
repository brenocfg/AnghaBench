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
typedef  int /*<<< orphan*/  ssa_op_iter ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  clear_and_done_ssa_iter (int /*<<< orphan*/ *) ; 
 int op_iter_done (int /*<<< orphan*/ *) ; 
 scalar_t__ op_iter_init_tree (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ op_iter_next_tree (int /*<<< orphan*/ *) ; 
 scalar_t__ stmt_ann (scalar_t__) ; 

__attribute__((used)) static inline bool
compare_ssa_operands_equal (tree stmt1, tree stmt2, int flags)
{
  ssa_op_iter iter1, iter2;
  tree op1 = NULL_TREE;
  tree op2 = NULL_TREE;
  bool look1, look2;

  if (stmt1 == stmt2)
    return true;

  look1 = stmt1 && stmt_ann (stmt1);
  look2 = stmt2 && stmt_ann (stmt2);

  if (look1)
    {
      op1 = op_iter_init_tree (&iter1, stmt1, flags);
      if (!look2)
        return op_iter_done (&iter1);
    }
  else
    clear_and_done_ssa_iter (&iter1);

  if (look2)
    {
      op2 = op_iter_init_tree (&iter2, stmt2, flags);
      if (!look1)
        return op_iter_done (&iter2);
    }
  else
    clear_and_done_ssa_iter (&iter2);

  while (!op_iter_done (&iter1) && !op_iter_done (&iter2))
    {
      if (op1 != op2)
	return false;
      op1 = op_iter_next_tree (&iter1);
      op2 = op_iter_next_tree (&iter2);
    }

  return (op_iter_done (&iter1) && op_iter_done (&iter2));
}