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
struct TYPE_2__ {int /*<<< orphan*/  rx_packets; } ;
struct tsap_cb {int send_credit; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  remote_credit; TYPE_1__ stats; } ;
struct sk_buff {int* data; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  irttp_run_rx_queue (struct tsap_cb*) ; 
 int /*<<< orphan*/  irttp_run_tx_queue (struct tsap_cb*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int irttp_data_indication(void *instance, void *sap,
				 struct sk_buff *skb)
{
	struct tsap_cb *self;
	unsigned long flags;
	int n;

	self = (struct tsap_cb *) instance;

	n = skb->data[0] & 0x7f;     /* Extract the credits */

	self->stats.rx_packets++;

	/*  Deal with inbound credit
	 *  Since we can transmit and receive frames concurrently,
	 *  the code below is a critical region and we must assure that
	 *  nobody messes with the credits while we update them.
	 */
	spin_lock_irqsave(&self->lock, flags);
	self->send_credit += n;
	if (skb->len > 1)
		self->remote_credit--;
	spin_unlock_irqrestore(&self->lock, flags);

	/*
	 *  Data or dataless packet? Dataless frames contains only the
	 *  TTP_HEADER.
	 */
	if (skb->len > 1) {
		/*
		 *  We don't remove the TTP header, since we must preserve the
		 *  more bit, so the defragment routing knows what to do
		 */
		skb_queue_tail(&self->rx_queue, skb);
	} else {
		/* Dataless flowdata TTP-PDU */
		dev_kfree_skb(skb);
	}


	/* Push data to the higher layer.
	 * We do it synchronously because running the todo timer for each
	 * receive packet would be too much overhead and latency.
	 * By passing control to the higher layer, we run the risk that
	 * it may take time or grab a lock. Most often, the higher layer
	 * will only put packet in a queue.
	 * Anyway, packets are only dripping through the IrDA, so we can
	 * have time before the next packet.
	 * Further, we are run from NET_BH, so the worse that can happen is
	 * us missing the optimal time to send back the PF bit in LAP.
	 * Jean II */
	irttp_run_rx_queue(self);

	/* We now give credits to peer in irttp_run_rx_queue().
	 * We need to send credit *NOW*, otherwise we are going
	 * to miss the next Tx window. The todo timer may take
	 * a while before it's run... - Jean II */

	/*
	 * If the peer device has given us some credits and we didn't have
	 * anyone from before, then we need to shedule the tx queue.
	 * We need to do that because our Tx have stopped (so we may not
	 * get any LAP flow indication) and the user may be stopped as
	 * well. - Jean II
	 */
	if (self->send_credit == n) {
		/* Restart pushing stuff to LAP */
		irttp_run_tx_queue(self);
		/* Note : we don't want to schedule the todo timer
		 * because it has horrible latency. No tasklets
		 * because the tasklet API is broken. - Jean II */
	}

	return 0;
}