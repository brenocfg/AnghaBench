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
struct TYPE_5__ {int /*<<< orphan*/ * thread_proc; int /*<<< orphan*/  ref; void* param; int /*<<< orphan*/  init_finished_event; } ;
typedef  int /*<<< orphan*/  THREAD_PROC ;
typedef  TYPE_1__ THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  AbortExit () ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_NEWTHREAD_COUNT ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewRef () ; 
 scalar_t__ OSInitThread (TYPE_1__*) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

THREAD *NewThreadInternal(THREAD_PROC *thread_proc, void *param)
{
	THREAD *t;
	UINT retry = 0;
	// Validate arguments
	if (thread_proc == NULL)
	{
		return NULL;
	}

	// Initialize Thread object
	t = ZeroMalloc(sizeof(THREAD));
	t->init_finished_event = NewEvent();

	t->param = param;
	t->ref = NewRef();
	t->thread_proc = thread_proc;

	// Wait until the OS to initialize the thread
	while (true)
	{
		if ((retry++) > 60)
		{
			printf("\n\n*** error: new thread create failed.\n\n");
			AbortExit();
		}
		if (OSInitThread(t))
		{
			break;
		}
		SleepThread(500);
	}

	// KS
	KS_INC(KS_NEWTHREAD_COUNT);

	return t;
}