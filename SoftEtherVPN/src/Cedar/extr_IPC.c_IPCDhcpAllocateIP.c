#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {TYPE_14__* ParsedOptionList; } ;
struct TYPE_17__ {scalar_t__ RequestedIp; scalar_t__ ServerAddress; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Opcode; } ;
struct TYPE_16__ {int /*<<< orphan*/  ClientHostname; } ;
struct TYPE_15__ {scalar_t__ SubnetMask; scalar_t__ LeaseTime; scalar_t__ ServerAddress; scalar_t__ ClientAddress; } ;
typedef  int /*<<< orphan*/  TUBE ;
typedef  TYPE_1__ IPC ;
typedef  TYPE_2__ DHCP_OPTION_LIST ;
typedef  TYPE_3__ DHCPV4_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_2__*,TYPE_14__*,int) ; 
 int /*<<< orphan*/  DHCP_ACK ; 
 int /*<<< orphan*/  DHCP_DISCOVER ; 
 int /*<<< orphan*/  DHCP_OFFER ; 
 int /*<<< orphan*/  DHCP_REQUEST ; 
 int /*<<< orphan*/  FreeDHCPv4Data (TYPE_3__*) ; 
 int /*<<< orphan*/  IPCDhcpSetConditionalUserClass (TYPE_1__*,TYPE_2__*) ; 
 TYPE_3__* IPCSendDhcpRequest (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* IPC_DHCP_DEFAULT_LEASE ; 
 scalar_t__ IPC_DHCP_MIN_LEASE ; 
 int /*<<< orphan*/  IPC_DHCP_TIMEOUT ; 
 int IsValidUnicastIPAddressUINT4 (scalar_t__) ; 
 int /*<<< orphan*/  Rand32 () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool IPCDhcpAllocateIP(IPC *ipc, DHCP_OPTION_LIST *opt, TUBE *discon_poll_tube)
{
	DHCP_OPTION_LIST req;
	DHCPV4_DATA *d, *d2;
	UINT tran_id = Rand32();
	bool ok;
	// Validate arguments
	if (ipc == NULL || opt == NULL)
	{
		return false;
	}

	// Send a DHCP Discover
	Zero(&req, sizeof(req));
	req.RequestedIp = 0;
	req.Opcode = DHCP_DISCOVER;
	StrCpy(req.Hostname, sizeof(req.Hostname), ipc->ClientHostname);
	IPCDhcpSetConditionalUserClass(ipc, &req);

	d = IPCSendDhcpRequest(ipc, NULL, tran_id, &req, DHCP_OFFER, IPC_DHCP_TIMEOUT, discon_poll_tube);
	if (d == NULL)
	{
		return false;
	}

	// Analyze the DHCP Offer
	ok = true;
	if (IsValidUnicastIPAddressUINT4(d->ParsedOptionList->ClientAddress) == false)
	{
		ok = false;
	}
	if (IsValidUnicastIPAddressUINT4(d->ParsedOptionList->ServerAddress) == false)
	{
		ok = false;
	}
	if (d->ParsedOptionList->SubnetMask == 0)
	{
		ok = false;
	}
	if (d->ParsedOptionList->LeaseTime == 0)
	{
		d->ParsedOptionList->LeaseTime = IPC_DHCP_DEFAULT_LEASE;
	}
	if (d->ParsedOptionList->LeaseTime <= IPC_DHCP_MIN_LEASE)
	{
		d->ParsedOptionList->LeaseTime = IPC_DHCP_MIN_LEASE;
	}

	if (ok == false)
	{
		FreeDHCPv4Data(d);
		return false;
	}

	// Send a DHCP Request
	Zero(&req, sizeof(req));
	req.Opcode = DHCP_REQUEST;
	StrCpy(req.Hostname, sizeof(req.Hostname), ipc->ClientHostname);
	req.ServerAddress = d->ParsedOptionList->ServerAddress;
	req.RequestedIp = d->ParsedOptionList->ClientAddress;
	IPCDhcpSetConditionalUserClass(ipc, &req);

	d2 = IPCSendDhcpRequest(ipc, NULL, tran_id, &req, DHCP_ACK, IPC_DHCP_TIMEOUT, discon_poll_tube);
	if (d2 == NULL)
	{
		FreeDHCPv4Data(d);
		return false;
	}

	// Analyze the DHCP Ack
	ok = true;
	if (IsValidUnicastIPAddressUINT4(d2->ParsedOptionList->ClientAddress) == false)
	{
		ok = false;
	}
	if (IsValidUnicastIPAddressUINT4(d2->ParsedOptionList->ServerAddress) == false)
	{
		ok = false;
	}
	if (d2->ParsedOptionList->SubnetMask == 0)
	{
		ok = false;
	}
	if (d2->ParsedOptionList->LeaseTime == 0)
	{
		d2->ParsedOptionList->LeaseTime = IPC_DHCP_DEFAULT_LEASE;
	}
	if (d2->ParsedOptionList->LeaseTime <= IPC_DHCP_MIN_LEASE)
	{
		d2->ParsedOptionList->LeaseTime = IPC_DHCP_MIN_LEASE;
	}

	if (ok == false)
	{
		FreeDHCPv4Data(d);
		FreeDHCPv4Data(d2);
		return false;
	}

	Copy(opt, d2->ParsedOptionList, sizeof(DHCP_OPTION_LIST));

	FreeDHCPv4Data(d);
	FreeDHCPv4Data(d2);

	return true;
}