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
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int Unlocked; int /*<<< orphan*/  Timeout; int /*<<< orphan*/ * Lock; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  LOCK ;
typedef  TYPE_1__ DEADCHECK ;

/* Variables and functions */
 int /*<<< orphan*/  AbortExitEx (char*) ; 
 int /*<<< orphan*/  CheckDeadLockThread ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void CheckDeadLock(LOCK *lock, UINT timeout, char *name)
{
	DEADCHECK c;
	THREAD *t;
	char msg[MAX_PATH];

	if (lock == NULL)
	{
		return;
	}
	if (name == NULL)
	{
		name = "Unknown";
	}

	Format(msg, sizeof(msg), "error: CheckDeadLock() Failed: %s\n", name);

	Zero(&c, sizeof(c));
	c.Lock = lock;
	c.Timeout = timeout;
	c.Unlocked = false;

	t = NewThread(CheckDeadLockThread, &c);
	WaitThreadInit(t);
	if (WaitThread(t, timeout) == false)
	{
		if (c.Unlocked == false)
		{
			// Deadlock occured
			AbortExitEx(msg);
		}
		else
		{
			WaitThread(t, INFINITE);
		}
	}

	ReleaseThread(t);
}