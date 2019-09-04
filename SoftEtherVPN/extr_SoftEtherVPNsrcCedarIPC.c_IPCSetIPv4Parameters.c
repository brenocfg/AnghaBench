#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int NumExistingRoutes; } ;
struct TYPE_14__ {int /*<<< orphan*/  ClasslessRoute; int /*<<< orphan*/  BroadcastAddress; int /*<<< orphan*/  DefaultGateway; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  ClientIPAddress; } ;
typedef  TYPE_1__ IPC ;
typedef  TYPE_2__ IP ;
typedef  TYPE_2__ DHCP_CLASSLESS_ROUTE_TABLE ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  GetBroadcastAddress4 (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int IsZeroIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool IPCSetIPv4Parameters(IPC *ipc, IP *ip, IP *subnet, IP *gw, DHCP_CLASSLESS_ROUTE_TABLE *rt)
{
	bool changed = false;
	// Validate arguments
	if (ipc == NULL || ip == NULL || subnet == NULL)
	{
		return false;
	}

	if (CmpIpAddr(&ipc->ClientIPAddress, ip) != 0)
	{
		changed = true;
	}
	Copy(&ipc->ClientIPAddress, ip, sizeof(IP));

	if (CmpIpAddr(&ipc->SubnetMask, subnet) != 0)
	{
		changed = true;
	}
	Copy(&ipc->SubnetMask, subnet, sizeof(IP));

	if (gw != NULL)
	{
		if (CmpIpAddr(&ipc->DefaultGateway, gw) != 0)
		{
			changed = true;
		}

		Copy(&ipc->DefaultGateway, gw, sizeof(IP));
	}
	else
	{
		if (IsZeroIP(&ipc->DefaultGateway) == false)
		{
			changed = true;
		}

		Zero(&ipc->DefaultGateway, sizeof(IP));
	}

	GetBroadcastAddress4(&ipc->BroadcastAddress, ip, subnet);

	if (rt != NULL && rt->NumExistingRoutes >= 1)
	{
		if (Cmp(&ipc->ClasslessRoute, rt, sizeof(DHCP_CLASSLESS_ROUTE_TABLE)) != 0)
		{
			changed = true;

			Copy(&ipc->ClasslessRoute, rt, sizeof(DHCP_CLASSLESS_ROUTE_TABLE));
		}
	}

	return changed;
}