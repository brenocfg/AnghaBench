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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ DFmode ; 
 scalar_t__ DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int SImode ; 
 scalar_t__ SPE_VECTOR_MODE (scalar_t__) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ TARGET_SPE ; 

bool
invalid_e500_subreg (rtx op, enum machine_mode mode)
{
  if (TARGET_E500_DOUBLE)
    {
      /* Reject (subreg:SI (reg:DF)).  */
      if (GET_CODE (op) == SUBREG
	  && mode == SImode
	  && REG_P (SUBREG_REG (op))
	  && GET_MODE (SUBREG_REG (op)) == DFmode)
	return true;

      /* Reject (subreg:DF (reg:DI)).  */
      if (GET_CODE (op) == SUBREG
	  && mode == DFmode
	  && REG_P (SUBREG_REG (op))
	  && GET_MODE (SUBREG_REG (op)) == DImode)
	return true;
    }

  if (TARGET_SPE
      && GET_CODE (op) == SUBREG
      && mode == SImode
      && REG_P (SUBREG_REG (op))
      && SPE_VECTOR_MODE (GET_MODE (SUBREG_REG (op))))
    return true;

  return false;
}