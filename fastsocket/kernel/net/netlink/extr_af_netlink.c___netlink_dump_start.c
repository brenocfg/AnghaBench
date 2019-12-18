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
struct sock {int /*<<< orphan*/  sk_protocol; } ;
struct sk_buff {int /*<<< orphan*/  users; } ;
struct nlmsghdr {int dummy; } ;
struct netlink_sock {int /*<<< orphan*/  cb_mutex; struct netlink_callback* cb; } ;
struct netlink_dump_control {int /*<<< orphan*/  min_dump_alloc; int /*<<< orphan*/  module; int /*<<< orphan*/  done; int /*<<< orphan*/  dump; } ;
struct netlink_callback_extended {int /*<<< orphan*/  module; int /*<<< orphan*/  min_dump_alloc; } ;
struct netlink_callback {struct sk_buff* skb; struct nlmsghdr const* nlh; int /*<<< orphan*/  done; int /*<<< orphan*/  dump; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EBUSY ; 
 int ECONNREFUSED ; 
 int EINTR ; 
 int ENOBUFS ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NETLINK_CALLBACK_TOTAL_SIZE ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct netlink_callback* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_destroy_callback (struct netlink_callback*) ; 
 int netlink_dump (struct sock*) ; 
 struct sock* netlink_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netlink_callback_extended* nl_callback_extended (struct netlink_callback*) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int __netlink_dump_start(struct sock *ssk, struct sk_buff *skb,
		       const struct nlmsghdr *nlh,
		       struct netlink_dump_control *control)
{
	struct netlink_callback *cb;
	struct netlink_callback_extended *cb_ext;
	struct sock *sk;
	struct netlink_sock *nlk;
	int ret;

	cb = kzalloc(NETLINK_CALLBACK_TOTAL_SIZE, GFP_KERNEL);
	if (cb == NULL)
		return -ENOBUFS;

	cb_ext = nl_callback_extended(cb);
	cb->dump = control->dump;
	cb->done = control->done;
	cb->nlh = nlh;
	cb_ext->module = control->module;
	cb_ext->min_dump_alloc = control->min_dump_alloc;
	atomic_inc(&skb->users);
	cb->skb = skb;

	sk = netlink_lookup(sock_net(ssk), ssk->sk_protocol, NETLINK_CB(skb).pid);
	if (sk == NULL) {
		netlink_destroy_callback(cb);
		return -ECONNREFUSED;
	}
	nlk = nlk_sk(sk);

	mutex_lock(nlk->cb_mutex);
	/* A dump is in progress... */
	if (nlk->cb) {
		mutex_unlock(nlk->cb_mutex);
		netlink_destroy_callback(cb);
		ret = -EBUSY;
		goto out;
	}
	/* add reference of module which cb->dump belongs to */
	if (!try_module_get(cb_ext->module)) {
		mutex_unlock(nlk->cb_mutex);
		netlink_destroy_callback(cb);
		ret = -EPROTONOSUPPORT;
		goto out;
	}

	nlk->cb = cb;
	mutex_unlock(nlk->cb_mutex);

	ret = netlink_dump(sk);
out:
	sock_put(sk);

	if (ret)
		return ret;

	/* We successfully started a dump, by returning -EINTR we
	 * signal not to send ACK even if it was requested.
	 */
	return -EINTR;
}