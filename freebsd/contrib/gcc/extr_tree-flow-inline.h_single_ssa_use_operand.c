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
typedef  int /*<<< orphan*/  use_operand_p ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  ssa_op_iter ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_USE_OPERAND_P ; 
 scalar_t__ op_iter_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_iter_init_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  op_iter_next_use (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline use_operand_p
single_ssa_use_operand (tree stmt, int flags)
{
  use_operand_p var;
  ssa_op_iter iter;

  var = op_iter_init_use (&iter, stmt, flags);
  if (op_iter_done (&iter))
    return NULL_USE_OPERAND_P;
  op_iter_next_use (&iter);
  if (op_iter_done (&iter))
    return var;
  return NULL_USE_OPERAND_P;
}