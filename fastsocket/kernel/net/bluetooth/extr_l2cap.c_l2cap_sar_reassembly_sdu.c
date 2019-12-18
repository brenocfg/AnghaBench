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
typedef  int u16 ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct l2cap_pinfo {int conn_state; struct sk_buff* sdu; int /*<<< orphan*/  sdu_len; int /*<<< orphan*/  partial_sdu_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int L2CAP_CONN_SAR_SDU ; 
 int L2CAP_CTRL_SAR ; 
#define  L2CAP_SDU_CONTINUE 131 
#define  L2CAP_SDU_END 130 
#define  L2CAP_SDU_START 129 
#define  L2CAP_SDU_UNSEGMENTED 128 
 struct sk_buff* bt_skb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int l2cap_sar_reassembly_sdu(struct sock *sk, struct sk_buff *skb, u16 control)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	struct sk_buff *_skb;
	int err = -EINVAL;

	switch (control & L2CAP_CTRL_SAR) {
	case L2CAP_SDU_UNSEGMENTED:
		if (pi->conn_state & L2CAP_CONN_SAR_SDU) {
			kfree_skb(pi->sdu);
			break;
		}

		err = sock_queue_rcv_skb(sk, skb);
		if (!err)
			return 0;

		break;

	case L2CAP_SDU_START:
		if (pi->conn_state & L2CAP_CONN_SAR_SDU) {
			kfree_skb(pi->sdu);
			break;
		}

		pi->sdu_len = get_unaligned_le16(skb->data);
		skb_pull(skb, 2);

		pi->sdu = bt_skb_alloc(pi->sdu_len, GFP_ATOMIC);
		if (!pi->sdu) {
			err = -ENOMEM;
			break;
		}

		memcpy(skb_put(pi->sdu, skb->len), skb->data, skb->len);

		pi->conn_state |= L2CAP_CONN_SAR_SDU;
		pi->partial_sdu_len = skb->len;
		err = 0;
		break;

	case L2CAP_SDU_CONTINUE:
		if (!(pi->conn_state & L2CAP_CONN_SAR_SDU))
			break;

		memcpy(skb_put(pi->sdu, skb->len), skb->data, skb->len);

		pi->partial_sdu_len += skb->len;
		if (pi->partial_sdu_len > pi->sdu_len)
			kfree_skb(pi->sdu);
		else
			err = 0;

		break;

	case L2CAP_SDU_END:
		if (!(pi->conn_state & L2CAP_CONN_SAR_SDU))
			break;

		memcpy(skb_put(pi->sdu, skb->len), skb->data, skb->len);

		pi->conn_state &= ~L2CAP_CONN_SAR_SDU;
		pi->partial_sdu_len += skb->len;

		if (pi->partial_sdu_len == pi->sdu_len) {
			_skb = skb_clone(pi->sdu, GFP_ATOMIC);
			err = sock_queue_rcv_skb(sk, _skb);
			if (err < 0)
				kfree_skb(_skb);
		}
		kfree_skb(pi->sdu);
		err = 0;

		break;
	}

	kfree_skb(skb);
	return err;
}