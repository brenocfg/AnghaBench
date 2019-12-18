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
struct rtentry_dbg {int dummy; } ;
struct rtentry {int /*<<< orphan*/  rt_lock; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int RTD_DEBUG ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_NOTHELD (struct rtentry*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int rte_debug ; 
 int /*<<< orphan*/  rte_lock_debug (struct rtentry_dbg*) ; 

void
rt_lock(struct rtentry *rt, boolean_t spin)
{
	RT_LOCK_ASSERT_NOTHELD(rt);
	if (spin)
		lck_mtx_lock_spin(&rt->rt_lock);
	else
		lck_mtx_lock(&rt->rt_lock);
	if (rte_debug & RTD_DEBUG)
		rte_lock_debug((struct rtentry_dbg *)rt);
}