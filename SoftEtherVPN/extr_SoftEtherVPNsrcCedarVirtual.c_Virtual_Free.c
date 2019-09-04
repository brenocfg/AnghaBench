#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int Active; int /*<<< orphan*/  Logger; int /*<<< orphan*/  Cancel; int /*<<< orphan*/ * SendQueue; } ;
typedef  TYPE_1__ VH ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  FreeArpTable (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeArpWaitTable (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeDhcpServer (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeIpCombineList (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeIpWaitTable (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeNat (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_1__*) ; 

void Virtual_Free(VH *v)
{
	// Release the DHCP server
	FreeDhcpServer(v);

	// NAT release
	FreeNat(v);

	LockVirtual(v);
	{
		// Release the IP combining list
		FreeIpCombineList(v);

		// Release the IP waiting table
		FreeIpWaitTable(v);

		// Release the ARP waiting table
		FreeArpWaitTable(v);

		// Release the ARP table
		FreeArpTable(v);

		// Release the transmission queue
		LockQueue(v->SendQueue);
		{
			BLOCK *block;

			// Release all queues
			while (block = GetNext(v->SendQueue))
			{
				FreeBlock(block);
			}
		}
		UnlockQueue(v->SendQueue);
		ReleaseQueue(v->SendQueue);
		v->SendQueue = NULL;

		// Release the cancel object
		ReleaseCancel(v->Cancel);

		v->Active = false;
	}
	UnlockVirtual(v);

	// Release the logger
	FreeLog(v->Logger);
}