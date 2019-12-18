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

/* Variables and functions */
 int /*<<< orphan*/  DEC_ROUND_CEILING ; 
 int /*<<< orphan*/  DEC_ROUND_DOWN ; 
 int /*<<< orphan*/  DEC_ROUND_FLOOR ; 
 int /*<<< orphan*/  DEC_ROUND_HALF_EVEN ; 
 int /*<<< orphan*/  DEC_ROUND_HALF_UP ; 
#define  FE_DEC_DOWNWARD 132 
#define  FE_DEC_TONEAREST 131 
#define  FE_DEC_TONEARESTFROMZERO 130 
#define  FE_DEC_TOWARDZERO 129 
#define  FE_DEC_UPWARD 128 
 int /*<<< orphan*/  __dfp_rounding_mode ; 

void
__dfp_set_round (int mode)
{
  switch (mode)
    {
    case FE_DEC_DOWNWARD:
      __dfp_rounding_mode = DEC_ROUND_FLOOR; break;
    case FE_DEC_TONEAREST:
      __dfp_rounding_mode = DEC_ROUND_HALF_EVEN; break;
    case FE_DEC_TONEARESTFROMZERO:
      __dfp_rounding_mode = DEC_ROUND_HALF_UP; break;
    case FE_DEC_TOWARDZERO:
      __dfp_rounding_mode = DEC_ROUND_DOWN; break;
    case FE_DEC_UPWARD:
      __dfp_rounding_mode = DEC_ROUND_CEILING; break;
    default:
     /* We can't use assert in libgcc, so just return the default mode.  */
      __dfp_rounding_mode = DEC_ROUND_HALF_EVEN; break;
    }
}