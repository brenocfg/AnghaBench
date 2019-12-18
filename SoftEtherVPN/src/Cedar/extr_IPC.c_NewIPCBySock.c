#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ref; } ;
struct TYPE_9__ {int /*<<< orphan*/  FlushList; int /*<<< orphan*/  IPv4ReceivedQueue; int /*<<< orphan*/  ArpTable; int /*<<< orphan*/  Interrupt; int /*<<< orphan*/  MacAddress; TYPE_1__* Sock; TYPE_3__* Cedar; } ;
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ IPC ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  IPCCmpArpTable ; 
 int /*<<< orphan*/  NewInterruptManager () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/  NewTubeFlushList () ; 
 TYPE_2__* ZeroMalloc (int) ; 

IPC *NewIPCBySock(CEDAR *cedar, SOCK *s, void *mac_address)
{
	IPC *ipc;
	// Validate arguments
	if (cedar == NULL || mac_address == NULL || s == NULL)
	{
		return NULL;
	}

	ipc = ZeroMalloc(sizeof(IPC));

	ipc->Cedar = cedar;
	AddRef(cedar->ref);

	ipc->Sock = s;
	AddRef(s->ref);

	Copy(ipc->MacAddress, mac_address, 6);

	ipc->Interrupt = NewInterruptManager();

	// Create an ARP table
	ipc->ArpTable = NewList(IPCCmpArpTable);

	// Create an IPv4 reception queue
	ipc->IPv4ReceivedQueue = NewQueue();

	ipc->FlushList = NewTubeFlushList();

	return ipc;
}