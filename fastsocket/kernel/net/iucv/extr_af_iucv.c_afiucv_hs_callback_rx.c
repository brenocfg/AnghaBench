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
struct sock {scalar_t__ sk_state; int sk_shutdown; } ;
struct sk_buff {int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct iucv_sock {TYPE_1__ message_q; int /*<<< orphan*/  backlog_skb_q; } ;
struct af_iucv_trans_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IUCV_CONNECTED ; 
 int NET_RX_SUCCESS ; 
 int RCV_SHUTDOWN ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afiucv_hs_callback_rx(struct sock *sk, struct sk_buff *skb)
{
	struct iucv_sock *iucv = iucv_sk(sk);

	if (!iucv) {
		kfree_skb(skb);
		return NET_RX_SUCCESS;
	}

	if (sk->sk_state != IUCV_CONNECTED) {
		kfree_skb(skb);
		return NET_RX_SUCCESS;
	}

	if (sk->sk_shutdown & RCV_SHUTDOWN) {
		kfree_skb(skb);
		return NET_RX_SUCCESS;
	}

		/* write stuff from iucv_msg to skb cb */
	if (skb->len < sizeof(struct af_iucv_trans_hdr)) {
		kfree_skb(skb);
		return NET_RX_SUCCESS;
	}
	skb_pull(skb, sizeof(struct af_iucv_trans_hdr));
	skb_reset_transport_header(skb);
	skb_reset_network_header(skb);
	spin_lock(&iucv->message_q.lock);
	if (skb_queue_empty(&iucv->backlog_skb_q)) {
		if (sock_queue_rcv_skb(sk, skb)) {
			/* handle rcv queue full */
			skb_queue_tail(&iucv->backlog_skb_q, skb);
		}
	} else
		skb_queue_tail(&iucv_sk(sk)->backlog_skb_q, skb);
	spin_unlock(&iucv->message_q.lock);
	return NET_RX_SUCCESS;
}