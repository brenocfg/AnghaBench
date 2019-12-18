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
struct TYPE_2__ {int /*<<< orphan*/  InterruptStatus; int /*<<< orphan*/  RawInterruptStatus; int /*<<< orphan*/  InterruptClear; int /*<<< orphan*/  Control; int /*<<< orphan*/  BackgroundLoad; int /*<<< orphan*/  LoadValue; } ;

/* Variables and functions */
 TYPE_1__* pTmrHw ; 
 int stub1 (char const*) ; 
 int stub2 (char const*,...) ; 
 int stub3 (char const*,...) ; 
 int stub4 (char const*,...) ; 
 int stub5 (char const*,...) ; 
 int stub6 (char const*,...) ; 
 int stub7 (char const*,...) ; 

void tmrHw_printDebugInfo(tmrHw_ID_t timerId,	/*  [ IN ] Timer id */
			  int (*fpPrint) (const char *, ...)	/*  [ IN ] Print callback function */
) {
	(*fpPrint) ("Displaying register contents \n\n");
	(*fpPrint) ("Timer %d: Load value              0x%X\n", timerId,
		    pTmrHw[timerId].LoadValue);
	(*fpPrint) ("Timer %d: Background load value   0x%X\n", timerId,
		    pTmrHw[timerId].BackgroundLoad);
	(*fpPrint) ("Timer %d: Control                 0x%X\n", timerId,
		    pTmrHw[timerId].Control);
	(*fpPrint) ("Timer %d: Interrupt clear         0x%X\n", timerId,
		    pTmrHw[timerId].InterruptClear);
	(*fpPrint) ("Timer %d: Interrupt raw interrupt 0x%X\n", timerId,
		    pTmrHw[timerId].RawInterruptStatus);
	(*fpPrint) ("Timer %d: Interrupt status        0x%X\n", timerId,
		    pTmrHw[timerId].InterruptStatus);
}