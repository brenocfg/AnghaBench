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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtentry {int /*<<< orphan*/ * rt_ifp; } ;
struct route {struct rtentry* ro_rt; int /*<<< orphan*/  ro_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROUTE_RELEASE_LOCKED (struct route*) ; 
 int /*<<< orphan*/  ROUTE_UNUSABLE (struct route*) ; 
 int /*<<< orphan*/  RT_GENID_SYNC (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_NOTHELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 struct rtentry* rtalloc1_common_locked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
rtalloc_ign_common_locked(struct route *ro, uint32_t ignore,
    unsigned int ifscope)
{
	struct rtentry *rt;

	if ((rt = ro->ro_rt) != NULL) {
		RT_LOCK_SPIN(rt);
		if (rt->rt_ifp != NULL && !ROUTE_UNUSABLE(ro)) {
			RT_UNLOCK(rt);
			return;
		}
		RT_UNLOCK(rt);
		ROUTE_RELEASE_LOCKED(ro);	/* rnh_lock already held */
	}
	ro->ro_rt = rtalloc1_common_locked(&ro->ro_dst, 1, ignore, ifscope);
	if (ro->ro_rt != NULL) {
		RT_GENID_SYNC(ro->ro_rt);
		RT_LOCK_ASSERT_NOTHELD(ro->ro_rt);
	}
}