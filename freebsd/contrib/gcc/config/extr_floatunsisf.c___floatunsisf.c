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
typedef  int USItype ;
typedef  scalar_t__ SItype ;
typedef  int SFtype ;

/* Variables and functions */

SFtype
__floatunsisf (USItype u)
{
  SItype s = (SItype) u;
  if (s < 0)
    {
      /* As in expand_float, compute (u & 1) | (u >> 1) to ensure
	 correct rounding if a nonzero bit is shifted out.  */
      return (SFtype) 2.0 * (SFtype) (SItype) ((u & 1) | (u >> 1));
    }
  else
    return (SFtype) s;
}