#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ param; } ;
struct TYPE_7__ {int /*<<< orphan*/  InitFinishEvent; int /*<<< orphan*/  Event; int /*<<< orphan*/ * ThreadProc; } ;
typedef  TYPE_1__ THREAD_POOL_DATA ;
typedef  TYPE_2__ THREAD ;

/* Variables and functions */
 scalar_t__ Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteCounter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_2__* Pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThreadInternal (TYPE_2__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 int /*<<< orphan*/  WaitThreadInternal (TYPE_2__*) ; 
 int /*<<< orphan*/ * thread_count ; 
 int /*<<< orphan*/  thread_pool ; 

void FreeThreading()
{
	while (true)
	{
		if (Count(thread_count) == 0)
		{
			break;
		}

		SleepThread(25);
	}

	while (true)
	{
		THREAD_POOL_DATA *pd;
		THREAD *t = Pop(thread_pool);

		if (t == NULL)
		{
			break;
		}

		pd = (THREAD_POOL_DATA *)t->param;

		pd->ThreadProc = NULL;
		Set(pd->Event);

		WaitThreadInternal(t);

		pd = (THREAD_POOL_DATA *)t->param;
		ReleaseEvent(pd->Event);
		ReleaseEvent(pd->InitFinishEvent);

		ReleaseThreadInternal(t);

		Free(pd);
	}

	ReleaseSk(thread_pool);

	DeleteCounter(thread_count);
	thread_count = NULL;
}