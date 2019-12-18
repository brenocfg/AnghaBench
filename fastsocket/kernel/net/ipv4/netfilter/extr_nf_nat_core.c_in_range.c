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
struct nf_nat_range {int flags; int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  max_ip; int /*<<< orphan*/  min_ip; } ;
struct nf_nat_protocol {scalar_t__ (* in_range ) (struct nf_conntrack_tuple const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  protonum; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_3__ dst; TYPE_2__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_NAT_MANIP_SRC ; 
 int IP_NAT_RANGE_MAP_IPS ; 
 int IP_NAT_RANGE_PROTO_SPECIFIED ; 
 struct nf_nat_protocol* __nf_nat_proto_find (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ stub1 (struct nf_conntrack_tuple const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
in_range(const struct nf_conntrack_tuple *tuple,
	 const struct nf_nat_range *range)
{
	const struct nf_nat_protocol *proto;
	int ret = 0;

	/* If we are supposed to map IPs, then we must be in the
	   range specified, otherwise let this drag us onto a new src IP. */
	if (range->flags & IP_NAT_RANGE_MAP_IPS) {
		if (ntohl(tuple->src.u3.ip) < ntohl(range->min_ip) ||
		    ntohl(tuple->src.u3.ip) > ntohl(range->max_ip))
			return 0;
	}

	rcu_read_lock();
	proto = __nf_nat_proto_find(tuple->dst.protonum);
	if (!(range->flags & IP_NAT_RANGE_PROTO_SPECIFIED) ||
	    proto->in_range(tuple, IP_NAT_MANIP_SRC,
			    &range->min, &range->max))
		ret = 1;
	rcu_read_unlock();

	return ret;
}