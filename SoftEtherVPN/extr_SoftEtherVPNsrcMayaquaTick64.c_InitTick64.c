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
struct TYPE_3__ {int /*<<< orphan*/  Thread; int /*<<< orphan*/  AdjustTime; int /*<<< orphan*/  TickLock; } ;
typedef  int /*<<< orphan*/  TICK64 ;

/* Variables and functions */
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tick64Thread ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  halt_tick_event ; 
 TYPE_1__* tk64 ; 

void InitTick64()
{
	if (tk64 != NULL)
	{
		// Already initialized
		return;
	}

	halt_tick_event = NewEvent();

	// Initialize the structure
	tk64 = ZeroMalloc(sizeof(TICK64));
	tk64->TickLock = NewLock();
	tk64->AdjustTime = NewList(NULL);

	// Creating a thread
	tk64->Thread = NewThread(Tick64Thread, NULL);
	WaitThreadInit(tk64->Thread);
}