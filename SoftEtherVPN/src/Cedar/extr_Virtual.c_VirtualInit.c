#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flag1; int Active; scalar_t__ CurrentIpQuota; scalar_t__ NextArpTablePolling; scalar_t__ DhcpId; TYPE_1__* Counter; int /*<<< orphan*/  SendQueue; int /*<<< orphan*/  Cancel; int /*<<< orphan*/ * Logger; } ;
typedef  TYPE_2__ VH ;
typedef  scalar_t__ UINT64 ;
struct TYPE_12__ {scalar_t__ c; } ;

/* Variables and functions */
 scalar_t__ ARP_ENTRY_POLLING_TIME ; 
 int /*<<< orphan*/  InitArpTable (TYPE_2__*) ; 
 int /*<<< orphan*/  InitArpWaitTable (TYPE_2__*) ; 
 int /*<<< orphan*/  InitDhcpServer (TYPE_2__*) ; 
 int /*<<< orphan*/  InitIpCombineList (TYPE_2__*) ; 
 int /*<<< orphan*/  InitIpWaitTable (TYPE_2__*) ; 
 int /*<<< orphan*/  InitNat (TYPE_2__*) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_2__*) ; 
 int /*<<< orphan*/  NewCancel () ; 
 int /*<<< orphan*/  NewQueue () ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_2__*) ; 

bool VirtualInit(VH *v)
{
	// Initialize the log
	v->Logger = NULL;

	LockVirtual(v);
	{
		// Initialize
		v->Cancel = NewCancel();
		v->SendQueue = NewQueue();
	}
	UnlockVirtual(v);

	// Counter reset
	v->Counter->c = 0;
	v->DhcpId = 0;

	// Initialize the ARP table
	InitArpTable(v);

	// Initialize the ARP waiting table
	InitArpWaitTable(v);

	// Initialize the IP waiting table
	InitIpWaitTable(v);

	// Initialize the IP combining list
	InitIpCombineList(v);

	// Initialize the NAT
	InitNat(v);

	// Initialize the DHCP server
	InitDhcpServer(v);

	// Other initialization
	v->flag1 = false;
	v->NextArpTablePolling = Tick64() + (UINT64)ARP_ENTRY_POLLING_TIME;
	v->CurrentIpQuota = 0;
	v->Active = true;

	return true;
}