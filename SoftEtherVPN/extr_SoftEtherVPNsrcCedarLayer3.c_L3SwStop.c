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
struct TYPE_3__ {int Active; int Halt; int /*<<< orphan*/  lock; int /*<<< orphan*/ * Thread; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ L3SW ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void L3SwStop(L3SW *s)
{
	THREAD *t = NULL;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	Lock(s->lock);
	{
		if (s->Active == false)
		{
			Unlock(s->lock);
			return;
		}

		s->Halt = true;

		t = s->Thread;

		s->Active = false;
	}
	Unlock(s->lock);

	WaitThread(t, INFINITE);
	ReleaseThread(t);
}