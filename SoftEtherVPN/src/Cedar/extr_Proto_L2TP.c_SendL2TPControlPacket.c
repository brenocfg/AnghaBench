#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_19__ {int IsControl; int /*<<< orphan*/  Ns; scalar_t__ Nr; int /*<<< orphan*/  SessionId; int /*<<< orphan*/  TunnelId; } ;
struct TYPE_18__ {scalar_t__ NextSendTick; int /*<<< orphan*/  Ns; int /*<<< orphan*/ * Buf; } ;
struct TYPE_17__ {scalar_t__ Now; } ;
struct TYPE_16__ {int /*<<< orphan*/  SendQueue; scalar_t__ LastNr; int /*<<< orphan*/  NextNs; int /*<<< orphan*/  TunnelId1; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  TYPE_2__ L2TP_SERVER ;
typedef  TYPE_3__ L2TP_QUEUE ;
typedef  TYPE_4__ L2TP_PACKET ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * BuildL2TPPacketData (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  L2TPAddInterrupt (TYPE_2__*,scalar_t__) ; 
 scalar_t__ L2TP_PACKET_RESEND_INTERVAL ; 
 int /*<<< orphan*/  SendL2TPControlPacketMain (TYPE_2__*,TYPE_1__*,TYPE_3__*) ; 
 TYPE_3__* ZeroMalloc (int) ; 

void SendL2TPControlPacket(L2TP_SERVER *l2tp, L2TP_TUNNEL *t, UINT session_id, L2TP_PACKET *p)
{
	BUF *buf;
	L2TP_QUEUE *q;
	// Validate arguments
	if (l2tp == NULL || t == NULL || p == NULL)
	{
		return;
	}

	p->IsControl = true;
	p->TunnelId = t->TunnelId1;
	p->SessionId = session_id;

	p->Ns = t->NextNs;
	t->NextNs++;

	p->Nr = t->LastNr + 1;

	buf = BuildL2TPPacketData(p, t);

	q = ZeroMalloc(sizeof(L2TP_QUEUE));
	q->Buf = buf;
	q->Ns = p->Ns;
	q->NextSendTick = l2tp->Now + (UINT64)L2TP_PACKET_RESEND_INTERVAL;
	SendL2TPControlPacketMain(l2tp, t, q);

	L2TPAddInterrupt(l2tp, q->NextSendTick);

	Add(t->SendQueue, q);

}