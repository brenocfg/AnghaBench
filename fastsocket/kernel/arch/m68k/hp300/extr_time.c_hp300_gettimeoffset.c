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
 scalar_t__ CLOCKBASE ; 
 unsigned char INTVAL ; 
 unsigned short USECS_PER_JIFFY ; 
 unsigned char in_8 (scalar_t__) ; 

unsigned long hp300_gettimeoffset(void)
{
  /* Read current timer 1 value */
  unsigned char lsb, msb1, msb2;
  unsigned short ticks;

  msb1 = in_8(CLOCKBASE + 5);
  lsb = in_8(CLOCKBASE + 7);
  msb2 = in_8(CLOCKBASE + 5);
  if (msb1 != msb2)
    /* A carry happened while we were reading.  Read it again */
    lsb = in_8(CLOCKBASE + 7);
  ticks = INTVAL - ((msb2 << 8) | lsb);
  return (USECS_PER_JIFFY * ticks) / INTVAL;
}