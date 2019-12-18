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
 scalar_t__ CC_REGNO_P (int) ; 
 scalar_t__ FP_REGNO_P (int) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ MMX_REGNO_P (int) ; 
 scalar_t__ MODE_CC ; 
 scalar_t__ MODE_PARTIAL_INT ; 
 scalar_t__ MODE_RANDOM ; 
 int QImode ; 
 scalar_t__ SSE_REGNO_P (int) ; 
 scalar_t__ TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_PARTIAL_REG_STALL ; 
 int VALID_FP_MODE_P (int) ; 
 scalar_t__ VALID_INT_MODE_P (int) ; 
 scalar_t__ VALID_MMX_REG_MODE (int) ; 
 scalar_t__ VALID_MMX_REG_MODE_3DNOW (int) ; 
 scalar_t__ VALID_SSE2_REG_MODE (int) ; 
 scalar_t__ VALID_SSE_REG_MODE (int) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 

bool
ix86_hard_regno_mode_ok (int regno, enum machine_mode mode)
{
  /* Flags and only flags can only hold CCmode values.  */
  if (CC_REGNO_P (regno))
    return GET_MODE_CLASS (mode) == MODE_CC;
  if (GET_MODE_CLASS (mode) == MODE_CC
      || GET_MODE_CLASS (mode) == MODE_RANDOM
      || GET_MODE_CLASS (mode) == MODE_PARTIAL_INT)
    return 0;
  if (FP_REGNO_P (regno))
    return VALID_FP_MODE_P (mode);
  if (SSE_REGNO_P (regno))
    {
      /* We implement the move patterns for all vector modes into and
	 out of SSE registers, even when no operation instructions
	 are available.  */
      return (VALID_SSE_REG_MODE (mode)
	      || VALID_SSE2_REG_MODE (mode)
	      || VALID_MMX_REG_MODE (mode)
	      || VALID_MMX_REG_MODE_3DNOW (mode));
    }
  if (MMX_REGNO_P (regno))
    {
      /* We implement the move patterns for 3DNOW modes even in MMX mode,
	 so if the register is available at all, then we can move data of
	 the given mode into or out of it.  */
      return (VALID_MMX_REG_MODE (mode)
	      || VALID_MMX_REG_MODE_3DNOW (mode));
    }

  if (mode == QImode)
    {
      /* Take care for QImode values - they can be in non-QI regs,
	 but then they do cause partial register stalls.  */
      if (regno < 4 || TARGET_64BIT)
	return 1;
      if (!TARGET_PARTIAL_REG_STALL)
	return 1;
      return reload_in_progress || reload_completed;
    }
  /* We handle both integer and floats in the general purpose registers.  */
  else if (VALID_INT_MODE_P (mode))
    return 1;
  else if (VALID_FP_MODE_P (mode))
    return 1;
  /* Lots of MMX code casts 8 byte vector modes to DImode.  If we then go
     on to use that value in smaller contexts, this can easily force a
     pseudo to be allocated to GENERAL_REGS.  Since this is no worse than
     supporting DImode, allow it.  */
  else if (VALID_MMX_REG_MODE_3DNOW (mode) || VALID_MMX_REG_MODE (mode))
    return 1;

  return 0;
}