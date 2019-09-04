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
struct rtentry {int rt_flags; int /*<<< orphan*/  rt_gateway; struct ifnet* rt_ifp; } ;
struct radix_node {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_mask (struct rtentry*) ; 
 int rtrequest_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
if_rtdel(struct radix_node *rn, void *arg)
{
	struct rtentry	*rt = (struct rtentry *)rn;
	struct ifnet	*ifp = arg;
	int		err;

	if (rt == NULL)
		return (0);
	/*
	 * Checking against RTF_UP protects against walktree
	 * recursion problems with cloned routes.
	 */
	RT_LOCK(rt);
	if (rt->rt_ifp == ifp && (rt->rt_flags & RTF_UP)) {
		/*
		 * Safe to drop rt_lock and use rt_key, rt_gateway,
		 * since holding rnh_lock here prevents another thread
		 * from calling rt_setgate() on this route.
		 */
		RT_UNLOCK(rt);
		err = rtrequest_locked(RTM_DELETE, rt_key(rt), rt->rt_gateway,
		    rt_mask(rt), rt->rt_flags, NULL);
		if (err) {
			log(LOG_WARNING, "if_rtdel: error %d\n", err);
		}
	} else {
		RT_UNLOCK(rt);
	}
	return (0);
}