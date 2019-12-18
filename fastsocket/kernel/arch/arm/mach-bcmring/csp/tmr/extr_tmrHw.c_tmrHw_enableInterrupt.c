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
typedef  size_t tmrHw_ID_t ;
struct TYPE_2__ {int /*<<< orphan*/  Control; } ;

/* Variables and functions */
 TYPE_1__* pTmrHw ; 
 int /*<<< orphan*/  tmrHw_CONTROL_INTERRUPT_ENABLE ; 

void tmrHw_enableInterrupt(tmrHw_ID_t timerId	/*  [ IN ] Timer id */
) {
	pTmrHw[timerId].Control |= tmrHw_CONTROL_INTERRUPT_ENABLE;
}