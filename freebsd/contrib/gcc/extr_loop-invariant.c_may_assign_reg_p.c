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

/* Variables and functions */
 scalar_t__ BLKmode ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HARD_REGISTER_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NO_REGS ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO_REG_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ can_copy_p (scalar_t__) ; 

__attribute__((used)) static bool
may_assign_reg_p (rtx x)
{
  return (GET_MODE (x) != VOIDmode
	  && GET_MODE (x) != BLKmode
	  && can_copy_p (GET_MODE (x))
	  && (!REG_P (x)
	      || !HARD_REGISTER_P (x)
	      || REGNO_REG_CLASS (REGNO (x)) != NO_REGS));
}