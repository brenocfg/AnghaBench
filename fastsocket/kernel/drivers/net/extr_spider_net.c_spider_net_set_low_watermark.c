#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spider_net_hw_descr {int dmac_cmd_status; } ;
struct spider_net_descr {struct spider_net_hw_descr* hwdescr; struct spider_net_descr* next; } ;
struct TYPE_2__ {int num_desc; int /*<<< orphan*/  lock; struct spider_net_descr* tail; struct spider_net_descr* head; } ;
struct spider_net_card {TYPE_1__ tx_chain; struct spider_net_descr* low_watermark; } ;

/* Variables and functions */
 int SPIDER_NET_DESCR_NOT_IN_USE ; 
 int SPIDER_NET_DESCR_TXDESFLG ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
spider_net_set_low_watermark(struct spider_net_card *card)
{
	struct spider_net_descr *descr = card->tx_chain.tail;
	struct spider_net_hw_descr *hwdescr;
	unsigned long flags;
	int status;
	int cnt=0;
	int i;

	/* Measure the length of the queue. Measurement does not
	 * need to be precise -- does not need a lock. */
	while (descr != card->tx_chain.head) {
		status = descr->hwdescr->dmac_cmd_status & SPIDER_NET_DESCR_NOT_IN_USE;
		if (status == SPIDER_NET_DESCR_NOT_IN_USE)
			break;
		descr = descr->next;
		cnt++;
	}

	/* If TX queue is short, don't even bother with interrupts */
	if (cnt < card->tx_chain.num_desc/4)
		return cnt;

	/* Set low-watermark 3/4th's of the way into the queue. */
	descr = card->tx_chain.tail;
	cnt = (cnt*3)/4;
	for (i=0;i<cnt; i++)
		descr = descr->next;

	/* Set the new watermark, clear the old watermark */
	spin_lock_irqsave(&card->tx_chain.lock, flags);
	descr->hwdescr->dmac_cmd_status |= SPIDER_NET_DESCR_TXDESFLG;
	if (card->low_watermark && card->low_watermark != descr) {
		hwdescr = card->low_watermark->hwdescr;
		hwdescr->dmac_cmd_status =
		     hwdescr->dmac_cmd_status & ~SPIDER_NET_DESCR_TXDESFLG;
	}
	card->low_watermark = descr;
	spin_unlock_irqrestore(&card->tx_chain.lock, flags);
	return cnt;
}