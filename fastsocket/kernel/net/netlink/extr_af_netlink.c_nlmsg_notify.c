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
typedef  int u32 ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  users; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int nlmsg_multicast (struct sock*,struct sk_buff*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int nlmsg_unicast (struct sock*,struct sk_buff*,int) ; 

int nlmsg_notify(struct sock *sk, struct sk_buff *skb, u32 pid,
		 unsigned int group, int report, gfp_t flags)
{
	int err = 0;

	if (group) {
		int exclude_pid = 0;

		if (report) {
			atomic_inc(&skb->users);
			exclude_pid = pid;
		}

		/* errors reported via destination sk->sk_err, but propagate
		 * delivery errors if NETLINK_BROADCAST_ERROR flag is set */
		err = nlmsg_multicast(sk, skb, exclude_pid, group, flags);
	}

	if (report) {
		int err2;

		err2 = nlmsg_unicast(sk, skb, pid);
		if (!err || err == -ESRCH)
			err = err2;
	}

	return err;
}