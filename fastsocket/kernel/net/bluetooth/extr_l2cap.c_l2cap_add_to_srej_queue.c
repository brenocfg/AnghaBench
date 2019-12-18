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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ tx_seq; scalar_t__ sar; } ;

/* Variables and functions */
 int /*<<< orphan*/  SREJ_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  __skb_queue_before (int /*<<< orphan*/ ,struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ ,struct sk_buff*) ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_is_last (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_queue_next (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static void l2cap_add_to_srej_queue(struct sock *sk, struct sk_buff *skb, u8 tx_seq, u8 sar)
{
	struct sk_buff *next_skb;

	bt_cb(skb)->tx_seq = tx_seq;
	bt_cb(skb)->sar = sar;

	next_skb = skb_peek(SREJ_QUEUE(sk));
	if (!next_skb) {
		__skb_queue_tail(SREJ_QUEUE(sk), skb);
		return;
	}

	do {
		if (bt_cb(next_skb)->tx_seq > tx_seq) {
			__skb_queue_before(SREJ_QUEUE(sk), next_skb, skb);
			return;
		}

		if (skb_queue_is_last(SREJ_QUEUE(sk), next_skb))
			break;

	} while((next_skb = skb_queue_next(SREJ_QUEUE(sk), next_skb)));

	__skb_queue_tail(SREJ_QUEUE(sk), skb);
}