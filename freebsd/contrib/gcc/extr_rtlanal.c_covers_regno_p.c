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
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 int covers_regno_no_parallel_p (scalar_t__,unsigned int) ; 

__attribute__((used)) static bool
covers_regno_p (rtx dest, unsigned int test_regno)
{
  if (GET_CODE (dest) == PARALLEL)
    {
      /* Some targets place small structures in registers for return
	 values of functions, and those registers are wrapped in
	 PARALLELs that we may see as the destination of a SET.  */
      int i;

      for (i = XVECLEN (dest, 0) - 1; i >= 0; i--)
	{
	  rtx inner = XEXP (XVECEXP (dest, 0, i), 0);
	  if (inner != NULL_RTX
	      && covers_regno_no_parallel_p (inner, test_regno))
	    return true;
	}

      return false;
    }
  else
    return covers_regno_no_parallel_p (dest, test_regno);
}