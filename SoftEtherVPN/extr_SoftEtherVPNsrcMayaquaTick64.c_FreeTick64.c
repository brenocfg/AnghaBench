#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int Halt; int /*<<< orphan*/  TickLock; int /*<<< orphan*/  AdjustTime; int /*<<< orphan*/  Thread; } ;
typedef  TYPE_1__ ADJUST_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * halt_tick_event ; 
 TYPE_1__* tk64 ; 

void FreeTick64()
{
	UINT i;
	if (tk64 == NULL)
	{
		// Uninitialized
		return;
	}

	// Termination process
	tk64->Halt = true;
	Set(halt_tick_event);
	WaitThread(tk64->Thread, INFINITE);
	ReleaseThread(tk64->Thread);

	// Releasing process
	for (i = 0;i < LIST_NUM(tk64->AdjustTime);i++)
	{
		ADJUST_TIME *t = LIST_DATA(tk64->AdjustTime, i);
		Free(t);
	}
	ReleaseList(tk64->AdjustTime);
	DeleteLock(tk64->TickLock);
	Free(tk64);
	tk64 = NULL;

	ReleaseEvent(halt_tick_event);
	halt_tick_event = NULL;
}