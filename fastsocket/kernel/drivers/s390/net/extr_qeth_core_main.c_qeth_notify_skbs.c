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
struct sk_buff {scalar_t__ protocol; scalar_t__ sk; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct qeth_qdio_out_buffer {int /*<<< orphan*/  skb_list; } ;
struct iucv_sock {int /*<<< orphan*/  (* sk_txnotify ) (struct sk_buff*,int) ;} ;
typedef  enum iucv_tx_notify { ____Placeholder_iucv_tx_notify } iucv_tx_notify ;

/* Variables and functions */
 scalar_t__ ETH_P_AF_IUCV ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,long) ; 
 int /*<<< orphan*/  TRACE ; 
 struct iucv_sock* iucv_sk (scalar_t__) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_is_last (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* skb_queue_next (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int) ; 

__attribute__((used)) static void qeth_notify_skbs(struct qeth_qdio_out_q *q,
		struct qeth_qdio_out_buffer *buf,
		enum iucv_tx_notify notification)
{
	struct sk_buff *skb;

	if (skb_queue_empty(&buf->skb_list))
		goto out;
	skb = skb_peek(&buf->skb_list);
	while (skb) {
		QETH_DBF_TEXT_(TRACE, 5, "skbn%d", notification);
		QETH_DBF_TEXT_(TRACE, 5, "%lx", (long) skb);
		if (skb->protocol == ETH_P_AF_IUCV) {
			if (skb->sk) {
				struct iucv_sock *iucv = iucv_sk(skb->sk);
				iucv->sk_txnotify(skb, notification);
			}
		}
		if (skb_queue_is_last(&buf->skb_list, skb))
			skb = NULL;
else
			skb = skb_queue_next(&buf->skb_list, skb);
	}
out:
	return;
}