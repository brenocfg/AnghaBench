#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {TYPE_1__* PacketData; } ;
struct TYPE_7__ {int /*<<< orphan*/  LoggingRecordCount; struct TYPE_7__* Client_Message; int /*<<< orphan*/ * CancelList; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/ * OldTraffic; int /*<<< orphan*/  DeviceName; struct TYPE_7__* ClientOption; scalar_t__* NicDownOnDisconnect; scalar_t__ PacketAdapter; struct TYPE_7__* Username; scalar_t__ Connection; struct TYPE_7__* Policy; scalar_t__ Cancel2; scalar_t__ Cancel1; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  lock; int /*<<< orphan*/ * Thread; struct TYPE_7__* Name; int /*<<< orphan*/ * Traffic; struct TYPE_7__* ClientAuth; int /*<<< orphan*/  ClientK; int /*<<< orphan*/ * ClientX; int /*<<< orphan*/ * DelayedPacketList; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ PKT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCounter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreePacket (TYPE_2__*) ; 
 int /*<<< orphan*/  FreePacketAdapter (scalar_t__) ; 
 int /*<<< orphan*/  FreeTraffic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseCancel (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseCancelList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseConnection (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnixVLanSetState (int /*<<< orphan*/ ,int) ; 

void CleanupSession(SESSION *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// Release the delayed packet list
	if (s->DelayedPacketList != NULL)
	{
		UINT i;
		for (i = 0;i < LIST_NUM(s->DelayedPacketList);i++)
		{
			PKT *p = LIST_DATA(s->DelayedPacketList, i);

			Free(p->PacketData);
			FreePacket(p);
		}

		ReleaseList(s->DelayedPacketList);
	}

	// Release the client connection options
	if (s->ClientOption != NULL)
	{
		Free(s->ClientOption);
	}

	// Release the client authentication data
	if (s->ClientAuth != NULL)
	{
		if (s->ClientAuth->ClientX != NULL)
		{
			FreeX(s->ClientAuth->ClientX);
		}
		if (s->ClientAuth->ClientX != NULL)
		{
			FreeK(s->ClientAuth->ClientK);
		}
		Free(s->ClientAuth);
	}

	FreeTraffic(s->Traffic);
	Free(s->Name);

	if (s->Thread != NULL)
	{
		ReleaseThread(s->Thread);
	}

	DeleteLock(s->lock);

	ReleaseEvent(s->HaltEvent);

	if (s->Cancel1)
	{
		ReleaseCancel(s->Cancel1);
	}

	if (s->Cancel2)
	{
		ReleaseCancel(s->Cancel2);
	}

	if (s->Policy)
	{
		Free(s->Policy);
	}

	if (s->Connection)
	{
		ReleaseConnection(s->Connection);
	}

	Free(s->Username);

	if (s->PacketAdapter)
	{
		FreePacketAdapter(s->PacketAdapter);
	}

#ifdef OS_UNIX
	if (s->NicDownOnDisconnect != NULL && *s->NicDownOnDisconnect)
	{
		UnixVLanSetState(s->ClientOption->DeviceName, false);
	}
#endif

	if (s->OldTraffic != NULL)
	{
		FreeTraffic(s->OldTraffic);
	}

	DeleteLock(s->TrafficLock);

	if (s->CancelList != NULL)
	{
		ReleaseCancelList(s->CancelList);
	}

	if (s->Client_Message != NULL)
	{
		Free(s->Client_Message);
	}

	DeleteCounter(s->LoggingRecordCount);

	Free(s);
}