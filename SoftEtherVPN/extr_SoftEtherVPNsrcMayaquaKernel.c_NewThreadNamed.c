#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int PoolThread; int /*<<< orphan*/  ref; int /*<<< orphan*/  Name; void* release_event; struct TYPE_9__* PoolHostThread; int /*<<< orphan*/  PoolWaitList; void* init_finished_event; int /*<<< orphan*/ * pData; void* param; int /*<<< orphan*/ * thread_proc; } ;
struct TYPE_8__ {void* InitFinishEvent; void* Event; TYPE_2__* Thread; int /*<<< orphan*/ * ThreadProc; } ;
typedef  int /*<<< orphan*/  THREAD_PROC ;
typedef  TYPE_1__ THREAD_POOL_DATA ;
typedef  TYPE_2__ THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  LockSk (int /*<<< orphan*/ ) ; 
 void* NewEvent () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewRef () ; 
 TYPE_2__* NewThreadInternal (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* Pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (void*) ; 
 int /*<<< orphan*/  ThreadPoolProc ; 
 int /*<<< orphan*/  UnlockSk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInitInternal (TYPE_2__*) ; 
 void* ZeroMalloc (int) ; 
 int /*<<< orphan*/  current_num_thread ; 
 int /*<<< orphan*/  thread_count ; 
 int /*<<< orphan*/  thread_pool ; 

THREAD *NewThreadNamed(THREAD_PROC *thread_proc, void *param, char *name)
{
	THREAD *host = NULL;
	THREAD_POOL_DATA *pd = NULL;
	THREAD *ret;
	// Validate arguments
	if (thread_proc == NULL)
	{
		return NULL;
	}

	Inc(thread_count);

	LockSk(thread_pool);
	{
		// Examine whether there is a thread that is currently vacant in the pool
		host = Pop(thread_pool);
	}
	UnlockSk(thread_pool);

	if (host == NULL)
	{
		// Create a new thread because a vacant thread is not found
		pd = ZeroMalloc(sizeof(THREAD_POOL_DATA));
		pd->Event = NewEvent();
		pd->InitFinishEvent = NewEvent();
		host = NewThreadInternal(ThreadPoolProc, pd);
		WaitThreadInitInternal(host);
	}
	else
	{
		pd = (THREAD_POOL_DATA *)host->param;
	}

	// Creating a thread pool
	ret = ZeroMalloc(sizeof(THREAD));
	ret->ref = NewRef();
	ret->thread_proc = thread_proc;
	ret->param = param;
	ret->pData = NULL;
	ret->init_finished_event = NewEvent();
	ret->PoolThread = true;
	ret->PoolWaitList = NewList(NULL);
	ret->PoolHostThread = host;
	ret->release_event = NewEvent();

	if (IsEmptyStr(name) == false)
	{
		ret->Name = CopyStr(name);
	}

	// Run
	pd->ThreadProc = thread_proc;
	pd->Thread = ret;
	AddRef(ret->ref);

	Set(pd->Event);

	Wait(pd->InitFinishEvent, INFINITE);

	current_num_thread++;

//	Debug("current_num_thread = %u\n", current_num_thread);

	return ret;
}