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
 int CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_REG_OK_FOR_BASE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LO_SUM ; 
 scalar_t__ MEM ; 
 scalar_t__ REG ; 
 int SImode ; 
 int /*<<< orphan*/  TARGET_MACHO ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flag_pic ; 

bool
macho_lo_sum_memory_operand (rtx x, enum machine_mode mode)
{
  if (!TARGET_MACHO || !flag_pic
      || mode != SImode || GET_CODE (x) != MEM)
    return false;
  x = XEXP (x, 0);

  if (GET_CODE (x) != LO_SUM)
    return false;
  if (GET_CODE (XEXP (x, 0)) != REG)
    return false;
  if (!INT_REG_OK_FOR_BASE_P (XEXP (x, 0), 0))
    return false;
  x = XEXP (x, 1);

  return CONSTANT_P (x);
}