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
typedef  int /*<<< orphan*/  tmrHw_INTERRUPT_STATUS_e ;
typedef  size_t tmrHw_ID_t ;
struct TYPE_2__ {scalar_t__ InterruptStatus; } ;

/* Variables and functions */
 TYPE_1__* pTmrHw ; 
 int /*<<< orphan*/  tmrHw_INTERRUPT_STATUS_SET ; 
 int /*<<< orphan*/  tmrHw_INTERRUPT_STATUS_UNSET ; 

tmrHw_INTERRUPT_STATUS_e tmrHw_getInterruptStatus(tmrHw_ID_t timerId	/*  [ IN ] Timer id */
) {
	if (pTmrHw[timerId].InterruptStatus) {
		return tmrHw_INTERRUPT_STATUS_SET;
	} else {
		return tmrHw_INTERRUPT_STATUS_UNSET;
	}
}