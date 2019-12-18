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
typedef  scalar_t__ uint32_t ;
typedef  size_t tmrHw_ID_t ;
struct TYPE_2__ {int Control; scalar_t__ CurrentValue; scalar_t__ BackgroundLoad; } ;

/* Variables and functions */
 TYPE_1__* pTmrHw ; 
#define  tmrHw_CONTROL_FREE_RUNNING 130 
 int tmrHw_CONTROL_MODE_MASK ; 
#define  tmrHw_CONTROL_ONESHOT 129 
#define  tmrHw_CONTROL_PERIODIC 128 
 scalar_t__ tmrHw_MAX_COUNT ; 

uint32_t tmrHw_GetCurrentCount(tmrHw_ID_t timerId	/*  [ IN ] Timer id */
) {
	/* return 32 bit timer value */
	switch (pTmrHw[timerId].Control & tmrHw_CONTROL_MODE_MASK) {
	case tmrHw_CONTROL_FREE_RUNNING:
		if (pTmrHw[timerId].CurrentValue) {
			return tmrHw_MAX_COUNT - pTmrHw[timerId].CurrentValue;
		}
		break;
	case tmrHw_CONTROL_PERIODIC:
	case tmrHw_CONTROL_ONESHOT:
		return pTmrHw[timerId].BackgroundLoad -
		    pTmrHw[timerId].CurrentValue;
	}
	return 0;
}