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
 int DFmode ; 
 int /*<<< orphan*/  FIRST_MMX_REG ; 
 int /*<<< orphan*/  FIRST_SSE_REG ; 
 int GET_MODE_SIZE (int) ; 
 int SFmode ; 
 int XFmode ; 
 int ix86_hard_regno_mode_ok (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ix86_tieable_integer_mode_p (int) ; 

bool
ix86_modes_tieable_p (enum machine_mode mode1, enum machine_mode mode2)
{
  if (mode1 == mode2)
    return true;

  if (ix86_tieable_integer_mode_p (mode1)
      && ix86_tieable_integer_mode_p (mode2))
    return true;

  /* MODE2 being XFmode implies fp stack or general regs, which means we
     can tie any smaller floating point modes to it.  Note that we do not
     tie this with TFmode.  */
  if (mode2 == XFmode)
    return mode1 == SFmode || mode1 == DFmode;

  /* MODE2 being DFmode implies fp stack, general or sse regs, which means
     that we can tie it with SFmode.  */
  if (mode2 == DFmode)
    return mode1 == SFmode;

  /* If MODE2 is only appropriate for an SSE register, then tie with
     any other mode acceptable to SSE registers.  */
  if (GET_MODE_SIZE (mode2) >= 8
      && ix86_hard_regno_mode_ok (FIRST_SSE_REG, mode2))
    return ix86_hard_regno_mode_ok (FIRST_SSE_REG, mode1);

  /* If MODE2 is appropriate for an MMX (or SSE) register, then tie
     with any other mode acceptable to MMX registers.  */
  if (GET_MODE_SIZE (mode2) == 8
      && ix86_hard_regno_mode_ok (FIRST_MMX_REG, mode2))
    return ix86_hard_regno_mode_ok (FIRST_MMX_REG, mode1);

  return false;
}