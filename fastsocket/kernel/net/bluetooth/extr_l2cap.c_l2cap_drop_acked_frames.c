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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ tx_seq; } ;
struct TYPE_3__ {scalar_t__ expected_ack_seq; int /*<<< orphan*/  retrans_timer; int /*<<< orphan*/  unacked_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_QUEUE (struct sock*) ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_drop_acked_frames(struct sock *sk)
{
	struct sk_buff *skb;

	while ((skb = skb_peek(TX_QUEUE(sk)))) {
		if (bt_cb(skb)->tx_seq == l2cap_pi(sk)->expected_ack_seq)
			break;

		skb = skb_dequeue(TX_QUEUE(sk));
		kfree_skb(skb);

		l2cap_pi(sk)->unacked_frames--;
	}

	if (!l2cap_pi(sk)->unacked_frames)
		del_timer(&l2cap_pi(sk)->retrans_timer);

	return;
}