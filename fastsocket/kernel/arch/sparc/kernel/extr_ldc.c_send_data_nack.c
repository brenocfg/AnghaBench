#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ackid; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct ldc_packet {int ctrl; TYPE_2__ u; scalar_t__ seqid; int /*<<< orphan*/  type; int /*<<< orphan*/  stype; } ;
struct ldc_channel {scalar_t__ snd_nxt; int /*<<< orphan*/  rcv_nxt; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HS ; 
 int LDC_CTRL_MSK ; 
 int /*<<< orphan*/  LDC_NACK ; 
 struct ldc_packet* data_get_tx_packet (struct ldc_channel*,unsigned long*) ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ldc_packet*,int /*<<< orphan*/ ,int) ; 
 int send_tx_packet (struct ldc_channel*,struct ldc_packet*,unsigned long) ; 

__attribute__((used)) static int send_data_nack(struct ldc_channel *lp, struct ldc_packet *data_pkt)
{
	struct ldc_packet *p;
	unsigned long new_tail;
	int err;

	p = data_get_tx_packet(lp, &new_tail);
	if (!p)
		return -EBUSY;
	memset(p, 0, sizeof(*p));
	p->type = data_pkt->type;
	p->stype = LDC_NACK;
	p->ctrl = data_pkt->ctrl & LDC_CTRL_MSK;
	p->seqid = lp->snd_nxt + 1;
	p->u.r.ackid = lp->rcv_nxt;

	ldcdbg(HS, "SEND DATA NACK type[0x%x] ctl[0x%x] seq[0x%x] ack[0x%x]\n",
	       p->type, p->ctrl, p->seqid, p->u.r.ackid);

	err = send_tx_packet(lp, p, new_tail);
	if (!err)
		lp->snd_nxt++;

	return err;
}