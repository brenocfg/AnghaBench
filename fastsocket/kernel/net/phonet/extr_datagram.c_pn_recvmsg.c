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
struct sockaddr_pn {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/ * msg_name; int /*<<< orphan*/  msg_iov; } ;
struct kiocb {int dummy; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 int MSG_OOB ; 
 int MSG_TRUNC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_pn*,int) ; 
 int /*<<< orphan*/  pn_skb_get_src_sockaddr (struct sk_buff*,struct sockaddr_pn*) ; 
 int skb_copy_datagram_iovec (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 

__attribute__((used)) static int pn_recvmsg(struct kiocb *iocb, struct sock *sk,
			struct msghdr *msg, size_t len, int noblock,
			int flags, int *addr_len)
{
	struct sk_buff *skb = NULL;
	struct sockaddr_pn sa;
	int rval = -EOPNOTSUPP;
	int copylen;

	if (flags & MSG_OOB)
		goto out_nofree;

	skb = skb_recv_datagram(sk, flags, noblock, &rval);
	if (skb == NULL)
		goto out_nofree;

	pn_skb_get_src_sockaddr(skb, &sa);

	copylen = skb->len;
	if (len < copylen) {
		msg->msg_flags |= MSG_TRUNC;
		copylen = len;
	}

	rval = skb_copy_datagram_iovec(skb, 0, msg->msg_iov, copylen);
	if (rval) {
		rval = -EFAULT;
		goto out;
	}

	rval = (flags & MSG_TRUNC) ? skb->len : copylen;

	if (msg->msg_name != NULL) {
		memcpy(msg->msg_name, &sa, sizeof(sa));
		*addr_len = sizeof(sa);
	}

out:
	skb_free_datagram(sk, skb);

out_nofree:
	return rval;
}