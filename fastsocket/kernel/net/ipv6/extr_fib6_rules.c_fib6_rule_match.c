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
struct flowi {int /*<<< orphan*/  fl6_flowlabel; int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  fl6_dst; } ;
struct fib_rule {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {scalar_t__ plen; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {scalar_t__ plen; int /*<<< orphan*/  addr; } ;
struct fib6_rule {int tclass; TYPE_3__ common; TYPE_2__ src; TYPE_1__ dst; } ;

/* Variables and functions */
 int FIB_RULE_FIND_SADDR ; 
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int /*<<< orphan*/  ipv6_prefix_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib6_rule_match(struct fib_rule *rule, struct flowi *fl, int flags)
{
	struct fib6_rule *r = (struct fib6_rule *) rule;

	if (r->dst.plen &&
	    !ipv6_prefix_equal(&fl->fl6_dst, &r->dst.addr, r->dst.plen))
		return 0;

	/*
	 * If FIB_RULE_FIND_SADDR is set and we do not have a
	 * source address for the traffic, we defer check for
	 * source address.
	 */
	if (r->src.plen) {
		if (flags & RT6_LOOKUP_F_HAS_SADDR) {
			if (!ipv6_prefix_equal(&fl->fl6_src, &r->src.addr,
					       r->src.plen))
				return 0;
		} else if (!(r->common.flags & FIB_RULE_FIND_SADDR))
			return 0;
	}

	if (r->tclass && r->tclass != ((ntohl(fl->fl6_flowlabel) >> 20) & 0xff))
		return 0;

	return 1;
}