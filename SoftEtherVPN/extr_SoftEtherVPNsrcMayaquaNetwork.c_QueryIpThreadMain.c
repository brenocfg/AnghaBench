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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int Halt; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  IntervalLastOk; int /*<<< orphan*/  IntervalLastNg; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Ip; int /*<<< orphan*/  Hostname; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ QUERYIPTHREAD ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ GetIP4Ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int IsZeroIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void QueryIpThreadMain(THREAD *thread, void *param)
{
	QUERYIPTHREAD *t = (QUERYIPTHREAD *)param;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	while (t->Halt == false)
	{
		UINT next_wait_time = 0;
		IP ip;
		bool ok = false;

		if (GetIP4Ex(&ip, t->Hostname, 5000, &t->Halt))
		{
			if (IsZeroIP(&ip) == false)
			{
				Lock(t->Lock);
				{
					Copy(&t->Ip, &ip, sizeof(IP));
				}
				Unlock(t->Lock);

				ok = true;
			}
		}

		if (ok == false)
		{
			next_wait_time = t->IntervalLastNg;
		}
		else
		{
			next_wait_time = t->IntervalLastOk;
		}

		if (t->Halt)
		{
			break;
		}

		Wait(t->HaltEvent, next_wait_time);
	}
}