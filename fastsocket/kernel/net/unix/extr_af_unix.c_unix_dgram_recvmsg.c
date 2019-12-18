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
typedef  int /*<<< orphan*/  tmp_scm ;
struct unix_sock {int /*<<< orphan*/  readlock; int /*<<< orphan*/  peer_wait; } ;
struct socket {struct sock* sk; } ;
struct sock_iocb {struct scm_cookie* scm; } ;
struct sock {scalar_t__ sk_type; int sk_shutdown; } ;
struct sk_buff {size_t len; int /*<<< orphan*/  sk; } ;
struct scm_cookie {int /*<<< orphan*/  fp; } ;
struct msghdr {int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_flags; scalar_t__ msg_name; scalar_t__ msg_namelen; } ;
struct kiocb {int dummy; } ;
struct TYPE_2__ {scalar_t__ fp; int /*<<< orphan*/  cred; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int MSG_DONTWAIT ; 
 int MSG_OOB ; 
 int MSG_PEEK ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 int RCV_SHUTDOWN ; 
 scalar_t__ SOCK_SEQPACKET ; 
 TYPE_1__ UNIXCB (struct sk_buff*) ; 
 struct sock_iocb* kiocb_to_siocb (struct kiocb*) ; 
 int /*<<< orphan*/  memset (struct scm_cookie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scm_fp_dup (scalar_t__) ; 
 int /*<<< orphan*/  scm_recv (struct socket*,struct msghdr*,struct scm_cookie*,int) ; 
 int /*<<< orphan*/  scm_set_cred (struct scm_cookie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_copy_datagram_iovec (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  unix_copy_addr (struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_detach_fds (struct scm_cookie*,struct sk_buff*) ; 
 int /*<<< orphan*/  unix_set_secdata (struct scm_cookie*,struct sk_buff*) ; 
 struct unix_sock* unix_sk (struct sock*) ; 
 int /*<<< orphan*/  unix_state_lock (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unix_dgram_recvmsg(struct kiocb *iocb, struct socket *sock,
			      struct msghdr *msg, size_t size,
			      int flags)
{
	struct sock_iocb *siocb = kiocb_to_siocb(iocb);
	struct scm_cookie tmp_scm;
	struct sock *sk = sock->sk;
	struct unix_sock *u = unix_sk(sk);
	int noblock = flags & MSG_DONTWAIT;
	struct sk_buff *skb;
	int err;

	err = -EOPNOTSUPP;
	if (flags&MSG_OOB)
		goto out;

	msg->msg_namelen = 0;

	mutex_lock(&u->readlock);

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	if (!skb) {
		unix_state_lock(sk);
		/* Signal EOF on disconnected non-blocking SEQPACKET socket. */
		if (sk->sk_type == SOCK_SEQPACKET && err == -EAGAIN &&
		    (sk->sk_shutdown & RCV_SHUTDOWN))
			err = 0;
		unix_state_unlock(sk);
		goto out_unlock;
	}

	wake_up_interruptible_sync(&u->peer_wait);

	if (msg->msg_name)
		unix_copy_addr(msg, skb->sk);

	if (size > skb->len)
		size = skb->len;
	else if (size < skb->len)
		msg->msg_flags |= MSG_TRUNC;

	err = skb_copy_datagram_iovec(skb, 0, msg->msg_iov, size);
	if (err)
		goto out_free;

	if (!siocb->scm) {
		siocb->scm = &tmp_scm;
		memset(&tmp_scm, 0, sizeof(tmp_scm));
	}
	scm_set_cred(siocb->scm, UNIXCB(skb).pid, UNIXCB(skb).cred);
	unix_set_secdata(siocb->scm, skb);

	if (!(flags & MSG_PEEK)) {
		if (UNIXCB(skb).fp)
			unix_detach_fds(siocb->scm, skb);
	} else {
		/* It is questionable: on PEEK we could:
		   - do not return fds - good, but too simple 8)
		   - return fds, and do not return them on read (old strategy,
		     apparently wrong)
		   - clone fds (I chose it for now, it is the most universal
		     solution)

		   POSIX 1003.1g does not actually define this clearly
		   at all. POSIX 1003.1g doesn't define a lot of things
		   clearly however!

		*/
		if (UNIXCB(skb).fp)
			siocb->scm->fp = scm_fp_dup(UNIXCB(skb).fp);
	}
	err = size;

	scm_recv(sock, msg, siocb->scm, flags);

out_free:
	skb_free_datagram(sk, skb);
out_unlock:
	mutex_unlock(&u->readlock);
out:
	return err;
}