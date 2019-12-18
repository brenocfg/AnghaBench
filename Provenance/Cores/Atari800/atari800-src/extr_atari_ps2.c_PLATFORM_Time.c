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
 double T0_COUNT ; 
 double timer_interrupt_ticks ; 

double PLATFORM_Time(void)
{
#ifdef USE_TIMERS
	/* AFAIK, multiplication is faster than division,
	   on every CPU architecture */
	return (timer_interrupt_ticks * 65536.0 + T0_COUNT) * (1.0 / 576000);
#else
	static double fake_timer = 0;
	return fake_timer++;
#endif
}