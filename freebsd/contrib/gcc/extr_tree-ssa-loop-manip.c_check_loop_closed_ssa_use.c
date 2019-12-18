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
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {int /*<<< orphan*/  loop_father; } ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ flow_bb_inside_loop_p (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_loop_closed_ssa_use (basic_block bb, tree use)
{
  tree def;
  basic_block def_bb;
  
  if (TREE_CODE (use) != SSA_NAME || !is_gimple_reg (use))
    return;

  def = SSA_NAME_DEF_STMT (use);
  def_bb = bb_for_stmt (def);
  gcc_assert (!def_bb
	      || flow_bb_inside_loop_p (def_bb->loop_father, bb));
}