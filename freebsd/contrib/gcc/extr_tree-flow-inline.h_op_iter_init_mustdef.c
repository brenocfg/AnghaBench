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
typedef  int /*<<< orphan*/  def_operand_p ;

/* Variables and functions */
 scalar_t__ PHI_NODE ; 
 int /*<<< orphan*/  SSA_OP_VMUSTKILL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  op_iter_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_iter_next_maymustdef (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ssa_op_iter_maymustdef ; 

__attribute__((used)) static inline void
op_iter_init_mustdef (ssa_op_iter *ptr, tree stmt, use_operand_p *kill, 
		     def_operand_p *def)
{
  gcc_assert (TREE_CODE (stmt) != PHI_NODE);

  op_iter_init (ptr, stmt, SSA_OP_VMUSTKILL);
  ptr->iter_type = ssa_op_iter_maymustdef;
  op_iter_next_maymustdef (kill, def, ptr);
}