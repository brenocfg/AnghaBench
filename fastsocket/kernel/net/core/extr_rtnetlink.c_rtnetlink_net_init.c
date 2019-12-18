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
struct sock {int dummy; } ;
struct net {struct sock* rtnl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NETLINK_ROUTE ; 
 int /*<<< orphan*/  RTNLGRP_MAX ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct sock* netlink_kernel_create (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnetlink_rcv ; 
 int /*<<< orphan*/  rtnl_mutex ; 

__attribute__((used)) static int rtnetlink_net_init(struct net *net)
{
	struct sock *sk;
	sk = netlink_kernel_create(net, NETLINK_ROUTE, RTNLGRP_MAX,
				   rtnetlink_rcv, &rtnl_mutex, THIS_MODULE);
	if (!sk)
		return -ENOMEM;
	net->rtnl = sk;
	return 0;
}