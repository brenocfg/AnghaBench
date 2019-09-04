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
struct rtentry {struct ifaddr* rt_ifa; } ;
struct ifaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_ADDREF (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_REMREF (struct ifaddr*) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  RT_CONVERT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_HELD (struct rtentry*) ; 
 int /*<<< orphan*/  rnh_lock ; 

void
rtsetifa(struct rtentry *rt, struct ifaddr *ifa)
{
	LCK_MTX_ASSERT(rnh_lock, LCK_MTX_ASSERT_OWNED);

	RT_LOCK_ASSERT_HELD(rt);

	if (rt->rt_ifa == ifa)
		return;

	/* Become a regular mutex, just in case */
	RT_CONVERT_LOCK(rt);

	/* Release the old ifa */
	if (rt->rt_ifa)
		IFA_REMREF(rt->rt_ifa);

	/* Set rt_ifa */
	rt->rt_ifa = ifa;

	/* Take a reference to the ifa */
	if (rt->rt_ifa)
		IFA_ADDREF(rt->rt_ifa);
}