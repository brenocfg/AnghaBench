#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int Halt; int /*<<< orphan*/  ThreadList; int /*<<< orphan*/  TunnelList; int /*<<< orphan*/  HaltCompletedEvent; int /*<<< orphan*/  SockEvent; } ;
struct TYPE_6__ {int /*<<< orphan*/  SessionList; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  int /*<<< orphan*/  L2TP_SESSION ;
typedef  TYPE_2__ L2TP_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopL2TPThread (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopThreadList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void StopL2TPServer(L2TP_SERVER *l2tp, bool no_wait)
{
	// Validate arguments
	if (l2tp == NULL)
	{
		return;
	}
	if (l2tp->Halt)
	{
		return;
	}

	// Begin to shut down
	l2tp->Halt = true;
	Debug("Shutting down L2TP Server...\n");

	// Hit the event
	SetSockEvent(l2tp->SockEvent);

	if (no_wait == false)
	{
		// Wait until complete stopping all tunnels
		Wait(l2tp->HaltCompletedEvent, INFINITE);
	}
	else
	{
		UINT i, j;
		// Kill the thread of all sessions
		for (i = 0;i < LIST_NUM(l2tp->TunnelList);i++)
		{
			L2TP_TUNNEL *t = LIST_DATA(l2tp->TunnelList, i);

			for (j = 0;j < LIST_NUM(t->SessionList);j++)
			{
				L2TP_SESSION *s = LIST_DATA(t->SessionList, j);

				StopL2TPThread(l2tp, t, s);
			}
		}
	}

	// Thread stop
	Debug("Stopping all L2TP PPP Threads...\n");
	StopThreadList(l2tp->ThreadList);
	Debug("L2TP Server Shutdown Completed.\n");
}