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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int ADDL_REGS ; 
#define  ALL_REGS 137 
#define  AR_I_REGS 136 
#define  AR_M_REGS 135 
#define  BR_REGS 134 
#define  FP_REGS 133 
#define  FR_REGS 132 
#define  GR_AND_BR_REGS 131 
#define  GR_AND_FR_REGS 130 
#define  GR_REGS 129 
 int MEMORY_MOVE_COST (int,int,int /*<<< orphan*/ ) ; 
#define  PR_REGS 128 
 int RFmode ; 
 int XFmode ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

int
ia64_register_move_cost (enum machine_mode mode, enum reg_class from,
			 enum reg_class to)
{
  /* ADDL_REGS is the same as GR_REGS for movement purposes.  */
  if (to == ADDL_REGS)
    to = GR_REGS;
  if (from == ADDL_REGS)
    from = GR_REGS;

  /* All costs are symmetric, so reduce cases by putting the
     lower number class as the destination.  */
  if (from < to)
    {
      enum reg_class tmp = to;
      to = from, from = tmp;
    }

  /* Moving from FR<->GR in XFmode must be more expensive than 2,
     so that we get secondary memory reloads.  Between FR_REGS,
     we have to make this at least as expensive as MEMORY_MOVE_COST
     to avoid spectacularly poor register class preferencing.  */
  if (mode == XFmode || mode == RFmode)
    {
      if (to != GR_REGS || from != GR_REGS)
        return MEMORY_MOVE_COST (mode, to, 0);
      else
	return 3;
    }

  switch (to)
    {
    case PR_REGS:
      /* Moving between PR registers takes two insns.  */
      if (from == PR_REGS)
	return 3;
      /* Moving between PR and anything but GR is impossible.  */
      if (from != GR_REGS)
	return MEMORY_MOVE_COST (mode, to, 0);
      break;

    case BR_REGS:
      /* Moving between BR and anything but GR is impossible.  */
      if (from != GR_REGS && from != GR_AND_BR_REGS)
	return MEMORY_MOVE_COST (mode, to, 0);
      break;

    case AR_I_REGS:
    case AR_M_REGS:
      /* Moving between AR and anything but GR is impossible.  */
      if (from != GR_REGS)
	return MEMORY_MOVE_COST (mode, to, 0);
      break;

    case GR_REGS:
    case FR_REGS:
    case FP_REGS:
    case GR_AND_FR_REGS:
    case GR_AND_BR_REGS:
    case ALL_REGS:
      break;

    default:
      gcc_unreachable ();
    }

  return 2;
}