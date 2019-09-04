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
struct TYPE_7__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  SendPacketList; } ;
typedef  int /*<<< orphan*/  IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;
typedef  TYPE_1__ ETHERIP_SERVER ;
typedef  TYPE_2__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_2__*) ; 
 int /*<<< orphan*/  IPSEC_IP_PROTO_ETHERIP ; 
 int /*<<< orphan*/  IPsecSendPacketByIkeClient (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

void IPsecIkeClientSendEtherIPPackets(IKE_SERVER *ike, IKE_CLIENT *c, ETHERIP_SERVER *s)
{
	UINT i;
	// Validate arguments
	if (ike == NULL || c == NULL || s == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(s->SendPacketList);i++)
	{
		BLOCK *b = LIST_DATA(s->SendPacketList, i);

		// Packet transmission
		IPsecSendPacketByIkeClient(ike, c, b->Buf, b->Size, IPSEC_IP_PROTO_ETHERIP);

		FreeBlock(b);
	}

	DeleteAll(s->SendPacketList);
}