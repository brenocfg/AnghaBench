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
struct socket {scalar_t__ type; struct sock* sk; } ;
struct sockaddr_dn {int dummy; } ;
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  sk_sleep; TYPE_1__* sk_socket; scalar_t__ sk_dst_cache; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int msg_flags; int msg_namelen; int /*<<< orphan*/  msg_iov; scalar_t__ msg_name; } ;
struct kiocb {int dummy; } ;
struct dn_skb_cb {int nsp_flags; } ;
struct dn_scp {size_t segsize_rem; unsigned char services_rem; scalar_t__ seg_total; int /*<<< orphan*/  persist; int /*<<< orphan*/  flowrem_dat; int /*<<< orphan*/  flowrem_oth; int /*<<< orphan*/  persist_fxn; struct sk_buff_head other_xmit_queue; struct sk_buff_head data_xmit_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DN_MAX_NSP_DATA_HEADER ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int EFAULT ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int EOPNOTSUPP ; 
 int EPIPE ; 
 int EWOULDBLOCK ; 
 int MSG_CMSG_COMPAT ; 
 int MSG_DONTWAIT ; 
 int MSG_EOR ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int MSG_OOB ; 
 int MSG_TRYHARD ; 
 unsigned char NSP_FC_MASK ; 
 unsigned char NSP_FC_NONE ; 
 unsigned char NSP_FC_SCMC ; 
 unsigned char NSP_FC_SRC ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SOCK_ASYNC_WAITDATA ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct sk_buff* dn_alloc_send_pskb (struct sock*,scalar_t__,int,int*) ; 
 int dn_check_state (struct sock*,struct sockaddr_dn*,int,long*,int) ; 
 size_t dn_current_mss (struct sock*,int) ; 
 int /*<<< orphan*/  dn_nsp_persist (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_queue_xmit (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dn_nsp_xmit_timeout ; 
 scalar_t__ dn_queue_too_long (struct dn_scp*,struct sk_buff_head*,int) ; 
 int /*<<< orphan*/  dst_negative_advice (scalar_t__*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 scalar_t__ memcpy_fromiovec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sk_stream_error (struct sock*,int,int) ; 
 int /*<<< orphan*/  sk_wait_event (struct sock*,long*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int sock_error (struct sock*) ; 
 int sock_intr_errno (long) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int dn_sendmsg(struct kiocb *iocb, struct socket *sock,
		      struct msghdr *msg, size_t size)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	size_t mss;
	struct sk_buff_head *queue = &scp->data_xmit_queue;
	int flags = msg->msg_flags;
	int err = 0;
	size_t sent = 0;
	int addr_len = msg->msg_namelen;
	struct sockaddr_dn *addr = (struct sockaddr_dn *)msg->msg_name;
	struct sk_buff *skb = NULL;
	struct dn_skb_cb *cb;
	size_t len;
	unsigned char fctype;
	long timeo;

	if (flags & ~(MSG_TRYHARD|MSG_OOB|MSG_DONTWAIT|MSG_EOR|MSG_NOSIGNAL|MSG_MORE|MSG_CMSG_COMPAT))
		return -EOPNOTSUPP;

	if (addr_len && (addr_len != sizeof(struct sockaddr_dn)))
		return -EINVAL;

	lock_sock(sk);
	timeo = sock_sndtimeo(sk, flags & MSG_DONTWAIT);
	/*
	 * The only difference between stream sockets and sequenced packet
	 * sockets is that the stream sockets always behave as if MSG_EOR
	 * has been set.
	 */
	if (sock->type == SOCK_STREAM) {
		if (flags & MSG_EOR) {
			err = -EINVAL;
			goto out;
		}
		flags |= MSG_EOR;
	}


	err = dn_check_state(sk, addr, addr_len, &timeo, flags);
	if (err)
		goto out_err;

	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		err = -EPIPE;
		if (!(flags & MSG_NOSIGNAL))
			send_sig(SIGPIPE, current, 0);
		goto out_err;
	}

	if ((flags & MSG_TRYHARD) && sk->sk_dst_cache)
		dst_negative_advice(&sk->sk_dst_cache);

	mss = scp->segsize_rem;
	fctype = scp->services_rem & NSP_FC_MASK;

	mss = dn_current_mss(sk, flags);

	if (flags & MSG_OOB) {
		queue = &scp->other_xmit_queue;
		if (size > mss) {
			err = -EMSGSIZE;
			goto out;
		}
	}

	scp->persist_fxn = dn_nsp_xmit_timeout;

	while(sent < size) {
		err = sock_error(sk);
		if (err)
			goto out;

		if (signal_pending(current)) {
			err = sock_intr_errno(timeo);
			goto out;
		}

		/*
		 * Calculate size that we wish to send.
		 */
		len = size - sent;

		if (len > mss)
			len = mss;

		/*
		 * Wait for queue size to go down below the window
		 * size.
		 */
		if (dn_queue_too_long(scp, queue, flags)) {
			DEFINE_WAIT(wait);

			if (flags & MSG_DONTWAIT) {
				err = -EWOULDBLOCK;
				goto out;
			}

			prepare_to_wait(sk->sk_sleep, &wait, TASK_INTERRUPTIBLE);
			set_bit(SOCK_ASYNC_WAITDATA, &sk->sk_socket->flags);
			sk_wait_event(sk, &timeo,
				      !dn_queue_too_long(scp, queue, flags));
			clear_bit(SOCK_ASYNC_WAITDATA, &sk->sk_socket->flags);
			finish_wait(sk->sk_sleep, &wait);
			continue;
		}

		/*
		 * Get a suitably sized skb.
		 * 64 is a bit of a hack really, but its larger than any
		 * link-layer headers and has served us well as a good
		 * guess as to their real length.
		 */
		skb = dn_alloc_send_pskb(sk, len + 64 + DN_MAX_NSP_DATA_HEADER,
					 flags & MSG_DONTWAIT, &err);

		if (err)
			break;

		if (!skb)
			continue;

		cb = DN_SKB_CB(skb);

		skb_reserve(skb, 64 + DN_MAX_NSP_DATA_HEADER);

		if (memcpy_fromiovec(skb_put(skb, len), msg->msg_iov, len)) {
			err = -EFAULT;
			goto out;
		}

		if (flags & MSG_OOB) {
			cb->nsp_flags = 0x30;
			if (fctype != NSP_FC_NONE)
				scp->flowrem_oth--;
		} else {
			cb->nsp_flags = 0x00;
			if (scp->seg_total == 0)
				cb->nsp_flags |= 0x20;

			scp->seg_total += len;

			if (((sent + len) == size) && (flags & MSG_EOR)) {
				cb->nsp_flags |= 0x40;
				scp->seg_total = 0;
				if (fctype == NSP_FC_SCMC)
					scp->flowrem_dat--;
			}
			if (fctype == NSP_FC_SRC)
				scp->flowrem_dat--;
		}

		sent += len;
		dn_nsp_queue_xmit(sk, skb, sk->sk_allocation, flags & MSG_OOB);
		skb = NULL;

		scp->persist = dn_nsp_persist(sk);

	}
out:

	kfree_skb(skb);

	release_sock(sk);

	return sent ? sent : err;

out_err:
	err = sk_stream_error(sk, flags, err);
	release_sock(sk);
	return err;
}