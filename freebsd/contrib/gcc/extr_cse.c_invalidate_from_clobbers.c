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
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ZERO_EXTRACT ; 
 int /*<<< orphan*/  invalidate (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
invalidate_from_clobbers (rtx x)
{
  if (GET_CODE (x) == CLOBBER)
    {
      rtx ref = XEXP (x, 0);
      if (ref)
	{
	  if (REG_P (ref) || GET_CODE (ref) == SUBREG
	      || MEM_P (ref))
	    invalidate (ref, VOIDmode);
	  else if (GET_CODE (ref) == STRICT_LOW_PART
		   || GET_CODE (ref) == ZERO_EXTRACT)
	    invalidate (XEXP (ref, 0), GET_MODE (ref));
	}
    }
  else if (GET_CODE (x) == PARALLEL)
    {
      int i;
      for (i = XVECLEN (x, 0) - 1; i >= 0; i--)
	{
	  rtx y = XVECEXP (x, 0, i);
	  if (GET_CODE (y) == CLOBBER)
	    {
	      rtx ref = XEXP (y, 0);
	      if (REG_P (ref) || GET_CODE (ref) == SUBREG
		  || MEM_P (ref))
		invalidate (ref, VOIDmode);
	      else if (GET_CODE (ref) == STRICT_LOW_PART
		       || GET_CODE (ref) == ZERO_EXTRACT)
		invalidate (XEXP (ref, 0), GET_MODE (ref));
	    }
	}
    }
}