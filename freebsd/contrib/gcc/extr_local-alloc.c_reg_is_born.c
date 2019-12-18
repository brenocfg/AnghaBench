#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int death; } ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEUDO_REGNO_SIZE (int) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_qty (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_life (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  post_mark_life (int,int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_1__* qty ; 
 int* reg_qty ; 
 int subreg_regno (int /*<<< orphan*/ ) ; 
 int this_insn_number ; 

__attribute__((used)) static void
reg_is_born (rtx reg, int birth)
{
  int regno;

  if (GET_CODE (reg) == SUBREG)
    {
      regno = REGNO (SUBREG_REG (reg));
      if (regno < FIRST_PSEUDO_REGISTER)
	regno = subreg_regno (reg);
    }
  else
    regno = REGNO (reg);

  if (regno < FIRST_PSEUDO_REGISTER)
    {
      mark_life (regno, GET_MODE (reg), 1);

      /* If the register was to have been born earlier that the present
	 insn, mark it as live where it is actually born.  */
      if (birth < 2 * this_insn_number)
	post_mark_life (regno, GET_MODE (reg), 1, birth, 2 * this_insn_number);
    }
  else
    {
      if (reg_qty[regno] == -2)
	alloc_qty (regno, GET_MODE (reg), PSEUDO_REGNO_SIZE (regno), birth);

      /* If this register has a quantity number, show that it isn't dead.  */
      if (reg_qty[regno] >= 0)
	qty[reg_qty[regno]].death = -1;
    }
}