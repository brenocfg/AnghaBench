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
 int TIMER0bit ; 
 int TIMER1bit ; 
 int TIMER_STATUS_TIMIL0 ; 
 int TIMER_STATUS_TIMIL1 ; 
 int TIMER_STATUS_TOVF0 ; 
 int TIMER_STATUS_TOVF1 ; 
 int TIMER_STATUS_TRUN0 ; 
 int TIMER_STATUS_TRUN1 ; 
 int /*<<< orphan*/  disable_gptimers (int) ; 
 int /*<<< orphan*/  set_gptimer_status (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bfin_t350mcqb_stop_timers(void)
{
	disable_gptimers(TIMER0bit | TIMER1bit);

	set_gptimer_status(0, TIMER_STATUS_TRUN0 | TIMER_STATUS_TRUN1 |
				TIMER_STATUS_TIMIL0 | TIMER_STATUS_TIMIL1 |
				 TIMER_STATUS_TOVF0 | TIMER_STATUS_TOVF1);

}