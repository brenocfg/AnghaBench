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
struct TYPE_17__ {int /*<<< orphan*/  Hostname; int /*<<< orphan*/  ClientAddress; int /*<<< orphan*/  Opcode; } ;
struct TYPE_16__ {int /*<<< orphan*/  ClientHostname; } ;
struct TYPE_15__ {scalar_t__ SubnetMask; } ;
typedef  int /*<<< orphan*/  TUBE ;
typedef  TYPE_1__ IPC ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ DHCP_OPTION_LIST ;
typedef  TYPE_3__ DHCPV4_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_2__*,TYPE_14__*,int) ; 
 int /*<<< orphan*/  DHCP_ACK ; 
 int /*<<< orphan*/  DHCP_INFORM ; 
 int /*<<< orphan*/  FreeDHCPv4Data (TYPE_3__*) ; 
 int /*<<< orphan*/  IPCDhcpSetConditionalUserClass (TYPE_1__*,TYPE_2__*) ; 
 TYPE_3__* IPCSendDhcpRequest (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPC_DHCP_TIMEOUT ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Rand32 () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool IPCDhcpRequestInformIP(IPC *ipc, DHCP_OPTION_LIST *opt, TUBE *discon_poll_tube, IP *client_ip)
{
	DHCP_OPTION_LIST req;
	DHCPV4_DATA *d;
	UINT tran_id = Rand32();
	bool ok;
	// Validate arguments
	if (ipc == NULL || opt == NULL || client_ip == NULL)
	{
		return false;
	}

	// Send a DHCP Inform
	Zero(&req, sizeof(req));
	req.Opcode = DHCP_INFORM;
	req.ClientAddress = IPToUINT(client_ip);
	StrCpy(req.Hostname, sizeof(req.Hostname), ipc->ClientHostname);
	IPCDhcpSetConditionalUserClass(ipc, &req);

	d = IPCSendDhcpRequest(ipc, NULL, tran_id, &req, DHCP_ACK, IPC_DHCP_TIMEOUT, discon_poll_tube);
	if (d == NULL)
	{
		return false;
	}

	// Analyze the DHCP Ack
	ok = true;
	if (d->ParsedOptionList->SubnetMask == 0)
	{
		ok = false;
	}

	if (ok == false)
	{
		FreeDHCPv4Data(d);
		return false;
	}

	Copy(opt, d->ParsedOptionList, sizeof(DHCP_OPTION_LIST));

	FreeDHCPv4Data(d);

	return true;
}