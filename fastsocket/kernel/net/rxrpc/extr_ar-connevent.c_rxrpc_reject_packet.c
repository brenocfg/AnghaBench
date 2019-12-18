#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rxrpc_local {int /*<<< orphan*/  rejecter; int /*<<< orphan*/  reject_queue; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CHECK_SLAB_OKAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  rxrpc_queue_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void rxrpc_reject_packet(struct rxrpc_local *local, struct sk_buff *skb)
{
	CHECK_SLAB_OKAY(&local->usage);

	if (!atomic_inc_not_zero(&local->usage)) {
		printk("resurrected on reject\n");
		BUG();
	}

	skb_queue_tail(&local->reject_queue, skb);
	rxrpc_queue_work(&local->rejecter);
}