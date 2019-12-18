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
typedef  int u8 ;
typedef  int u16 ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct l2cap_pinfo {scalar_t__ remote_max_tx; int req_seq; scalar_t__ fcs; int /*<<< orphan*/  conn; } ;
struct TYPE_2__ {int tx_seq; scalar_t__ retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int L2CAP_CTRL_REQSEQ_SHIFT ; 
 int L2CAP_CTRL_TXSEQ_SHIFT ; 
 scalar_t__ L2CAP_FCS_CRC16 ; 
 scalar_t__ L2CAP_HDR_SIZE ; 
 int /*<<< orphan*/  TX_QUEUE (struct sock*) ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int crc16 (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int l2cap_do_send (struct sock*,struct sk_buff*) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,scalar_t__) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_is_last (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_queue_next (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int l2cap_retransmit_frame(struct sock *sk, u8 tx_seq)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	struct sk_buff *skb, *tx_skb;
	u16 control, fcs;
	int err;

	skb = skb_peek(TX_QUEUE(sk));
	do {
		if (bt_cb(skb)->tx_seq != tx_seq) {
			if (skb_queue_is_last(TX_QUEUE(sk), skb))
				break;
			skb = skb_queue_next(TX_QUEUE(sk), skb);
			continue;
		}

		if (pi->remote_max_tx &&
				bt_cb(skb)->retries == pi->remote_max_tx) {
			l2cap_send_disconn_req(pi->conn, sk);
			break;
		}

		tx_skb = skb_clone(skb, GFP_ATOMIC);
		bt_cb(skb)->retries++;
		control = get_unaligned_le16(tx_skb->data + L2CAP_HDR_SIZE);
		control |= (pi->req_seq << L2CAP_CTRL_REQSEQ_SHIFT)
				| (tx_seq << L2CAP_CTRL_TXSEQ_SHIFT);
		put_unaligned_le16(control, tx_skb->data + L2CAP_HDR_SIZE);

		if (l2cap_pi(sk)->fcs == L2CAP_FCS_CRC16) {
			fcs = crc16(0, (u8 *)tx_skb->data, tx_skb->len - 2);
			put_unaligned_le16(fcs, tx_skb->data + tx_skb->len - 2);
		}

		err = l2cap_do_send(sk, tx_skb);
		if (err < 0) {
			l2cap_send_disconn_req(pi->conn, sk);
			return err;
		}
		break;
	} while(1);
	return 0;
}