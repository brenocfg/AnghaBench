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

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ IF_THEN_ELSE ; 
 scalar_t__ NE ; 
 scalar_t__ UNSPEC ; 
 int UNSPEC_CHKACLR ; 
 int UNSPEC_CHKS ; 
 int UNSPEC_LDCCLR ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static int
ia64_spec_check_src_p (rtx src)
{
  if (GET_CODE (src) == IF_THEN_ELSE)
    {
      rtx t;

      t = XEXP (src, 0);
      if (GET_CODE (t) == NE)
	{
	  t = XEXP (t, 0);	    

	  if (GET_CODE (t) == UNSPEC)
	    {
	      int code;
	      
	      code = XINT (t, 1);
	     
	      if (code == UNSPEC_CHKACLR
		  || code == UNSPEC_CHKS
		  || code == UNSPEC_LDCCLR)
		{
		  gcc_assert (code != 0);
		  return code;
		}
	    }
	}
    }
  return 0;
}