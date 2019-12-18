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
 scalar_t__ ABI_AIX ; 
 scalar_t__ ABI_DARWIN ; 
 int CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DEFAULT_ABI ; 
 int DFmode ; 
 int DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_BITSIZE (int) ; 
 int GET_MODE_NUNITS (int) ; 
 int /*<<< orphan*/  INT_REG_OK_FOR_BASE_P (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LO_SUM ; 
 scalar_t__ REG ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ TARGET_ELF ; 
 scalar_t__ TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_MACHO ; 
 int /*<<< orphan*/  TARGET_POWERPC64 ; 
 scalar_t__ TARGET_TOC ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ flag_pic ; 

__attribute__((used)) static bool
legitimate_lo_sum_address_p (enum machine_mode mode, rtx x, int strict)
{
  if (GET_CODE (x) != LO_SUM)
    return false;
  if (GET_CODE (XEXP (x, 0)) != REG)
    return false;
  if (!INT_REG_OK_FOR_BASE_P (XEXP (x, 0), strict))
    return false;
  /* Restrict addressing for DI because of our SUBREG hackery.  */
  if (TARGET_E500_DOUBLE && (mode == DFmode || mode == DImode))
    return false;
  x = XEXP (x, 1);

  if (TARGET_ELF || TARGET_MACHO)
    {
      if (DEFAULT_ABI != ABI_AIX && DEFAULT_ABI != ABI_DARWIN && flag_pic)
	return false;
      if (TARGET_TOC)
	return false;
      if (GET_MODE_NUNITS (mode) != 1)
	return false;
      if (GET_MODE_BITSIZE (mode) > 64
	  || (GET_MODE_BITSIZE (mode) > 32 && !TARGET_POWERPC64
	      && !(TARGET_HARD_FLOAT && TARGET_FPRS && mode == DFmode)))
	return false;

      return CONSTANT_P (x);
    }

  return false;
}