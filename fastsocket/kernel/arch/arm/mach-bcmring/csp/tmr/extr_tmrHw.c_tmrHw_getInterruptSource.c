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
typedef  int tmrHw_ID_t ;
struct TYPE_2__ {scalar_t__ InterruptStatus; } ;

/* Variables and functions */
 TYPE_1__* pTmrHw ; 
 int tmrHw_TIMER_NUM_COUNT ; 

tmrHw_ID_t tmrHw_getInterruptSource(void	/*  void */
) {
	int i;

	for (i = 0; i < tmrHw_TIMER_NUM_COUNT; i++) {
		if (pTmrHw[i].InterruptStatus) {
			return i;
		}
	}

	return 0xFFFFFFFF;
}