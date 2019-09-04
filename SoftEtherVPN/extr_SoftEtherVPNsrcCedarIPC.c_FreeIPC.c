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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  IPv4ReceivedQueue; int /*<<< orphan*/  ArpTable; int /*<<< orphan*/  Interrupt; int /*<<< orphan*/  Cedar; struct TYPE_4__* Policy; int /*<<< orphan*/  Sock; int /*<<< orphan*/  FlushList; } ;
typedef  int /*<<< orphan*/  IPC_ARP ;
typedef  TYPE_1__ IPC ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeInterruptManager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeTubeFlushList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPCFreeARP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 

void FreeIPC(IPC *ipc)
{
	UINT i;
	// Validate arguments
	if (ipc == NULL)
	{
		return;
	}

	FreeTubeFlushList(ipc->FlushList);

	Disconnect(ipc->Sock);
	ReleaseSock(ipc->Sock);

	if (ipc->Policy != NULL)
	{
		Free(ipc->Policy);
	}

	ReleaseCedar(ipc->Cedar);

	FreeInterruptManager(ipc->Interrupt);

	for (i = 0;i < LIST_NUM(ipc->ArpTable);i++)
	{
		IPC_ARP *a = LIST_DATA(ipc->ArpTable, i);
		IPCFreeARP(a);
	}

	ReleaseList(ipc->ArpTable);

	while (true)
	{
		BLOCK *b = GetNext(ipc->IPv4ReceivedQueue);
		if (b == NULL)
		{
			break;
		}

		FreeBlock(b);
	}

	ReleaseQueue(ipc->IPv4ReceivedQueue);

	Free(ipc);
}