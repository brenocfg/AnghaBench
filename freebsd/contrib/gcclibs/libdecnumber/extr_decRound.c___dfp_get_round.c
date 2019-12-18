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
#define  DEC_ROUND_CEILING 132 
#define  DEC_ROUND_DOWN 131 
#define  DEC_ROUND_FLOOR 130 
#define  DEC_ROUND_HALF_EVEN 129 
#define  DEC_ROUND_HALF_UP 128 
 int FE_DEC_DOWNWARD ; 
 int FE_DEC_TONEAREST ; 
 int FE_DEC_TONEARESTFROMZERO ; 
 int FE_DEC_TOWARDZERO ; 
 int FE_DEC_UPWARD ; 
 int __dfp_rounding_mode ; 

int
__dfp_get_round (void)
{
  int mode;

  switch (__dfp_rounding_mode)
    {
    case DEC_ROUND_FLOOR:
      mode = FE_DEC_DOWNWARD; break;
    case DEC_ROUND_HALF_EVEN:
      mode = FE_DEC_TONEAREST; break;
    case DEC_ROUND_HALF_UP:
      mode = FE_DEC_TONEARESTFROMZERO; break;
    case DEC_ROUND_DOWN:
      mode = FE_DEC_TOWARDZERO; break;
    case DEC_ROUND_CEILING:
      mode = FE_DEC_UPWARD; break;
    default:
      /* We shouldn't get here, but can't use assert in libgcc.  */
      mode = -1;
    }
  return mode;
}