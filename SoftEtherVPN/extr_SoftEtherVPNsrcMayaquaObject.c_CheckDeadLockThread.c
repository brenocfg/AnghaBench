#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int Unlocked; int /*<<< orphan*/  Lock; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ DEADCHECK ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void CheckDeadLockThread(THREAD *t, void *param)
{
	DEADCHECK *c = (DEADCHECK *)param;

	if (t == NULL || c == NULL)
	{
		return;
	}

	NoticeThreadInit(t);

	Lock(c->Lock);
	Unlock(c->Lock);
	c->Unlocked = true;
}