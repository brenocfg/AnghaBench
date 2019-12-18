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
struct rtentry {int rt_flags; struct rtentry* rt_gwroute; } ;
struct route_event {int /*<<< orphan*/  route_event_code; struct rtentry* rt; } ;
struct radix_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int RTF_GATEWAY ; 
 int RTPRF_OURS ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  route_event_enqueue_nwk_wq_entry (struct rtentry*,struct rtentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
route_event_walktree(struct radix_node *rn, void *arg)
{
	struct route_event *p_route_ev = (struct route_event *)arg;
	struct rtentry *rt = (struct rtentry *)rn;
	struct rtentry *gwrt = p_route_ev->rt;

	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);

	RT_LOCK(rt);

	/* Return if the entry is pending cleanup */
	if (rt->rt_flags & RTPRF_OURS) {
		RT_UNLOCK(rt);
		return (0);
	}

	/* Return if it is not an indirect route */
	if (!(rt->rt_flags & RTF_GATEWAY)) {
		RT_UNLOCK(rt);
		return (0);
	}

	if (rt->rt_gwroute != gwrt) {
		RT_UNLOCK(rt);
		return (0);
	}

	route_event_enqueue_nwk_wq_entry(rt, gwrt, p_route_ev->route_event_code,
	    NULL, TRUE);
	RT_UNLOCK(rt);

	return (0);
}