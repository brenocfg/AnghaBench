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
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  ServerAddress; int /*<<< orphan*/  Opcode; } ;
typedef  int /*<<< orphan*/  IPC ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ DHCP_OPTION_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  DHCP_RELEASE ; 
 int /*<<< orphan*/  FreeDHCPv4Data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPCDhcpSetConditionalUserClass (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IPCSendDhcpRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Rand32 () ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void IPCDhcpFreeIP(IPC *ipc, IP *dhcp_server)
{
	DHCP_OPTION_LIST req;
	UINT tran_id = Rand32();
	// Validate arguments
	if (ipc == NULL || dhcp_server == NULL)
	{
		return;
	}

	Zero(&req, sizeof(req));
	req.Opcode = DHCP_RELEASE;
	req.ServerAddress = IPToUINT(dhcp_server);
	IPCDhcpSetConditionalUserClass(ipc, &req);

	FreeDHCPv4Data(IPCSendDhcpRequest(ipc, NULL, tran_id, &req, 0, 0, NULL));
}