#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  use_operand_p ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {int /*<<< orphan*/  iter_type; } ;
typedef  TYPE_1__ ssa_op_iter ;

/* Variables and functions */
 int SSA_OP_ALL_DEFS ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  op_iter_init (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  op_iter_next_use (TYPE_1__*) ; 
 int /*<<< orphan*/  ssa_op_iter_use ; 

__attribute__((used)) static inline use_operand_p
op_iter_init_use (ssa_op_iter *ptr, tree stmt, int flags)
{
  gcc_assert ((flags & SSA_OP_ALL_DEFS) == 0);
  op_iter_init (ptr, stmt, flags);
  ptr->iter_type = ssa_op_iter_use;
  return op_iter_next_use (ptr);
}