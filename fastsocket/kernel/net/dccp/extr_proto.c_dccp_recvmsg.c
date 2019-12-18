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
struct sock {scalar_t__ sk_state; int sk_shutdown; scalar_t__ sk_err; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {size_t len; } ;
struct msghdr {int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_flags; } ;
struct kiocb {int dummy; } ;
struct dccp_hdr {int dccph_type; } ;

/* Variables and functions */
 scalar_t__ DCCP_CLOSED ; 
 scalar_t__ DCCP_LISTEN ; 
#define  DCCP_PKT_CLOSE 132 
#define  DCCP_PKT_CLOSEREQ 131 
#define  DCCP_PKT_DATA 130 
#define  DCCP_PKT_DATAACK 129 
#define  DCCP_PKT_RESET 128 
 size_t EAGAIN ; 
 size_t EFAULT ; 
 size_t ENOTCONN ; 
 int MSG_PEEK ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 int RCV_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dccp_finish_passive_close (struct sock*) ; 
 struct dccp_hdr* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_packet_name (int) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_eat_skb (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_wait_data (struct sock*,long*) ; 
 scalar_t__ skb_copy_datagram_iovec (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 size_t sock_error (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 size_t sock_intr_errno (long) ; 
 long sock_rcvtimeo (struct sock*,int) ; 

int dccp_recvmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,
		 size_t len, int nonblock, int flags, int *addr_len)
{
	const struct dccp_hdr *dh;
	long timeo;

	lock_sock(sk);

	if (sk->sk_state == DCCP_LISTEN) {
		len = -ENOTCONN;
		goto out;
	}

	timeo = sock_rcvtimeo(sk, nonblock);

	do {
		struct sk_buff *skb = skb_peek(&sk->sk_receive_queue);

		if (skb == NULL)
			goto verify_sock_status;

		dh = dccp_hdr(skb);

		switch (dh->dccph_type) {
		case DCCP_PKT_DATA:
		case DCCP_PKT_DATAACK:
			goto found_ok_skb;

		case DCCP_PKT_CLOSE:
		case DCCP_PKT_CLOSEREQ:
			if (!(flags & MSG_PEEK))
				dccp_finish_passive_close(sk);
			/* fall through */
		case DCCP_PKT_RESET:
			dccp_pr_debug("found fin (%s) ok!\n",
				      dccp_packet_name(dh->dccph_type));
			len = 0;
			goto found_fin_ok;
		default:
			dccp_pr_debug("packet_type=%s\n",
				      dccp_packet_name(dh->dccph_type));
			sk_eat_skb(sk, skb, 0);
		}
verify_sock_status:
		if (sock_flag(sk, SOCK_DONE)) {
			len = 0;
			break;
		}

		if (sk->sk_err) {
			len = sock_error(sk);
			break;
		}

		if (sk->sk_shutdown & RCV_SHUTDOWN) {
			len = 0;
			break;
		}

		if (sk->sk_state == DCCP_CLOSED) {
			if (!sock_flag(sk, SOCK_DONE)) {
				/* This occurs when user tries to read
				 * from never connected socket.
				 */
				len = -ENOTCONN;
				break;
			}
			len = 0;
			break;
		}

		if (!timeo) {
			len = -EAGAIN;
			break;
		}

		if (signal_pending(current)) {
			len = sock_intr_errno(timeo);
			break;
		}

		sk_wait_data(sk, &timeo);
		continue;
	found_ok_skb:
		if (len > skb->len)
			len = skb->len;
		else if (len < skb->len)
			msg->msg_flags |= MSG_TRUNC;

		if (skb_copy_datagram_iovec(skb, 0, msg->msg_iov, len)) {
			/* Exception. Bailout! */
			len = -EFAULT;
			break;
		}
	found_fin_ok:
		if (!(flags & MSG_PEEK))
			sk_eat_skb(sk, skb, 0);
		break;
	} while (1);
out:
	release_sock(sk);
	return len;
}