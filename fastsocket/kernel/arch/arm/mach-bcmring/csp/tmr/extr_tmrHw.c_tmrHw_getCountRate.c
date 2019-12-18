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
struct TYPE_2__ {int Control; } ;

/* Variables and functions */
 TYPE_1__* pTmrHw ; 
 int /*<<< orphan*/  tmrHw_ASSERT (int /*<<< orphan*/ ) ; 
#define  tmrHw_CONTROL_PRESCALE_1 130 
#define  tmrHw_CONTROL_PRESCALE_16 129 
#define  tmrHw_CONTROL_PRESCALE_256 128 
 int tmrHw_CONTROL_PRESCALE_MASK ; 
 int /*<<< orphan*/  tmrHw_HIGH_RESOLUTION_CLOCK ; 
 int /*<<< orphan*/  tmrHw_LOW_RESOLUTION_CLOCK ; 
 int /*<<< orphan*/  tmrHw_divide (int /*<<< orphan*/ ,int) ; 

tmrHw_RATE_t tmrHw_getCountRate(tmrHw_ID_t timerId	/*  [ IN ] Timer id */
) {
	uint32_t divider = 0;

	switch (pTmrHw[timerId].Control & tmrHw_CONTROL_PRESCALE_MASK) {
	case tmrHw_CONTROL_PRESCALE_1:
		divider = 1;
		break;
	case tmrHw_CONTROL_PRESCALE_16:
		divider = 16;
		break;
	case tmrHw_CONTROL_PRESCALE_256:
		divider = 256;
		break;
	default:
		tmrHw_ASSERT(0);
	}

	if (timerId == 0 || timerId == 1) {
		return tmrHw_divide(tmrHw_LOW_RESOLUTION_CLOCK, divider);
	} else {
		return tmrHw_divide(tmrHw_HIGH_RESOLUTION_CLOCK, divider);
	}
	return 0;
}