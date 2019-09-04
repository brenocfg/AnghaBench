#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_6__ {int /*<<< orphan*/  ServerAddress; } ;
struct TYPE_8__ {TYPE_1__ L3ClientAddressOption; } ;
struct TYPE_7__ {scalar_t__ Mode; TYPE_4__* IpcAsync; int /*<<< orphan*/ * Ipc; int /*<<< orphan*/ ** Channels; } ;
typedef  TYPE_2__ OPENVPN_SESSION ;
typedef  int /*<<< orphan*/  OPENVPN_CHANNEL ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeIPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIPCAsync (TYPE_4__*) ; 
 int /*<<< orphan*/  IPCDhcpFreeIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPCProcessL3Events (int /*<<< orphan*/ *) ; 
 scalar_t__ OPENVPN_MODE_L3 ; 
 size_t OPENVPN_NUM_CHANNELS ; 
 int /*<<< orphan*/  OvsFreeChannel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void OvsFreeSession(OPENVPN_SESSION *se)
{
	UINT i;
	// Validate arguments
	if (se == NULL)
	{
		return;
	}

	// If there is IP addresses which is got from a DHCP server in the session, release it
	if (se->Ipc != NULL)
	{
		if (se->Mode == OPENVPN_MODE_L3)
		{
			if (se->IpcAsync != NULL)
			{
				IP dhcp_ip;

				UINTToIP(&dhcp_ip, se->IpcAsync->L3ClientAddressOption.ServerAddress);

				IPCDhcpFreeIP(se->Ipc, &dhcp_ip);
				IPCProcessL3Events(se->Ipc);
			}
		}
	}

	// Release the channel
	for (i = 0;i < OPENVPN_NUM_CHANNELS;i++)
	{
		OPENVPN_CHANNEL *c = se->Channels[i];

		if (c != NULL)
		{
			OvsFreeChannel(c);
		}
	}

	// Release the IPC
	if (se->Ipc != NULL)
	{
		FreeIPC(se->Ipc);
	}

	if (se->IpcAsync != NULL)
	{
		FreeIPCAsync(se->IpcAsync);
	}

	Free(se);
}