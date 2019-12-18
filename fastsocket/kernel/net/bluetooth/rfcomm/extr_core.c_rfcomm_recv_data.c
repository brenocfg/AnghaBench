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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct rfcomm_session {int /*<<< orphan*/  state; } ;
struct rfcomm_dlc {scalar_t__ state; int /*<<< orphan*/  (* data_ready ) (struct rfcomm_dlc*,struct sk_buff*) ;int /*<<< orphan*/  rx_credits; int /*<<< orphan*/  flags; scalar_t__ tx_credits; scalar_t__ cfc; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  RFCOMM_TX_THROTTLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rfcomm_dlc* rfcomm_dlc_get (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_send_dm (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct rfcomm_dlc*,struct sk_buff*) ; 

__attribute__((used)) static int rfcomm_recv_data(struct rfcomm_session *s, u8 dlci, int pf, struct sk_buff *skb)
{
	struct rfcomm_dlc *d;

	BT_DBG("session %p state %ld dlci %d pf %d", s, s->state, dlci, pf);

	d = rfcomm_dlc_get(s, dlci);
	if (!d) {
		rfcomm_send_dm(s, dlci);
		goto drop;
	}

	if (pf && d->cfc) {
		u8 credits = *(u8 *) skb->data; skb_pull(skb, 1);

		d->tx_credits += credits;
		if (d->tx_credits)
			clear_bit(RFCOMM_TX_THROTTLED, &d->flags);
	}

	if (skb->len && d->state == BT_CONNECTED) {
		rfcomm_dlc_lock(d);
		d->rx_credits--;
		d->data_ready(d, skb);
		rfcomm_dlc_unlock(d);
		return 0;
	}

drop:
	kfree_skb(skb);
	return 0;
}