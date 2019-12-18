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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int /*<<< orphan*/ * sk_send_head; } ;
struct sk_buff_head {int /*<<< orphan*/ * next; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int dummy; } ;
struct l2cap_pinfo {size_t max_pdu_size; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  L2CAP_SDU_CONTINUE ; 
 int /*<<< orphan*/  L2CAP_SDU_END ; 
 int /*<<< orphan*/  L2CAP_SDU_START ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  TX_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 struct sk_buff* l2cap_create_iframe_pdu (struct sock*,struct msghdr*,size_t,int /*<<< orphan*/ ,size_t) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail (struct sk_buff_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int l2cap_sar_segment_sdu(struct sock *sk, struct msghdr *msg, size_t len)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	struct sk_buff *skb;
	struct sk_buff_head sar_queue;
	u16 control;
	size_t size = 0;

	__skb_queue_head_init(&sar_queue);
	control = L2CAP_SDU_START;
	skb = l2cap_create_iframe_pdu(sk, msg, pi->max_pdu_size, control, len);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	__skb_queue_tail(&sar_queue, skb);
	len -= pi->max_pdu_size;
	size +=pi->max_pdu_size;
	control = 0;

	while (len > 0) {
		size_t buflen;

		if (len > pi->max_pdu_size) {
			control |= L2CAP_SDU_CONTINUE;
			buflen = pi->max_pdu_size;
		} else {
			control |= L2CAP_SDU_END;
			buflen = len;
		}

		skb = l2cap_create_iframe_pdu(sk, msg, buflen, control, 0);
		if (IS_ERR(skb)) {
			skb_queue_purge(&sar_queue);
			return PTR_ERR(skb);
		}

		__skb_queue_tail(&sar_queue, skb);
		len -= buflen;
		size += buflen;
		control = 0;
	}
	skb_queue_splice_tail(&sar_queue, TX_QUEUE(sk));
	if (sk->sk_send_head == NULL)
		sk->sk_send_head = sar_queue.next;

	return size;
}