#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_10__ {scalar_t__ SrcPort; scalar_t__ Size; scalar_t__ Data; } ;
typedef  TYPE_1__ UDPPACKET ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  L2TPClientPort; } ;
struct TYPE_11__ {int /*<<< orphan*/  SendPacketList; } ;
typedef  TYPE_2__ L2TP_SERVER ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  TYPE_3__ IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeUdpPacket (TYPE_1__*) ; 
 int /*<<< orphan*/  IPSEC_IP_PROTO_L2TPV3 ; 
 int /*<<< orphan*/  IPSEC_PORT_L2TP ; 
 scalar_t__ IPSEC_PORT_L2TPV3_VIRTUAL ; 
 int /*<<< orphan*/  IPsecIkeSendUdpForDebug (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  IPsecSendPacketByIkeClient (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPsecSendUdpPacket (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

void IPsecIkeClientSendL2TPPackets(IKE_SERVER *ike, IKE_CLIENT *c, L2TP_SERVER *l2tp)
{
	UINT i;
	// Validate arguments
	if (ike == NULL || c == NULL || l2tp == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(l2tp->SendPacketList);i++)
	{
		UDPPACKET *u = LIST_DATA(l2tp->SendPacketList, i);

		if (u->SrcPort != IPSEC_PORT_L2TPV3_VIRTUAL)
		{
			// L2TP UDP packet transmission
			IPsecSendUdpPacket(ike, c, IPSEC_PORT_L2TP, c->L2TPClientPort,
				u->Data, u->Size);
		}
		else
		{
			// L2TPv3 special IP packet transmission
			IPsecSendPacketByIkeClient(ike, c, u->Data, u->Size, IPSEC_IP_PROTO_L2TPV3);

#ifdef	RAW_DEBUG
			IPsecIkeSendUdpForDebug(IPSEC_PORT_L2TP, 1, ((UCHAR *)u->Data) + 4, u->Size - 4);
#endif	// RAW_DEBUG
		}

		FreeUdpPacket(u);
	}

	DeleteAll(l2tp->SendPacketList);
}