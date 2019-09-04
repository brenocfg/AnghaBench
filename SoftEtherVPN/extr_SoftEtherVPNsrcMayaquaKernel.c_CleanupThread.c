#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* Name; int /*<<< orphan*/  PoolWaitList; int /*<<< orphan*/  release_event; int /*<<< orphan*/  init_finished_event; } ;
typedef  TYPE_1__ THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_num_thread ; 

void CleanupThread(THREAD *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	ReleaseEvent(t->init_finished_event);
	ReleaseEvent(t->release_event);
	ReleaseList(t->PoolWaitList);

	if (t->Name != NULL)
	{
		Free(t->Name);
	}

	Free(t);

	current_num_thread--;
	//Debug("current_num_thread = %u\n", current_num_thread);
}