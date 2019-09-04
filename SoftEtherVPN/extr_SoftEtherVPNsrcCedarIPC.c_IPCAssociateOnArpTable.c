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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_14__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_13__ {int /*<<< orphan*/  ArpTable; int /*<<< orphan*/  BroadcastAddress; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  ClientIPAddress; int /*<<< orphan*/  MacAddress; } ;
struct TYPE_12__ {int Resolved; scalar_t__ ExpireTime; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  PacketQueue; scalar_t__ GiveupTime; } ;
typedef  TYPE_1__ IPC_ARP ;
typedef  TYPE_2__ IPC ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ BLOCK ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_3__*) ; 
 TYPE_3__* GetNext (int /*<<< orphan*/ ) ; 
 TYPE_1__* IPCNewARP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* IPCSearchArpTable (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPCSendIPv4WithDestMacAddr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IPC_ARP_LIFETIME ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int IsInSameNetwork4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsValidUnicastIPAddress4 (int /*<<< orphan*/ *) ; 
 int IsValidUnicastMacAddress (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 

void IPCAssociateOnArpTable(IPC *ipc, IP *ip, UCHAR *mac_address)
{
	IPC_ARP *a;
	// Validate arguments 
	if (ipc == NULL || ip == NULL || IsValidUnicastIPAddress4(ip) == false || IsValidUnicastMacAddress(mac_address) == false)
	{
		return;
	}
	if (CmpIpAddr(&ipc->ClientIPAddress, ip) == 0 || Cmp(ipc->MacAddress, mac_address, 6) == 0)
	{
		return;
	}
	if (IsInSameNetwork4(ip, &ipc->ClientIPAddress, &ipc->SubnetMask) == false)
	{
		// Not to learn the IP address of outside the subnet
		return;
	}

	if (CmpIpAddr(&ipc->BroadcastAddress, ip) == 0)
	{
		// Not to learn the broadcast IP address
		return;
	}

	// Search whether there is ARP table entry already
	a = IPCSearchArpTable(ipc, ip);
	if (a == NULL)
	{
		// Add to the ARP table
		a = IPCNewARP(ip, mac_address);

		Insert(ipc->ArpTable, a);
	}
	else
	{
		Copy(a->MacAddress, mac_address, 6);

		// There is the ARP table entry already
		if (a->Resolved == false)
		{
			a->Resolved = true;
			a->GiveupTime = 0;

			// Send all the packets that are accumulated to be sent
			while (true)
			{
				BLOCK *b = GetNext(a->PacketQueue);

				if (b == NULL)
				{
					break;
				}

				IPCSendIPv4WithDestMacAddr(ipc, b->Buf, b->Size, a->MacAddress);

				FreeBlock(b);
			}
		}

		// Extend the expiration date
		a->ExpireTime = Tick64() + (UINT64)IPC_ARP_LIFETIME;
	}
}