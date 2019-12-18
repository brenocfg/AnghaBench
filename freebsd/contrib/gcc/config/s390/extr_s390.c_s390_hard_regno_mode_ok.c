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
#define  ACCESS_REGS 132 
#define  ADDR_REGS 131 
#define  CC_REGS 130 
 int DImode ; 
 int /*<<< orphan*/  FLOAT_MODE_P (int) ; 
#define  FP_REGS 129 
 int /*<<< orphan*/  FRAME_REGNO_P (unsigned int) ; 
#define  GENERAL_REGS 128 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 int /*<<< orphan*/  MODE_CC ; 
 int /*<<< orphan*/  MODE_VECTOR_FLOAT ; 
 int Pmode ; 
 int /*<<< orphan*/  REGNO_PAIR_OK (unsigned int,int) ; 
 int REGNO_REG_CLASS (unsigned int) ; 
 int SImode ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 int TCmode ; 
 int TDmode ; 
 int TFmode ; 

bool
s390_hard_regno_mode_ok (unsigned int regno, enum machine_mode mode)
{
  switch (REGNO_REG_CLASS (regno))
    {
    case FP_REGS:
      if (REGNO_PAIR_OK (regno, mode))
	{
	  if (mode == SImode || mode == DImode)
	    return true;

	  if (FLOAT_MODE_P (mode) && GET_MODE_CLASS (mode) != MODE_VECTOR_FLOAT)
	    return true;
	}
      break;
    case ADDR_REGS:
      if (FRAME_REGNO_P (regno) && mode == Pmode)
	return true;

      /* fallthrough */
    case GENERAL_REGS:
      if (REGNO_PAIR_OK (regno, mode))
	{
	  if (TARGET_64BIT 
	      || (mode != TFmode && mode != TCmode && mode != TDmode))
	    return true;
	}	  
      break;
    case CC_REGS:
      if (GET_MODE_CLASS (mode) == MODE_CC)
	return true;
      break;
    case ACCESS_REGS:
      if (REGNO_PAIR_OK (regno, mode))
	{
	  if (mode == SImode || mode == Pmode)
	    return true;
	}
      break;
    default:
      return false;
    }
  
  return false;
}