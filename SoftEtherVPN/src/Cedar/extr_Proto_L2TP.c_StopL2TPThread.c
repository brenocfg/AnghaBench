#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* IkeServer; int /*<<< orphan*/  ThreadList; } ;
struct TYPE_10__ {int HasThread; int /*<<< orphan*/  SessionId2; int /*<<< orphan*/  SessionId1; int /*<<< orphan*/ * TubeSend; int /*<<< orphan*/ * TubeRecv; int /*<<< orphan*/ * Thread; int /*<<< orphan*/ * EtherIP; scalar_t__ IsV3; } ;
struct TYPE_9__ {int /*<<< orphan*/  TunnelId2; int /*<<< orphan*/  TunnelId1; } ;
struct TYPE_8__ {int /*<<< orphan*/  ThreadList; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ L2TP_TUNNEL ;
typedef  TYPE_3__ L2TP_SESSION ;
typedef  TYPE_4__ L2TP_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  AddThreadToThreadList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEtherIPServer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseTube (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TubeDisconnect (int /*<<< orphan*/ *) ; 

void StopL2TPThread(L2TP_SERVER *l2tp, L2TP_TUNNEL *t, L2TP_SESSION *s)
{
	THREAD *thread;
	// Validate arguments
	if (l2tp == NULL || t == NULL || s == NULL)
	{
		return;
	}

	if (s->IsV3)
	{
		// Process the L2TPv3
		if (s->EtherIP != NULL)
		{
			// Release the EtherIP server
			ReleaseEtherIPServer(s->EtherIP);
			s->EtherIP = NULL;
		}
		return;
	}

	if (s->HasThread == false)
	{
		return;
	}
	thread = s->Thread;
	s->Thread = NULL;
	s->HasThread = false;

	// Disconnect the tube
	TubeDisconnect(s->TubeRecv);
	TubeDisconnect(s->TubeSend);

	// Release the tube
	ReleaseTube(s->TubeRecv);
	ReleaseTube(s->TubeSend);

	s->TubeRecv = NULL;
	s->TubeSend = NULL;

	// Pass the thread to termination list
	if (l2tp->IkeServer == NULL)
	{
		AddThreadToThreadList(l2tp->ThreadList, thread);
	}
	else
	{
		AddThreadToThreadList(l2tp->IkeServer->ThreadList, thread);
	}

	Debug("Thread Stopped for Session %u/%u on Tunnel %u/%u\n",
		s->SessionId1, s->SessionId2, t->TunnelId1, t->TunnelId2);

	// Release the thread
	ReleaseThread(thread);
}