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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int** hard_regno_nregs ; 
 int /*<<< orphan*/  hard_regs_live ; 

__attribute__((used)) static void
mark_reg_live_nc (int regno, enum machine_mode mode)
{
  int last = regno + hard_regno_nregs[regno][mode];
  while (regno < last)
    {
      SET_HARD_REG_BIT (hard_regs_live, regno);
      regno++;
    }
}