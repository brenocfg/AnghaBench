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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  tmrHw_RATE_t ;
typedef  size_t tmrHw_ID_t ;
struct TYPE_2__ {int /*<<< orphan*/  Control; } ;

/* Variables and functions */
 int /*<<< orphan*/  ResetTimer (size_t) ; 
 TYPE_1__* pTmrHw ; 
 int /*<<< orphan*/  tmrHw_CONTROL_ONESHOT ; 
 int /*<<< orphan*/  tmrHw_CONTROL_PERIODIC ; 
 int /*<<< orphan*/  tmrHw_CONTROL_PRESCALE_1 ; 
 int /*<<< orphan*/  tmrHw_CONTROL_PRESCALE_16 ; 
 int /*<<< orphan*/  tmrHw_CONTROL_PRESCALE_256 ; 
 int /*<<< orphan*/  tmrHw_HIGH_RESOLUTION_CLOCK ; 
 int /*<<< orphan*/  tmrHw_LOW_RESOLUTION_CLOCK ; 
 int /*<<< orphan*/  tmrHw_divide (int /*<<< orphan*/ ,int) ; 

tmrHw_RATE_t tmrHw_setFreeRunningTimer(tmrHw_ID_t timerId,	/*  [ IN ] Timer Id */
				       uint32_t divider	/*  [ IN ] Dividing the clock frequency */
) {
	uint32_t scale = 0;

	ResetTimer(timerId);
	/* Set timer as free running mode */
	pTmrHw[timerId].Control &= ~tmrHw_CONTROL_PERIODIC;
	pTmrHw[timerId].Control &= ~tmrHw_CONTROL_ONESHOT;

	if (divider >= 64) {
		pTmrHw[timerId].Control |= tmrHw_CONTROL_PRESCALE_256;
		scale = 256;
	} else if (divider >= 8) {
		pTmrHw[timerId].Control |= tmrHw_CONTROL_PRESCALE_16;
		scale = 16;
	} else {
		pTmrHw[timerId].Control |= tmrHw_CONTROL_PRESCALE_1;
		scale = 1;
	}

	if (timerId == 0 || timerId == 1) {
		return tmrHw_divide(tmrHw_LOW_RESOLUTION_CLOCK, scale);
	} else if (timerId == 2 || timerId == 3) {
		return tmrHw_divide(tmrHw_HIGH_RESOLUTION_CLOCK, scale);
	}

	return 0;
}