#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_11__ {char* Name; int Stopped; int PoolHalting; int /*<<< orphan*/  release_event; TYPE_1__* ref; int /*<<< orphan*/  PoolWaitList; int /*<<< orphan*/  ThreadId; int /*<<< orphan*/  param; } ;
struct TYPE_10__ {TYPE_3__* Thread; int /*<<< orphan*/  (* ThreadProc ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * InitFinishEvent; int /*<<< orphan*/  Event; } ;
struct TYPE_9__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_2__ THREAD_POOL_DATA ;
typedef  TYPE_3__ THREAD ;
typedef  int /*<<< orphan*/  EVENT ;

/* Variables and functions */
 int Count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 int INFINITE ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockSk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsRestoreThreadPriority () ; 
 int /*<<< orphan*/  NoticeThreadInitInternal (TYPE_3__*) ; 
 int /*<<< orphan*/  Push (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (TYPE_3__*) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetThreadName (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ThreadId () ; 
 int /*<<< orphan*/ ** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockSk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_count ; 
 int /*<<< orphan*/  thread_pool ; 

void ThreadPoolProc(THREAD *t, void *param)
{
	THREAD_POOL_DATA *pd;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	pd = (THREAD_POOL_DATA *)param;

	NoticeThreadInitInternal(t);

	while (true)
	{
		THREAD *thread;
		UINT i, num;
		EVENT **ee;

		// Wait for the next job
		Wait(pd->Event, INFINITE);

		if (pd->ThreadProc == NULL)
		{
			// Stop the pool thread
			break;
		}

		thread = pd->Thread;
		thread->ThreadId = ThreadId();

		// Initialization is completed
		Set(pd->InitFinishEvent);

		// Set the thread name
		if (thread->Name != NULL)
		{
			SetThreadName(thread->ThreadId, thread->Name, thread->param);
		}
		else
		{
			SetThreadName(thread->ThreadId, "Unknown", 0);
		}

		// Run the thread procedure
		pd->ThreadProc(pd->Thread, thread->param);

		// Set the thread name
		SetThreadName(thread->ThreadId, NULL, 0);

		pd->Thread->Stopped = true;

		thread->PoolHalting = true;

		// Set the waiting event list
		LockList(thread->PoolWaitList);
		{
			num = LIST_NUM(thread->PoolWaitList);
			ee = ToArray(thread->PoolWaitList);

			DeleteAll(thread->PoolWaitList);
		}
		UnlockList(thread->PoolWaitList);

		for (i = 0;i < num;i++)
		{
			EVENT *e = ee[i];

			Set(e);
			ReleaseEvent(e);
		}

		Free(ee);

		while (true)
		{
			if (Count(thread->ref->c) <= 1)
			{
				break;
			}

			Wait(thread->release_event, 256);
		}

		ReleaseThread(thread);

#ifdef	OS_WIN32
		// For Win32: Recover the priority of the thread
		MsRestoreThreadPriority();
#endif	// OS_WIN32

		// Register the thread itself to the thread pool
		LockSk(thread_pool);
		{
			Push(thread_pool, t);
		}
		UnlockSk(thread_pool);

		Dec(thread_count);
	}
}