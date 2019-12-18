#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ PriorityQoS; } ;
struct TYPE_14__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_13__ {scalar_t__ IsControl; int /*<<< orphan*/  AttributeList; int /*<<< orphan*/  MessageType; } ;
struct TYPE_12__ {int /*<<< orphan*/  SendQueue; } ;
typedef  TYPE_1__ SSTP_SERVER ;
typedef  TYPE_2__ SSTP_PACKET ;
typedef  TYPE_3__ BUF ;
typedef  TYPE_4__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_3__*) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_4__* NewBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* SstpBuildPacket (TYPE_2__*) ; 

void SstpSendPacket(SSTP_SERVER *s, SSTP_PACKET *p)
{
	BUF *b;
	BLOCK *block;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	if (p->IsControl)
	{
		Debug("SSTP Control Packet Send: Msg = %u, Num = %u\n", p->MessageType, LIST_NUM(p->AttributeList));
	}
	else
	{
		//Debug("SSTP Data Packet Send: Size=%u\n", p->DataSize);
	}

	b = SstpBuildPacket(p);
	if (b == NULL)
	{
		return;
	}

	block = NewBlock(b->Buf, b->Size, 0);
	block->PriorityQoS = p->IsControl;
	Free(b);

	InsertQueue(s->SendQueue, block);
}