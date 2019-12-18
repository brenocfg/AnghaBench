#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int ip6_rt_max_size; int ip6_rt_gc_min_interval; int ip6_rt_gc_timeout; int ip6_rt_gc_interval; int ip6_rt_gc_elasticity; int ip6_rt_mtu_expires; int ip6_rt_min_advmss; scalar_t__ flush_delay; } ;
struct TYPE_15__ {int ip6_rt_gc_expire; TYPE_8__* ip6_null_entry; TYPE_8__* ip6_prohibit_entry; TYPE_6__ sysctl; int /*<<< orphan*/  ip6_dst_ops; TYPE_5__* ip6_blk_hole_entry; } ;
struct net {TYPE_7__ ipv6; } ;
struct dst_entry {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ops; struct dst_entry* path; } ;
struct TYPE_10__ {TYPE_1__ dst; } ;
struct TYPE_16__ {TYPE_2__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; struct dst_entry* path; } ;
struct TYPE_12__ {TYPE_3__ dst; } ;
struct TYPE_13__ {TYPE_4__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int IPV6_MIN_MTU ; 
 int /*<<< orphan*/  ip6_blk_hole_entry_template ; 
 int /*<<< orphan*/  ip6_dst_ops_template ; 
 int /*<<< orphan*/  ip6_null_entry_template ; 
 int /*<<< orphan*/  ip6_prohibit_entry_template ; 
 int /*<<< orphan*/  kfree (TYPE_8__*) ; 
 void* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ip6_route_net_init(struct net *net)
{
	int ret = -ENOMEM;

	memcpy(&net->ipv6.ip6_dst_ops, &ip6_dst_ops_template,
	       sizeof(net->ipv6.ip6_dst_ops));

	net->ipv6.ip6_null_entry = kmemdup(&ip6_null_entry_template,
					   sizeof(*net->ipv6.ip6_null_entry),
					   GFP_KERNEL);
	if (!net->ipv6.ip6_null_entry)
		goto out_ip6_dst_ops;
	net->ipv6.ip6_null_entry->u.dst.path =
		(struct dst_entry *)net->ipv6.ip6_null_entry;
	net->ipv6.ip6_null_entry->u.dst.ops = &net->ipv6.ip6_dst_ops;

#ifdef CONFIG_IPV6_MULTIPLE_TABLES
	net->ipv6.ip6_prohibit_entry = kmemdup(&ip6_prohibit_entry_template,
					       sizeof(*net->ipv6.ip6_prohibit_entry),
					       GFP_KERNEL);
	if (!net->ipv6.ip6_prohibit_entry)
		goto out_ip6_null_entry;
	net->ipv6.ip6_prohibit_entry->u.dst.path =
		(struct dst_entry *)net->ipv6.ip6_prohibit_entry;
	net->ipv6.ip6_prohibit_entry->u.dst.ops = &net->ipv6.ip6_dst_ops;

	net->ipv6.ip6_blk_hole_entry = kmemdup(&ip6_blk_hole_entry_template,
					       sizeof(*net->ipv6.ip6_blk_hole_entry),
					       GFP_KERNEL);
	if (!net->ipv6.ip6_blk_hole_entry)
		goto out_ip6_prohibit_entry;
	net->ipv6.ip6_blk_hole_entry->u.dst.path =
		(struct dst_entry *)net->ipv6.ip6_blk_hole_entry;
	net->ipv6.ip6_blk_hole_entry->u.dst.ops = &net->ipv6.ip6_dst_ops;
#endif

	net->ipv6.sysctl.flush_delay = 0;
	net->ipv6.sysctl.ip6_rt_max_size = 4096;
	net->ipv6.sysctl.ip6_rt_gc_min_interval = HZ / 2;
	net->ipv6.sysctl.ip6_rt_gc_timeout = 60*HZ;
	net->ipv6.sysctl.ip6_rt_gc_interval = 30*HZ;
	net->ipv6.sysctl.ip6_rt_gc_elasticity = 9;
	net->ipv6.sysctl.ip6_rt_mtu_expires = 10*60*HZ;
	net->ipv6.sysctl.ip6_rt_min_advmss = IPV6_MIN_MTU - 20 - 40;

	net->ipv6.ip6_rt_gc_expire = 30*HZ;

	ret = 0;
out:
	return ret;

#ifdef CONFIG_IPV6_MULTIPLE_TABLES
out_ip6_prohibit_entry:
	kfree(net->ipv6.ip6_prohibit_entry);
out_ip6_null_entry:
	kfree(net->ipv6.ip6_null_entry);
#endif
out_ip6_dst_ops:
	goto out;
}