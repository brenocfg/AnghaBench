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
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_type; scalar_t__ sk_state; struct sk_buff* sk_send_head; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int msg_flags; } ;
struct l2cap_pinfo {int mode; size_t omtu; size_t max_pdu_size; } ;
struct kiocb {int dummy; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ERR (struct sk_buff*) ; 
#define  L2CAP_MODE_BASIC 130 
#define  L2CAP_MODE_ERTM 129 
#define  L2CAP_MODE_STREAMING 128 
 int /*<<< orphan*/  L2CAP_SDU_UNSEGMENTED ; 
 int MSG_OOB ; 
 int PTR_ERR (struct sk_buff*) ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int /*<<< orphan*/  TX_QUEUE (struct sock*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* l2cap_create_basic_pdu (struct sock*,struct msghdr*,size_t) ; 
 struct sk_buff* l2cap_create_connless_pdu (struct sock*,struct msghdr*,size_t) ; 
 struct sk_buff* l2cap_create_iframe_pdu (struct sock*,struct msghdr*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int l2cap_do_send (struct sock*,struct sk_buff*) ; 
 int l2cap_ertm_send (struct sock*) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 int l2cap_sar_segment_sdu (struct sock*,struct msghdr*,size_t) ; 
 int l2cap_streaming_send (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int sock_error (struct sock*) ; 

__attribute__((used)) static int l2cap_sock_sendmsg(struct kiocb *iocb, struct socket *sock, struct msghdr *msg, size_t len)
{
	struct sock *sk = sock->sk;
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	struct sk_buff *skb;
	u16 control;
	int err;

	BT_DBG("sock %p, sk %p", sock, sk);

	err = sock_error(sk);
	if (err)
		return err;

	if (msg->msg_flags & MSG_OOB)
		return -EOPNOTSUPP;

	/* Check outgoing MTU */
	if (sk->sk_type == SOCK_SEQPACKET && pi->mode == L2CAP_MODE_BASIC
			&& len > pi->omtu)
		return -EINVAL;

	lock_sock(sk);

	if (sk->sk_state != BT_CONNECTED) {
		err = -ENOTCONN;
		goto done;
	}

	/* Connectionless channel */
	if (sk->sk_type == SOCK_DGRAM) {
		skb = l2cap_create_connless_pdu(sk, msg, len);
		err = l2cap_do_send(sk, skb);
		goto done;
	}

	switch (pi->mode) {
	case L2CAP_MODE_BASIC:
		/* Create a basic PDU */
		skb = l2cap_create_basic_pdu(sk, msg, len);
		if (IS_ERR(skb)) {
			err = PTR_ERR(skb);
			goto done;
		}

		err = l2cap_do_send(sk, skb);
		if (!err)
			err = len;
		break;

	case L2CAP_MODE_ERTM:
	case L2CAP_MODE_STREAMING:
		/* Entire SDU fits into one PDU */
		if (len <= pi->max_pdu_size) {
			control = L2CAP_SDU_UNSEGMENTED;
			skb = l2cap_create_iframe_pdu(sk, msg, len, control, 0);
			if (IS_ERR(skb)) {
				err = PTR_ERR(skb);
				goto done;
			}
			__skb_queue_tail(TX_QUEUE(sk), skb);
			if (sk->sk_send_head == NULL)
				sk->sk_send_head = skb;
		} else {
		/* Segment SDU into multiples PDUs */
			err = l2cap_sar_segment_sdu(sk, msg, len);
			if (err < 0)
				goto done;
		}

		if (pi->mode == L2CAP_MODE_STREAMING)
			err = l2cap_streaming_send(sk);
		else
			err = l2cap_ertm_send(sk);

		if (!err)
			err = len;
		break;

	default:
		BT_DBG("bad state %1.1x", pi->mode);
		err = -EINVAL;
	}

done:
	release_sock(sk);
	return err;
}