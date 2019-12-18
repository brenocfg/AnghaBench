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
struct TYPE_2__ {scalar_t__ xLpIndex; } ;
typedef  scalar_t__ HvLpIndex ;
typedef  size_t HvLpEvent_Type ;

/* Variables and functions */
 int /*<<< orphan*/  HvCallEvent_openLpEventPath (scalar_t__,size_t) ; 
 size_t HvLpEvent_Type_NumTypes ; 
 TYPE_1__ itLpNaca ; 
 scalar_t__* lpEventHandler ; 
 int /*<<< orphan*/ * lpEventHandlerPaths ; 

int HvLpEvent_openPath(HvLpEvent_Type eventType, HvLpIndex lpIndex)
{
	if ((eventType < HvLpEvent_Type_NumTypes) &&
			lpEventHandler[eventType]) {
		if (lpIndex == 0)
			lpIndex = itLpNaca.xLpIndex;
		HvCallEvent_openLpEventPath(lpIndex, eventType);
		++lpEventHandlerPaths[eventType];
		return 0;
	}
	return 1;
}