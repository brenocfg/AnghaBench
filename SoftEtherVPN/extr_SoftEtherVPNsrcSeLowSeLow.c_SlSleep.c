#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int __int64 ;
struct TYPE_3__ {int QuadPart; } ;
typedef  int /*<<< orphan*/  PKTIMER ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  KTIMER ;

/* Variables and functions */
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KeInitializeTimerEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeSetTimerEx (int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NotificationTimer ; 
 int /*<<< orphan*/  SlFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlMalloc (int) ; 

void SlSleep(int milliSeconds)
{
	PKTIMER timer = SlMalloc(sizeof(KTIMER));
	LARGE_INTEGER duetime;

	duetime.QuadPart = (__int64)milliSeconds * -10000;
	KeInitializeTimerEx(timer, NotificationTimer);
	KeSetTimerEx(timer, duetime, 0, NULL);

	KeWaitForSingleObject(timer, Executive, KernelMode, FALSE, NULL);

	SlFree(timer);
}