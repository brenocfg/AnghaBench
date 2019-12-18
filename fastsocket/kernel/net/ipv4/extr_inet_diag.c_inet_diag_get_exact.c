#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; int /*<<< orphan*/  nlmsg_type; } ;
struct inet_timewait_sock {int dummy; } ;
struct inet_hashinfo {int dummy; } ;
struct TYPE_3__ {scalar_t__* idiag_cookie; int /*<<< orphan*/  idiag_if; int /*<<< orphan*/  idiag_sport; int /*<<< orphan*/ * idiag_src; int /*<<< orphan*/  idiag_dport; int /*<<< orphan*/ * idiag_dst; } ;
struct inet_diag_req {scalar_t__ idiag_family; int /*<<< orphan*/  idiag_ext; TYPE_1__ id; } ;
struct inet_diag_msg {int dummy; } ;
struct inet_diag_meminfo {int dummy; } ;
struct inet_diag_handler {scalar_t__ idiag_info_size; struct inet_hashinfo* idiag_hashinfo; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ESTALE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ INET_DIAG_NOCOOKIE ; 
 scalar_t__ IS_ERR (struct inet_diag_handler const*) ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 struct inet_diag_req* NLMSG_DATA (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  NLMSG_SPACE (scalar_t__) ; 
 int PTR_ERR (struct inet_diag_handler const*) ; 
 scalar_t__ TCP_TIME_WAIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idiagnl ; 
 struct sock* inet6_lookup (int /*<<< orphan*/ *,struct inet_hashinfo*,struct in6_addr*,int /*<<< orphan*/ ,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_diag_handler* inet_diag_lock_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_diag_unlock_handler (struct inet_diag_handler const*) ; 
 struct sock* inet_lookup (int /*<<< orphan*/ *,struct inet_hashinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sk_diag_fill (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int inet_diag_get_exact(struct sk_buff *in_skb,
			       const struct nlmsghdr *nlh)
{
	int err;
	struct sock *sk;
	struct inet_diag_req *req = NLMSG_DATA(nlh);
	struct sk_buff *rep;
	struct inet_hashinfo *hashinfo;
	const struct inet_diag_handler *handler;

	handler = inet_diag_lock_handler(nlh->nlmsg_type);
	if (IS_ERR(handler)) {
		err = PTR_ERR(handler);
		goto unlock;
	}

	hashinfo = handler->idiag_hashinfo;
	err = -EINVAL;

	if (req->idiag_family == AF_INET) {
		sk = inet_lookup(&init_net, hashinfo, req->id.idiag_dst[0],
				 req->id.idiag_dport, req->id.idiag_src[0],
				 req->id.idiag_sport, req->id.idiag_if);
	}
#if defined(CONFIG_IPV6) || defined (CONFIG_IPV6_MODULE)
	else if (req->idiag_family == AF_INET6) {
		sk = inet6_lookup(&init_net, hashinfo,
				  (struct in6_addr *)req->id.idiag_dst,
				  req->id.idiag_dport,
				  (struct in6_addr *)req->id.idiag_src,
				  req->id.idiag_sport,
				  req->id.idiag_if);
	}
#endif
	else {
		goto unlock;
	}

	err = -ENOENT;
	if (sk == NULL)
		goto unlock;

	err = -ESTALE;
	if ((req->id.idiag_cookie[0] != INET_DIAG_NOCOOKIE ||
	     req->id.idiag_cookie[1] != INET_DIAG_NOCOOKIE) &&
	    ((u32)(unsigned long)sk != req->id.idiag_cookie[0] ||
	     (u32)((((unsigned long)sk) >> 31) >> 1) != req->id.idiag_cookie[1]))
		goto out;

	err = -ENOMEM;
	rep = alloc_skb(NLMSG_SPACE((sizeof(struct inet_diag_msg) +
				     sizeof(struct inet_diag_meminfo) +
				     handler->idiag_info_size + 64)),
			GFP_KERNEL);
	if (!rep)
		goto out;

	err = sk_diag_fill(sk, rep, req->idiag_ext,
			   NETLINK_CB(in_skb).pid,
			   nlh->nlmsg_seq, 0, nlh);
	if (err < 0) {
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(rep);
		goto out;
	}
	err = netlink_unicast(idiagnl, rep, NETLINK_CB(in_skb).pid,
			      MSG_DONTWAIT);
	if (err > 0)
		err = 0;

out:
	if (sk) {
		if (sk->sk_state == TCP_TIME_WAIT)
			inet_twsk_put((struct inet_timewait_sock *)sk);
		else
			sock_put(sk);
	}
unlock:
	inet_diag_unlock_handler(handler);
	return err;
}