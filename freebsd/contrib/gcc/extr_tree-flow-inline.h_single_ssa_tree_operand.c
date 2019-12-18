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
typedef  int /*<<< orphan*/  ssa_op_iter ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ op_iter_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_iter_init_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  op_iter_next_tree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline tree
single_ssa_tree_operand (tree stmt, int flags)
{
  tree var;
  ssa_op_iter iter;

  var = op_iter_init_tree (&iter, stmt, flags);
  if (op_iter_done (&iter))
    return NULL_TREE;
  op_iter_next_tree (&iter);
  if (op_iter_done (&iter))
    return var;
  return NULL_TREE;
}