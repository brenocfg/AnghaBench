#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtentry {int rt_flags; TYPE_1__* rt_gateway; } ;
struct radix_node {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int RTF_HOST ; 
 int RTF_STATIC ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 TYPE_2__* SIN6 (TYPE_1__*) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_mask (struct rtentry*) ; 
 int rtrequest_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rt6_deleteroute(
	struct radix_node *rn,
	void *arg)
{
	struct rtentry *rt = (struct rtentry *)rn;
	struct in6_addr *gate = (struct in6_addr *)arg;

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);

	RT_LOCK(rt);
	if (rt->rt_gateway == NULL || rt->rt_gateway->sa_family != AF_INET6) {
		RT_UNLOCK(rt);
		return (0);
	}

	if (!IN6_ARE_ADDR_EQUAL(gate, &SIN6(rt->rt_gateway)->sin6_addr)) {
		RT_UNLOCK(rt);
		return (0);
	}
	/*
	 * Do not delete a static route.
	 * XXX: this seems to be a bit ad-hoc. Should we consider the
	 * 'cloned' bit instead?
	 */
	if ((rt->rt_flags & RTF_STATIC) != 0) {
		RT_UNLOCK(rt);
		return (0);
	}
	/*
	 * We delete only host route. This means, in particular, we don't
	 * delete default route.
	 */
	if ((rt->rt_flags & RTF_HOST) == 0) {
		RT_UNLOCK(rt);
		return (0);
	}

	/*
	 * Safe to drop rt_lock and use rt_key, rt_gateway, since holding
	 * rnh_lock here prevents another thread from calling rt_setgate()
	 * on this route.
	 */
	RT_UNLOCK(rt);
	return (rtrequest_locked(RTM_DELETE, rt_key(rt), rt->rt_gateway,
	    rt_mask(rt), rt->rt_flags, 0));
}