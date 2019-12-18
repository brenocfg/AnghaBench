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
struct sockaddr_pn {scalar_t__ spn_family; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int msg_flags; int msg_namelen; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/ * msg_name; } ;
struct kiocb {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_PHONET ; 
 int EAFNOSUPPORT ; 
 int EDESTADDRREQ ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ MAX_PHONET_HEADER ; 
 int MSG_DONTWAIT ; 
 int MSG_OOB ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int memcpy_fromiovec (void*,int /*<<< orphan*/ ,size_t) ; 
 int pn_skb_send (struct sock*,struct sk_buff*,struct sockaddr_pn*) ; 
 scalar_t__ skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,scalar_t__,int,int*) ; 

__attribute__((used)) static int pn_sendmsg(struct kiocb *iocb, struct sock *sk,
			struct msghdr *msg, size_t len)
{
	struct sockaddr_pn *target;
	struct sk_buff *skb;
	int err;

	if (msg->msg_flags & MSG_OOB)
		return -EOPNOTSUPP;

	if (msg->msg_name == NULL)
		return -EDESTADDRREQ;

	if (msg->msg_namelen < sizeof(struct sockaddr_pn))
		return -EINVAL;

	target = (struct sockaddr_pn *)msg->msg_name;
	if (target->spn_family != AF_PHONET)
		return -EAFNOSUPPORT;

	skb = sock_alloc_send_skb(sk, MAX_PHONET_HEADER + len,
					msg->msg_flags & MSG_DONTWAIT, &err);
	if (skb == NULL)
		return err;
	skb_reserve(skb, MAX_PHONET_HEADER);

	err = memcpy_fromiovec((void *)skb_put(skb, len), msg->msg_iov, len);
	if (err < 0) {
		kfree_skb(skb);
		return err;
	}

	/*
	 * Fill in the Phonet header and
	 * finally pass the packet forwards.
	 */
	err = pn_skb_send(sk, skb, target);

	/* If ok, return len. */
	return (err >= 0) ? len : err;
}