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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_INT ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ZERO_EXTRACT ; 

__attribute__((used)) static bool
reg_subword_p (rtx x, rtx reg)
{
  /* Check that reg is an integer mode register.  */
  if (!REG_P (reg) || GET_MODE_CLASS (GET_MODE (reg)) != MODE_INT)
    return false;

  if (GET_CODE (x) == STRICT_LOW_PART
      || GET_CODE (x) == ZERO_EXTRACT)
    x = XEXP (x, 0);

  return GET_CODE (x) == SUBREG
	 && SUBREG_REG (x) == reg
	 && GET_MODE_CLASS (GET_MODE (x)) == MODE_INT;
}