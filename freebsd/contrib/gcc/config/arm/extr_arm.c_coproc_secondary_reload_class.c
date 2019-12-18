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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GENERAL_REGS ; 
 int NO_REGS ; 
 scalar_t__ arm_coproc_mem_operand (int /*<<< orphan*/ ,int) ; 
 scalar_t__ s_register_operand (int /*<<< orphan*/ ,int) ; 

enum reg_class
coproc_secondary_reload_class (enum machine_mode mode, rtx x, bool wb)
{
  if (arm_coproc_mem_operand (x, wb) || s_register_operand (x, mode))
    return NO_REGS;

  return GENERAL_REGS;
}