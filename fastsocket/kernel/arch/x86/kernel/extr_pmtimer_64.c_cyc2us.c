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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 cyc2us(u32 cycles)
{
	/* The Power Management Timer ticks at 3.579545 ticks per microsecond.
	 * 1 / PM_TIMER_FREQUENCY == 0.27936511 =~ 286/1024 [error: 0.024%]
	 *
	 * Even with HZ = 100, delta is at maximum 35796 ticks, so it can
	 * easily be multiplied with 286 (=0x11E) without having to fear
	 * u32 overflows.
	 */
	cycles *= 286;
	return (cycles >> 10);
}