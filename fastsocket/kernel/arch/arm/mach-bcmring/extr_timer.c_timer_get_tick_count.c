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
typedef  int /*<<< orphan*/  timer_tick_count_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROF_TIMER ; 
 int /*<<< orphan*/  tmrHw_GetCurrentCount (int /*<<< orphan*/ ) ; 

timer_tick_count_t timer_get_tick_count(void)
{
	return tmrHw_GetCurrentCount(PROF_TIMER);	/* change downcounter to upcounter */
}