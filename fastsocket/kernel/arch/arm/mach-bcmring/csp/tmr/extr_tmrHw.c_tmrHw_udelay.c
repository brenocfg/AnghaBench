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
typedef  unsigned long tmrHw_RATE_t ;
typedef  int /*<<< orphan*/  tmrHw_ID_t ;
typedef  unsigned long tmrHw_COUNT_t ;

/* Variables and functions */
 unsigned long tmrHw_GetCurrentCount (int /*<<< orphan*/ ) ; 
 unsigned long tmrHw_divide (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tmrHw_getCountRate (int /*<<< orphan*/ ) ; 

void tmrHw_udelay(tmrHw_ID_t timerId,	/*  [ IN ] Timer id */
		  unsigned long usecs /*  [ IN ] usec to delay */
) {
	tmrHw_RATE_t usec_tick_rate;
	tmrHw_COUNT_t start_time;
	tmrHw_COUNT_t delta_time;

	start_time = tmrHw_GetCurrentCount(timerId);
	usec_tick_rate = tmrHw_divide(tmrHw_getCountRate(timerId), 1000000);
	delta_time = usecs * usec_tick_rate;

	/* Busy wait */
	while (delta_time > (tmrHw_GetCurrentCount(timerId) - start_time))
		;
}