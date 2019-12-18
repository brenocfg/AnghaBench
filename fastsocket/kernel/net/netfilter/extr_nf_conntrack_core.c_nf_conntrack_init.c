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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * destroy_conntrack ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  ip_ct_attach ; 
 scalar_t__ net_eq (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nf_conntrack_attach ; 
 int /*<<< orphan*/  nf_conntrack_cleanup_init_net () ; 
 int nf_conntrack_init_init_net () ; 
 int nf_conntrack_init_net (struct net*) ; 
 int /*<<< orphan*/  nf_ct_destroy ; 
 int /*<<< orphan*/  nf_ct_nat_offset ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nf_conntrack_init(struct net *net)
{
	int ret;

	if (net_eq(net, &init_net)) {
		ret = nf_conntrack_init_init_net();
		if (ret < 0)
			goto out_init_net;
	}
	ret = nf_conntrack_init_net(net);
	if (ret < 0)
		goto out_net;

	if (net_eq(net, &init_net)) {
		/* For use by REJECT target */
		rcu_assign_pointer(ip_ct_attach, nf_conntrack_attach);
		rcu_assign_pointer(nf_ct_destroy, destroy_conntrack);

		/* Howto get NAT offsets */
		rcu_assign_pointer(nf_ct_nat_offset, NULL);
	}
	return 0;

out_net:
	if (net_eq(net, &init_net))
		nf_conntrack_cleanup_init_net();
out_init_net:
	return ret;
}