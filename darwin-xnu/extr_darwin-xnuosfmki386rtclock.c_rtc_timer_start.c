#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rtcDeadline; } ;

/* Variables and functions */
 int /*<<< orphan*/  EndOfAllTime ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 
 TYPE_1__* x86_lcpu () ; 

void
rtc_timer_start(void)
{
	/*
	 * Force a complete re-evaluation of timer deadlines.
	 */
	x86_lcpu()->rtcDeadline = EndOfAllTime;
	timer_resync_deadlines();
}