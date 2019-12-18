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
struct TYPE_5__ {int /*<<< orphan*/  init_finished_event; } ;
typedef  TYPE_1__ THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  KS_FREETHREAD_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSFreeThread (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 

void CleanupThreadInternal(THREAD *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	// Release of the thread
	OSFreeThread(t);

	// Release the event
	ReleaseEvent(t->init_finished_event);
	// Memory release
	Free(t);

	// KS
	KS_INC(KS_FREETHREAD_COUNT);
}