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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ ackid; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct ldc_packet {scalar_t__ seqid; TYPE_2__ u; } ;
struct ldc_channel {unsigned long tx_acked; unsigned long tx_tail; struct ldc_packet* tx_base; } ;

/* Variables and functions */
 unsigned long LDC_PACKET_SIZE ; 
 int ldc_abort (struct ldc_channel*) ; 
 unsigned long tx_advance (struct ldc_channel*,unsigned long) ; 

__attribute__((used)) static int process_data_ack(struct ldc_channel *lp,
			    struct ldc_packet *ack)
{
	unsigned long head = lp->tx_acked;
	u32 ackid = ack->u.r.ackid;

	while (1) {
		struct ldc_packet *p = lp->tx_base + (head / LDC_PACKET_SIZE);

		head = tx_advance(lp, head);

		if (p->seqid == ackid) {
			lp->tx_acked = head;
			return 0;
		}
		if (head == lp->tx_tail)
			return ldc_abort(lp);
	}

	return 0;
}