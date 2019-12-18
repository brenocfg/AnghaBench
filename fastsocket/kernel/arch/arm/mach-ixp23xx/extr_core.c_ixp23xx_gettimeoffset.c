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
 unsigned long CLOCK_TICKS_PER_USEC ; 
 unsigned long* IXP23XX_TIMER_CONT ; 
 unsigned long LATCH ; 
 unsigned long next_jiffy_time ; 

__attribute__((used)) static unsigned long
ixp23xx_gettimeoffset(void)
{
	unsigned long elapsed;

	elapsed = *IXP23XX_TIMER_CONT - (next_jiffy_time - LATCH);

	return elapsed / CLOCK_TICKS_PER_USEC;
}