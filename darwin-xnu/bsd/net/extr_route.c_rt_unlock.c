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

/* Variables and functions */
 int RTD_DEBUG ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int rte_debug ; 
 int /*<<< orphan*/  rte_unlock_debug (struct rtentry_dbg*) ; 

void
rt_unlock(struct rtentry *rt)
{
	if (rte_debug & RTD_DEBUG)
		rte_unlock_debug((struct rtentry_dbg *)rt);
	lck_mtx_unlock(&rt->rt_lock);

}