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
struct TYPE_2__ {int CurrentValue; int InterruptClear; scalar_t__ RawInterruptStatus; int /*<<< orphan*/  Control; scalar_t__ BackgroundLoad; scalar_t__ LoadValue; } ;

/* Variables and functions */
 TYPE_1__* pTmrHw ; 
 int /*<<< orphan*/  tmrHw_CONTROL_32BIT ; 

__attribute__((used)) static void ResetTimer(tmrHw_ID_t timerId	/*  [ IN ] Timer Id */
) {
	/* Reset timer */
	pTmrHw[timerId].LoadValue = 0;
	pTmrHw[timerId].CurrentValue = 0xFFFFFFFF;
	pTmrHw[timerId].Control = 0;
	pTmrHw[timerId].BackgroundLoad = 0;
	/* Always configure as a 32 bit timer */
	pTmrHw[timerId].Control |= tmrHw_CONTROL_32BIT;
	/* Clear interrupt only if raw status interrupt is set */
	if (pTmrHw[timerId].RawInterruptStatus) {
		pTmrHw[timerId].InterruptClear = 0xFFFFFFFF;
	}
}