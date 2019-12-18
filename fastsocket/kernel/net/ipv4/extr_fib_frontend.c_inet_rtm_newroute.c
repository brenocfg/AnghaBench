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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct net {int dummy; } ;
struct fib_table {int (* tb_insert ) (struct fib_table*,struct fib_config*) ;} ;
struct fib_config {int /*<<< orphan*/  fc_table; } ;

/* Variables and functions */
 int ENOBUFS ; 
 struct fib_table* fib_new_table (struct net*,int /*<<< orphan*/ ) ; 
 int rtm_to_fib_config (struct net*,struct sk_buff*,struct nlmsghdr*,struct fib_config*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int stub1 (struct fib_table*,struct fib_config*) ; 

__attribute__((used)) static int inet_rtm_newroute(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg)
{
	struct net *net = sock_net(skb->sk);
	struct fib_config cfg;
	struct fib_table *tb;
	int err;

	err = rtm_to_fib_config(net, skb, nlh, &cfg);
	if (err < 0)
		goto errout;

	tb = fib_new_table(net, cfg.fc_table);
	if (tb == NULL) {
		err = -ENOBUFS;
		goto errout;
	}

	err = tb->tb_insert(tb, &cfg);
errout:
	return err;
}