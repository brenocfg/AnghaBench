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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int CCEQmode ; 
 int CCFPmode ; 
 int CCUNSmode ; 
 int EQ ; 
 int GE ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ GET_RTX_CLASS (int) ; 
 int GEU ; 
 int GT ; 
 int GTU ; 
 int LE ; 
 int LEU ; 
 int LT ; 
 int LTGT ; 
 int LTU ; 
 scalar_t__ MODE_CC ; 
 int NE ; 
 int ORDERED ; 
 scalar_t__ RTX_COMM_COMPARE ; 
 scalar_t__ RTX_COMPARE ; 
 int UNEQ ; 
 int UNGE ; 
 int UNGT ; 
 int UNLE ; 
 int UNLT ; 
 int UNORDERED ; 
 scalar_t__ flag_finite_math_only ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

void
validate_condition_mode (enum rtx_code code, enum machine_mode mode)
{
  gcc_assert ((GET_RTX_CLASS (code) == RTX_COMPARE
	       || GET_RTX_CLASS (code) == RTX_COMM_COMPARE)
	      && GET_MODE_CLASS (mode) == MODE_CC);

  /* These don't make sense.  */
  gcc_assert ((code != GT && code != LT && code != GE && code != LE)
	      || mode != CCUNSmode);

  gcc_assert ((code != GTU && code != LTU && code != GEU && code != LEU)
	      || mode == CCUNSmode);

  gcc_assert (mode == CCFPmode
	      || (code != ORDERED && code != UNORDERED
		  && code != UNEQ && code != LTGT
		  && code != UNGT && code != UNLT
		  && code != UNGE && code != UNLE));

  /* These should never be generated except for
     flag_finite_math_only.  */
  gcc_assert (mode != CCFPmode
	      || flag_finite_math_only
	      || (code != LE && code != GE
		  && code != UNEQ && code != LTGT
		  && code != UNGT && code != UNLT));

  /* These are invalid; the information is not there.  */
  gcc_assert (mode != CCEQmode || code == EQ || code == NE);
}