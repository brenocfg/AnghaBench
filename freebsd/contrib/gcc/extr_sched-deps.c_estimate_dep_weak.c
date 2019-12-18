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
typedef  int dw_t ;

/* Variables and functions */
 int MIN_DEP_WEAK ; 
 int NO_DEP_WEAK ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int UNCERTAIN_DEP_WEAK ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dw_t
estimate_dep_weak (rtx mem1, rtx mem2)
{
  rtx r1, r2;

  if (mem1 == mem2)
    /* MEMs are the same - don't speculate.  */
    return MIN_DEP_WEAK;

  r1 = XEXP (mem1, 0);
  r2 = XEXP (mem2, 0);

  if (r1 == r2
      || (REG_P (r1) && REG_P (r2)
	  && REGNO (r1) == REGNO (r2)))
    /* Again, MEMs are the same.  */
    return MIN_DEP_WEAK;
  else if ((REG_P (r1) && !REG_P (r2))
	   || (!REG_P (r1) && REG_P (r2)))
    /* Different addressing modes - reason to be more speculative,
       than usual.  */
    return NO_DEP_WEAK - (NO_DEP_WEAK - UNCERTAIN_DEP_WEAK) / 2;
  else
    /* We can't say anything about the dependence.  */
    return UNCERTAIN_DEP_WEAK;
}