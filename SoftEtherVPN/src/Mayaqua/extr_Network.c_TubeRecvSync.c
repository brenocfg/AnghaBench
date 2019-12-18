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
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Event; int /*<<< orphan*/  Queue; } ;
typedef  int /*<<< orphan*/  TUBEDATA ;
typedef  TYPE_1__ TUBE ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetTubeSockEvent (TYPE_1__*) ; 
 scalar_t__ INFINITE ; 
 int IsTubeConnected (TYPE_1__*) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WaitSockEvent (int /*<<< orphan*/ *,scalar_t__) ; 

TUBEDATA *TubeRecvSync(TUBE *t, UINT timeout)
{
	UINT64 start_tick, timeout_tick;
	TUBEDATA *d = NULL;
	// Validate arguments
	if (t == NULL)
	{
		return NULL;
	}

	if (IsTubeConnected(t) == false)
	{
		return NULL;
	}

	start_tick = Tick64();
	timeout_tick = start_tick + (UINT64)timeout;

	while (true)
	{
		UINT64 now = Tick64();
		UINT remain_time;
		SOCK_EVENT *e;
		UINT interval;

		d = NULL;

		if (IsTubeConnected(t) == false)
		{
			break;
		}

		LockQueue(t->Queue);
		{
			d = GetNext(t->Queue);
		}
		UnlockQueue(t->Queue);

		if (d != NULL)
		{
			break;
		}

		if (timeout != INFINITE && now >= timeout_tick)
		{
			return NULL;
		}

		remain_time = (UINT)(timeout_tick - now);

		e = GetTubeSockEvent(t);

		interval = (timeout == INFINITE ? INFINITE : remain_time);

		if (e == NULL)
		{
			Wait(t->Event, interval);
		}
		else
		{
			WaitSockEvent(e, interval);

			ReleaseSockEvent(e);
		}
	}

	return d;
}