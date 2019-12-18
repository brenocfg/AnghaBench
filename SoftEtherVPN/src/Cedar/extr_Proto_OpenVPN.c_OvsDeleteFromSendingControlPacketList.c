#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/ * SendControlPacketList; } ;
struct TYPE_8__ {scalar_t__ PacketId; } ;
typedef  TYPE_1__ OPENVPN_CONTROL_PACKET ;
typedef  TYPE_2__ OPENVPN_CHANNEL ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  AddDistinct (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OvsFreeControlPacket (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void OvsDeleteFromSendingControlPacketList(OPENVPN_CHANNEL *c, UINT num_acks, UINT *acks)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (c == NULL || num_acks == 0)
	{
		return;
	}

	o = NewListFast(NULL);
	for (i = 0;i < num_acks;i++)
	{
		UINT ack = acks[i];
		UINT j;

		for (j = 0;j < LIST_NUM(c->SendControlPacketList);j++)
		{
			OPENVPN_CONTROL_PACKET *p = LIST_DATA(c->SendControlPacketList, j);

			if (p->PacketId == ack)
			{
				AddDistinct(o, p);
			}
		}
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		OPENVPN_CONTROL_PACKET *p = LIST_DATA(o, i);

		Delete(c->SendControlPacketList, p);

		OvsFreeControlPacket(p);
	}

	ReleaseList(o);
}