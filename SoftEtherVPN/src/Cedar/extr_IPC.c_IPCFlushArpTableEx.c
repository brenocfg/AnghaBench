#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/ * ArpTable; } ;
struct TYPE_8__ {int Resolved; scalar_t__ ExpireTime; scalar_t__ GiveupTime; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ IPC_ARP ;
typedef  TYPE_2__ IPC ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IPCFreeARP (TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 

void IPCFlushArpTableEx(IPC *ipc, UINT64 now)
{
	UINT i;
	LIST *o = NULL;
	// Validate arguments
	if (ipc == NULL)
	{
		return;
	}
	if (now == 0)
	{
		now = Tick64();
	}

	for (i = 0;i < LIST_NUM(ipc->ArpTable);i++)
	{
		IPC_ARP *a = LIST_DATA(ipc->ArpTable, i);
		bool b = false;

		if (a->Resolved && a->ExpireTime <= now)
		{
			b = true;
		}
		else if (a->Resolved == false && a->GiveupTime <= now)
		{
			b = true;
		}

		if (b)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Add(o, a);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			IPC_ARP *a = LIST_DATA(o, i);

			IPCFreeARP(a);

			Delete(ipc->ArpTable, a);
		}

		ReleaseList(o);
	}
}