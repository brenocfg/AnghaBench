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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {int /*<<< orphan*/  iter_type; } ;
typedef  TYPE_1__ ssa_op_iter ;
typedef  int /*<<< orphan*/  def_operand_p ;

/* Variables and functions */
 int SSA_OP_ALL_USES ; 
 int SSA_OP_VIRTUAL_KILLS ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  op_iter_init (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  op_iter_next_def (TYPE_1__*) ; 
 int /*<<< orphan*/  ssa_op_iter_def ; 

__attribute__((used)) static inline def_operand_p
op_iter_init_def (ssa_op_iter *ptr, tree stmt, int flags)
{
  gcc_assert ((flags & (SSA_OP_ALL_USES | SSA_OP_VIRTUAL_KILLS)) == 0);
  op_iter_init (ptr, stmt, flags);
  ptr->iter_type = ssa_op_iter_def;
  return op_iter_next_def (ptr);
}