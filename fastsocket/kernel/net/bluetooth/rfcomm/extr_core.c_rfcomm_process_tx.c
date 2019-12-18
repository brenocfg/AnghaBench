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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rfcomm_dlc {int cfc; int rx_credits; int tx_credits; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  flags; int /*<<< orphan*/  session; int /*<<< orphan*/  addr; int /*<<< orphan*/  v24_sig; int /*<<< orphan*/  dlci; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  RFCOMM_MSC_PENDING ; 
 int /*<<< orphan*/  RFCOMM_RX_THROTTLED ; 
 int /*<<< orphan*/  RFCOMM_TX_THROTTLED ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_send_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rfcomm_send_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_send_msc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int rfcomm_process_tx(struct rfcomm_dlc *d)
{
	struct sk_buff *skb;
	int err;

	BT_DBG("dlc %p state %ld cfc %d rx_credits %d tx_credits %d",
			d, d->state, d->cfc, d->rx_credits, d->tx_credits);

	/* Send pending MSC */
	if (test_and_clear_bit(RFCOMM_MSC_PENDING, &d->flags))
		rfcomm_send_msc(d->session, 1, d->dlci, d->v24_sig);

	if (d->cfc) {
		/* CFC enabled.
		 * Give them some credits */
		if (!test_bit(RFCOMM_RX_THROTTLED, &d->flags) &&
				d->rx_credits <= (d->cfc >> 2)) {
			rfcomm_send_credits(d->session, d->addr, d->cfc - d->rx_credits);
			d->rx_credits = d->cfc;
		}
	} else {
		/* CFC disabled.
		 * Give ourselves some credits */
		d->tx_credits = 5;
	}

	if (test_bit(RFCOMM_TX_THROTTLED, &d->flags))
		return skb_queue_len(&d->tx_queue);

	while (d->tx_credits && (skb = skb_dequeue(&d->tx_queue))) {
		err = rfcomm_send_frame(d->session, skb->data, skb->len);
		if (err < 0) {
			skb_queue_head(&d->tx_queue, skb);
			break;
		}
		kfree_skb(skb);
		d->tx_credits--;
	}

	if (d->cfc && !d->tx_credits) {
		/* We're out of TX credits.
		 * Set TX_THROTTLED flag to avoid unnesary wakeups by dlc_send. */
		set_bit(RFCOMM_TX_THROTTLED, &d->flags);
	}

	return skb_queue_len(&d->tx_queue);
}