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
 int ARG_POINTER_REGNUM ; 
 int ARM_REGNO_OK_FOR_BASE_P (int) ; 
 int FIRST_PSEUDO_REGISTER ; 
 int FRAME_POINTER_REGNUM ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int LAST_ARM_REGNUM ; 
 scalar_t__ REG ; 
 int REGNO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_address_register_rtx_p (rtx x, int strict_p)
{
  int regno;

  if (GET_CODE (x) != REG)
    return 0;

  regno = REGNO (x);

  if (strict_p)
    return ARM_REGNO_OK_FOR_BASE_P (regno);

  return (regno <= LAST_ARM_REGNUM
	  || regno >= FIRST_PSEUDO_REGISTER
	  || regno == FRAME_POINTER_REGNUM
	  || regno == ARG_POINTER_REGNUM);
}