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
 int COSTS_N_INSNS (int) ; 
 int DImode ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 int /*<<< orphan*/  MODE_FLOAT ; 
#define  MULT 128 
 int /*<<< orphan*/  REG_OR_SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGN_EXTEND ; 
 scalar_t__ TARGET_THUMB ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZERO_EXTEND ; 
 int arm_rtx_costs_1 (int /*<<< orphan*/ ,int,int) ; 
 int thumb_rtx_costs (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
arm_9e_rtx_costs (rtx x, int code, int outer_code, int *total)
{
  enum machine_mode mode = GET_MODE (x);
  int nonreg_cost;
  int cost;

  if (TARGET_THUMB)
    {
      switch (code)
	{
	case MULT:
	  *total = COSTS_N_INSNS (3);
	  return true;

	default:
	  *total = thumb_rtx_costs (x, code, outer_code);
	  return true;
	}
    }

  switch (code)
    {
    case MULT:
      /* There is no point basing this on the tuning, since it is always the
	 fast variant if it exists at all.  */
      if (mode == DImode
	  && (GET_CODE (XEXP (x, 0)) == GET_CODE (XEXP (x, 1)))
	  && (GET_CODE (XEXP (x, 0)) == ZERO_EXTEND
	      || GET_CODE (XEXP (x, 0)) == SIGN_EXTEND))
	{
	  *total = 3;
	  return true;
	}


      if (GET_MODE_CLASS (mode) == MODE_FLOAT)
	{
	  *total = 30;
	  return true;
	}
      if (mode == DImode)
	{
	  cost = 7;
	  nonreg_cost = 8;
	}
      else
	{
	  cost = 2;
	  nonreg_cost = 4;
	}


      *total = cost + (REG_OR_SUBREG_REG (XEXP (x, 0)) ? 0 : nonreg_cost)
		    + (REG_OR_SUBREG_REG (XEXP (x, 1)) ? 0 : nonreg_cost);
      return true;

    default:
      *total = arm_rtx_costs_1 (x, code, outer_code);
      return true;
    }
}