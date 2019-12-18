#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dst_entry {TYPE_3__* dev; } ;
struct TYPE_5__ {struct dst_entry dst; } ;
struct rtable {TYPE_2__ u; } ;
struct TYPE_4__ {int sysctl_icmp_ratemask; int /*<<< orphan*/  sysctl_icmp_ratelimit; } ;
struct net {TYPE_1__ ipv4; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int ICMP_DEST_UNREACH ; 
 int ICMP_FRAG_NEEDED ; 
 int IFF_LOOPBACK ; 
 int NR_ICMP_TYPES ; 
 int xrlim_allow (struct dst_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int icmpv4_xrlim_allow(struct net *net, struct rtable *rt,
		int type, int code)
{
	struct dst_entry *dst = &rt->u.dst;
	int rc = 1;

	if (type > NR_ICMP_TYPES)
		goto out;

	/* Don't limit PMTU discovery. */
	if (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED)
		goto out;

	/* No rate limit on loopback */
	if (dst->dev && (dst->dev->flags&IFF_LOOPBACK))
		goto out;

	/* Limit if icmp type is enabled in ratemask. */
	if ((1 << type) & net->ipv4.sysctl_icmp_ratemask)
		rc = xrlim_allow(dst, net->ipv4.sysctl_icmp_ratelimit);
out:
	return rc;
}