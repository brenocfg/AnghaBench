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
struct sock {int dummy; } ;
struct TYPE_2__ {struct sock* fibnl; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  NETLINK_FIB_LOOKUP ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct sock* netlink_kernel_create (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_fib_input ; 

__attribute__((used)) static int nl_fib_lookup_init(struct net *net)
{
	struct sock *sk;
	sk = netlink_kernel_create(net, NETLINK_FIB_LOOKUP, 0,
				   nl_fib_input, NULL, THIS_MODULE);
	if (sk == NULL)
		return -EAFNOSUPPORT;
	net->ipv4.fibnl = sk;
	return 0;
}