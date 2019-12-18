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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sock {struct sk_buff* sk_send_head; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct l2cap_pinfo {int conn_state; scalar_t__ remote_max_tx; int req_seq; int next_tx_seq; scalar_t__ fcs; int /*<<< orphan*/  unacked_frames; int /*<<< orphan*/  conn; } ;
struct TYPE_2__ {scalar_t__ retries; int tx_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int L2CAP_CONN_REMOTE_BUSY ; 
 int L2CAP_CONN_WAIT_F ; 
 int L2CAP_CTRL_REQSEQ_SHIFT ; 
 int L2CAP_CTRL_TXSEQ_SHIFT ; 
 scalar_t__ L2CAP_FCS_CRC16 ; 
 scalar_t__ L2CAP_HDR_SIZE ; 
 int /*<<< orphan*/  TX_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  __mod_retrans_timer () ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int crc16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int l2cap_do_send (struct sock*,struct sk_buff*) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  l2cap_tx_window_full (struct sock*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,scalar_t__) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_is_last (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_queue_next (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int l2cap_ertm_send(struct sock *sk)
{
	struct sk_buff *skb, *tx_skb;
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	u16 control, fcs;
	int err;

	if (pi->conn_state & L2CAP_CONN_WAIT_F)
		return 0;

	while ((skb = sk->sk_send_head) && (!l2cap_tx_window_full(sk))
			&& !(pi->conn_state & L2CAP_CONN_REMOTE_BUSY)) {
		tx_skb = skb_clone(skb, GFP_ATOMIC);

		if (pi->remote_max_tx &&
				bt_cb(skb)->retries == pi->remote_max_tx) {
			l2cap_send_disconn_req(pi->conn, sk);
			break;
		}

		bt_cb(skb)->retries++;

		control = get_unaligned_le16(tx_skb->data + L2CAP_HDR_SIZE);
		control |= (pi->req_seq << L2CAP_CTRL_REQSEQ_SHIFT)
				| (pi->next_tx_seq << L2CAP_CTRL_TXSEQ_SHIFT);
		put_unaligned_le16(control, tx_skb->data + L2CAP_HDR_SIZE);


		if (l2cap_pi(sk)->fcs == L2CAP_FCS_CRC16) {
			fcs = crc16(0, (u8 *)skb->data, tx_skb->len - 2);
			put_unaligned_le16(fcs, skb->data + tx_skb->len - 2);
		}

		err = l2cap_do_send(sk, tx_skb);
		if (err < 0) {
			l2cap_send_disconn_req(pi->conn, sk);
			return err;
		}
		__mod_retrans_timer();

		bt_cb(skb)->tx_seq = pi->next_tx_seq;
		pi->next_tx_seq = (pi->next_tx_seq + 1) % 64;

		pi->unacked_frames++;

		if (skb_queue_is_last(TX_QUEUE(sk), skb))
			sk->sk_send_head = NULL;
		else
			sk->sk_send_head = skb_queue_next(TX_QUEUE(sk), skb);
	}

	return 0;
}