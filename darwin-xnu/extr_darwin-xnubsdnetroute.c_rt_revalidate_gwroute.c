#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct rtentry {int rt_flags; scalar_t__ rt_ifp; TYPE_2__* rt_gateway; TYPE_1__* rt_gwroute; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {scalar_t__ sa_family; } ;
struct TYPE_8__ {int rt_flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int RTF_CLONING ; 
 int RTF_GATEWAY ; 
 int RTF_PRCLONING ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 TYPE_2__* SA (struct sockaddr_storage*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ equal (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 TYPE_2__* rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_set_gwroute (struct rtentry*,TYPE_2__*,struct rtentry*) ; 
 int /*<<< orphan*/  sa_copy (TYPE_2__*,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 

void
rt_revalidate_gwroute(struct rtentry *rt, struct rtentry *gwrt)
{
	VERIFY(gwrt != NULL);

	RT_LOCK_SPIN(rt);
	if ((rt->rt_flags & (RTF_GATEWAY | RTF_UP)) == (RTF_GATEWAY | RTF_UP) &&
	    rt->rt_ifp == gwrt->rt_ifp && rt->rt_gateway->sa_family ==
	    rt_key(gwrt)->sa_family && (rt->rt_gwroute == NULL ||
	    !(rt->rt_gwroute->rt_flags & RTF_UP))) {
		boolean_t isequal;
		VERIFY(rt->rt_flags & (RTF_CLONING | RTF_PRCLONING));

		if (rt->rt_gateway->sa_family == AF_INET ||
		    rt->rt_gateway->sa_family == AF_INET6) {
			struct sockaddr_storage key_ss, gw_ss;
			/*
			 * We need to compare rt_key and rt_gateway; create
			 * local copies to get rid of any ifscope association.
			 */
			(void) sa_copy(rt_key(gwrt), &key_ss, NULL);
			(void) sa_copy(rt->rt_gateway, &gw_ss, NULL);

			isequal = equal(SA(&key_ss), SA(&gw_ss));
		} else {
			isequal = equal(rt_key(gwrt), rt->rt_gateway);
		}

		/* If they are the same, update gwrt */
		if (isequal) {
			RT_UNLOCK(rt);
			lck_mtx_lock(rnh_lock);
			RT_LOCK(rt);
			rt_set_gwroute(rt, rt_key(rt), gwrt);
			RT_UNLOCK(rt);
			lck_mtx_unlock(rnh_lock);
		} else {
			RT_UNLOCK(rt);
		}
	} else {
		RT_UNLOCK(rt);
	}
}