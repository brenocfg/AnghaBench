#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
struct TYPE_14__ {scalar_t__ AdditionalConnectionFailedCounter; scalar_t__ LastCounterResetTick; int /*<<< orphan*/  ConnectingThreads; int /*<<< orphan*/  CurrentNumConnection; } ;
struct TYPE_13__ {scalar_t__ LastTryAddConnectTime; TYPE_3__* Connection; } ;
struct TYPE_12__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ THREAD ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ CONNECTION ;

/* Variables and functions */
 scalar_t__ ADDITIONAL_CONNECTION_COUNTER_RESET_INTERVAL ; 
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int ClientAdditionalConnect (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Dec (int /*<<< orphan*/ ) ; 
 scalar_t__ Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoticeThreadInit (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseThread (TYPE_1__*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void ClientAdditionalThread(THREAD *t, void *param)
{
	SESSION *s;
	CONNECTION *c;
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return;
	}

	s = (SESSION *)param;

	s->LastTryAddConnectTime = Tick64();

	c = s->Connection;
	// Increment of connection counter
	Inc(c->CurrentNumConnection);
	LockList(c->ConnectingThreads);
	{
		// Add to processing thread
		Add(c->ConnectingThreads, t);
		AddRef(t->ref);
	}
	UnlockList(c->ConnectingThreads);

	// Notify the completion of initialization
	NoticeThreadInit(t);

	Debug("Additional Connection #%u\n", Count(c->CurrentNumConnection));

	// Put an additional connection
	if (ClientAdditionalConnect(c, t) == false)
	{
		// Decrement the counter which is currently processing
		Dec(c->CurrentNumConnection);

		if (c->AdditionalConnectionFailedCounter == 0)
		{
			c->LastCounterResetTick = Tick64();
		}

		c->AdditionalConnectionFailedCounter++;

		if ((c->LastCounterResetTick + (UINT64)ADDITIONAL_CONNECTION_COUNTER_RESET_INTERVAL) <= Tick64())
		{
			// Reset the number of failures periodically
			c->AdditionalConnectionFailedCounter = 0;
			c->LastCounterResetTick = Tick64();
		}
	}
	else
	{
		s->LastTryAddConnectTime = Tick64();
		c->AdditionalConnectionFailedCounter = 0;
		c->LastCounterResetTick = Tick64();
	}

	// Remove from the processing thread
	LockList(c->ConnectingThreads);
	{
		// Remove from the processing thread
		if (Delete(c->ConnectingThreads, t))
		{
			ReleaseThread(t);
		}
	}
	UnlockList(c->ConnectingThreads);
	ReleaseSession(s);
}