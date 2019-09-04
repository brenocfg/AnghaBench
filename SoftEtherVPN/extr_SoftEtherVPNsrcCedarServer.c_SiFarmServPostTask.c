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
struct TYPE_9__ {int /*<<< orphan*/  TaskPostEvent; int /*<<< orphan*/  TaskQueue; scalar_t__ Halting; } ;
struct TYPE_8__ {int /*<<< orphan*/  CompleteEvent; int /*<<< orphan*/ * Request; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ FARM_TASK ;
typedef  TYPE_2__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

FARM_TASK *SiFarmServPostTask(FARM_MEMBER *f, PACK *request)
{
	FARM_TASK *t;
	// Validate arguments
	if (f == NULL || request == NULL)
	{
		return NULL;
	}

	t = ZeroMalloc(sizeof(FARM_TASK));
	t->CompleteEvent = NewEvent();
	t->Request = request;

	LockQueue(f->TaskQueue);
	{
		if (f->Halting)
		{
			// Halting (failure)
			UnlockQueue(f->TaskQueue);
			ReleaseEvent(t->CompleteEvent);
			Free(t);
			return NULL;
		}

		InsertQueue(f->TaskQueue, t);
	}
	UnlockQueue(f->TaskQueue);

	Set(f->TaskPostEvent);

	return t;
}