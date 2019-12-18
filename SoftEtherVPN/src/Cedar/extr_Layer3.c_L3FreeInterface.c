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
struct TYPE_12__ {int /*<<< orphan*/ * SendQueue; int /*<<< orphan*/ * IpWaitList; int /*<<< orphan*/ * IpPacketQueue; int /*<<< orphan*/ * ArpWaitTable; int /*<<< orphan*/ * ArpTable; } ;
struct TYPE_11__ {TYPE_1__* Packet; } ;
struct TYPE_10__ {TYPE_2__* PacketData; } ;
typedef  TYPE_1__ PKT ;
typedef  TYPE_2__ L3PACKET ;
typedef  TYPE_3__ L3IF ;
typedef  TYPE_2__ L3ARPWAIT ;
typedef  TYPE_2__ L3ARPENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  FreePacket (TYPE_1__*) ; 
 void* GetNext (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ *) ; 

void L3FreeInterface(L3IF *f)
{
	UINT i;
	L3PACKET *p;
	PKT *pkt;
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(f->ArpTable);i++)
	{
		L3ARPENTRY *a = LIST_DATA(f->ArpTable, i);
		Free(a);
	}
	ReleaseList(f->ArpTable);
	f->ArpTable = NULL;

	for (i = 0;i < LIST_NUM(f->ArpWaitTable);i++)
	{
		L3ARPWAIT *w = LIST_DATA(f->ArpWaitTable, i);
		Free(w);
	}
	ReleaseList(f->ArpWaitTable);
	f->ArpWaitTable = NULL;

	while (p = GetNext(f->IpPacketQueue))
	{
		Free(p->Packet->PacketData);
		FreePacket(p->Packet);
		Free(p);
	}
	ReleaseQueue(f->IpPacketQueue);
	f->IpPacketQueue = NULL;

	for (i = 0;i < LIST_NUM(f->IpWaitList);i++)
	{
		L3PACKET *p = LIST_DATA(f->IpWaitList, i);
		Free(p->Packet->PacketData);
		FreePacket(p->Packet);
		Free(p);
	}
	ReleaseList(f->IpWaitList);
	f->IpWaitList = NULL;

	while (pkt = GetNext(f->SendQueue))
	{
		Free(pkt->PacketData);
		FreePacket(pkt);
	}
	ReleaseQueue(f->SendQueue);
	f->SendQueue = NULL;
}