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
struct hpsb_packet {int tlabel; TYPE_2__* host; int /*<<< orphan*/  node_id; } ;
struct TYPE_4__ {TYPE_1__* tl_pool; } ;
struct TYPE_3__ {unsigned long* map; } ;

/* Variables and functions */
 int ALL_NODES ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NODEID_TO_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __test_and_clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  hpsb_tlabel_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tlabel_wq ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void hpsb_free_tlabel(struct hpsb_packet *packet)
{
	unsigned long flags, *tp;
	int tlabel, n = NODEID_TO_NODE(packet->node_id);

	if (unlikely(n == ALL_NODES))
		return;
	tp = packet->host->tl_pool[n].map;
	tlabel = packet->tlabel;
	BUG_ON(tlabel > 63 || tlabel < 0);

	spin_lock_irqsave(&hpsb_tlabel_lock, flags);
	BUG_ON(!__test_and_clear_bit(tlabel, tp));
	spin_unlock_irqrestore(&hpsb_tlabel_lock, flags);

	wake_up_interruptible(&tlabel_wq);
}