#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_9__ {scalar_t__ count; } ;
struct TYPE_10__ {TYPE_3__ hscx; } ;
struct BCState {int /*<<< orphan*/  Flag; TYPE_4__ hw; int /*<<< orphan*/  squeue; TYPE_5__* tx_skb; int /*<<< orphan*/  aclock; int /*<<< orphan*/  ackcnt; TYPE_2__* st; } ;
struct TYPE_11__ {scalar_t__ pkt_type; scalar_t__ len; } ;
struct TYPE_7__ {int /*<<< orphan*/  flag; } ;
struct TYPE_8__ {TYPE_1__ lli; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int /*<<< orphan*/  B_ACKPENDING ; 
 int /*<<< orphan*/  B_XMTBUFREADY ; 
 int /*<<< orphan*/  FLG_LLI_L1WAKEUP ; 
 scalar_t__ PACKET_NOACK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_5__*) ; 
 int /*<<< orphan*/  schedule_event (struct BCState*,int /*<<< orphan*/ ) ; 
 TYPE_5__* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_modem (struct BCState*) ; 

__attribute__((used)) static inline void
modem_fill(struct BCState *bcs) {
		
	if (bcs->tx_skb) {
		if (bcs->tx_skb->len) {
			write_modem(bcs);
			return;
		} else {
			if (test_bit(FLG_LLI_L1WAKEUP,&bcs->st->lli.flag) &&
				(PACKET_NOACK != bcs->tx_skb->pkt_type)) {
				u_long	flags;
				spin_lock_irqsave(&bcs->aclock, flags);
				bcs->ackcnt += bcs->hw.hscx.count;
				spin_unlock_irqrestore(&bcs->aclock, flags);
				schedule_event(bcs, B_ACKPENDING);
			}
			dev_kfree_skb_any(bcs->tx_skb);
			bcs->tx_skb = NULL;
		}
	}
	if ((bcs->tx_skb = skb_dequeue(&bcs->squeue))) {
		bcs->hw.hscx.count = 0;
		test_and_set_bit(BC_FLG_BUSY, &bcs->Flag);
		write_modem(bcs);
	} else {
		test_and_clear_bit(BC_FLG_BUSY, &bcs->Flag);
		schedule_event(bcs, B_XMTBUFREADY);
	}
}