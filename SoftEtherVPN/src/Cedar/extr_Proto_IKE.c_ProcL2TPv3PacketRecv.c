#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ Size; int /*<<< orphan*/ * Data; void* SrcPort; int /*<<< orphan*/  SrcIP; int /*<<< orphan*/  DstIP; void* DestPort; scalar_t__ Type; } ;
typedef  TYPE_1__ UDPPACKET ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int IsL2TPOnIPsecTunnelMode; int /*<<< orphan*/  L2TP; int /*<<< orphan*/  L2TPClientIP; int /*<<< orphan*/  L2TPServerIP; int /*<<< orphan*/  TunnelModeClientIP; int /*<<< orphan*/  TunnelModeServerIP; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_2__ IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPSEC_PORT_L2TP ; 
 void* IPSEC_PORT_L2TPV3_VIRTUAL ; 
 int /*<<< orphan*/  IPsecIkeClientManageL2TPServer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  IPsecIkeSendUdpForDebug (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ProcL2TPPacketRecv (int /*<<< orphan*/ ,TYPE_1__*) ; 

void ProcL2TPv3PacketRecv(IKE_SERVER *ike, IKE_CLIENT *c, UCHAR *data, UINT data_size, bool is_tunnel_mode)
{
	UDPPACKET p;
	// Validate arguments
	if (ike == NULL || c == NULL || data == NULL || data_size == 0)
	{
		return;
	}

	c->IsL2TPOnIPsecTunnelMode = is_tunnel_mode;

	IPsecIkeClientManageL2TPServer(ike, c);

	// Pass the received packet to the L2TP server
	p.Type = 0;
	p.Data = data;
	p.DestPort = IPSEC_PORT_L2TPV3_VIRTUAL;
	p.Size = data_size;

	if (is_tunnel_mode)
	{
		Copy(&p.DstIP, &c->TunnelModeServerIP, sizeof(IP));
		Copy(&p.SrcIP, &c->TunnelModeClientIP, sizeof(IP));
	}
	else
	{
		Copy(&p.DstIP, &c->L2TPServerIP, sizeof(IP));
		Copy(&p.SrcIP, &c->L2TPClientIP, sizeof(IP));
	}
	p.SrcPort = IPSEC_PORT_L2TPV3_VIRTUAL;

#ifdef	RAW_DEBUG
	IPsecIkeSendUdpForDebug(IPSEC_PORT_L2TP, 1, ((UCHAR *)p.Data) + 4, p.Size - 4);
#endif	// RAW_DEBUG

	ProcL2TPPacketRecv(c->L2TP, &p);
}