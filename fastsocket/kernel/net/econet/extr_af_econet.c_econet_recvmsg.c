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
struct socket {struct sock* sk; } ;
struct sockaddr_ec {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_stamp; } ;
struct sk_buff {size_t len; int /*<<< orphan*/  cb; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  data; } ;
struct msghdr {int /*<<< orphan*/  msg_namelen; scalar_t__ msg_name; int /*<<< orphan*/  msg_iov; int /*<<< orphan*/  msg_flags; } ;
struct kiocb {int dummy; } ;
struct TYPE_2__ {int msg_namelen; } ;

/* Variables and functions */
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 int /*<<< orphan*/  econet_mutex ; 
 TYPE_1__* m ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memcpy_toiovec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 

__attribute__((used)) static int econet_recvmsg(struct kiocb *iocb, struct socket *sock,
			  struct msghdr *msg, size_t len, int flags)
{
	struct sock *sk = sock->sk;
	struct sk_buff *skb;
	size_t copied;
	int err;

	msg->msg_namelen = 0;

	mutex_lock(&econet_mutex);

	/*
	 *	Call the generic datagram receiver. This handles all sorts
	 *	of horrible races and re-entrancy so we can forget about it
	 *	in the protocol layers.
	 *
	 *	Now it will return ENETDOWN, if device have just gone down,
	 *	but then it will block.
	 */

	skb=skb_recv_datagram(sk,flags,flags&MSG_DONTWAIT,&err);

	/*
	 *	An error occurred so return it. Because skb_recv_datagram()
	 *	handles the blocking we don't see and worry about blocking
	 *	retries.
	 */

	if(skb==NULL)
		goto out;

	/*
	 *	You lose any data beyond the buffer you gave. If it worries a
	 *	user program they can ask the device for its MTU anyway.
	 */

	copied = skb->len;
	if (copied > len)
	{
		copied=len;
		msg->msg_flags|=MSG_TRUNC;
	}

	/* We can't use skb_copy_datagram here */
	err = memcpy_toiovec(msg->msg_iov, skb->data, copied);
	if (err)
		goto out_free;
	sk->sk_stamp = skb->tstamp;

	if (msg->msg_name) {
		m->msg_namelen = sizeof(struct sockaddr_ec);
		memcpy(msg->msg_name, skb->cb, msg->msg_namelen);
	}
	/*
	 *	Free or return the buffer as appropriate. Again this
	 *	hides all the races and re-entrancy issues from us.
	 */
	err = copied;

out_free:
	skb_free_datagram(sk, skb);
out:
	mutex_unlock(&econet_mutex);
	return err;
}