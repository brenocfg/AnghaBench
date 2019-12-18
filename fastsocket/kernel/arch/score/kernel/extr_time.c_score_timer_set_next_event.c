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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_TIMER0_CTRL ; 
 int /*<<< orphan*/  P_TIMER0_PRELOAD ; 
 unsigned long TMR_ENABLE ; 
 unsigned long TMR_IE_ENABLE ; 
 unsigned long TMR_M_PERIODIC ; 
 unsigned long inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int score_timer_set_next_event(unsigned long delta,
		struct clock_event_device *evdev)
{
	outl((TMR_M_PERIODIC | TMR_IE_ENABLE), P_TIMER0_CTRL);
	outl(delta, P_TIMER0_PRELOAD);
	outl(inl(P_TIMER0_CTRL) | TMR_ENABLE, P_TIMER0_CTRL);

	return 0;
}