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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  SendPacketList; int /*<<< orphan*/ * Ipc; int /*<<< orphan*/ * IpcConnectThread; } ;
typedef  TYPE_1__ ETHERIP_SERVER ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EtherIPLog (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 

void CleanupEtherIPServer(ETHERIP_SERVER *s)
{
	UINT i;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	EtherIPLog(s, "LE_STOP");

	if (s->IpcConnectThread != NULL)
	{
		ReleaseThread(s->IpcConnectThread);
	}

	if (s->Ipc != NULL)
	{
		FreeIPC(s->Ipc);
	}

	for (i = 0;i < LIST_NUM(s->SendPacketList);i++)
	{
		BLOCK *b = LIST_DATA(s->SendPacketList, i);

		FreeBlock(b);
	}

	ReleaseList(s->SendPacketList);

	ReleaseSockEvent(s->SockEvent);

	ReleaseCedar(s->Cedar);

	DeleteLock(s->Lock);

	Free(s);
}