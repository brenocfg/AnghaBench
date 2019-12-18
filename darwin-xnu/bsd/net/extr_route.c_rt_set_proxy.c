#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtentry {int rt_flags; } ;
struct radix_node_head {int /*<<< orphan*/  (* rnh_walktree_from ) (struct radix_node_head*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,struct rtentry*) ;} ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {size_t sa_family; } ;

/* Variables and functions */
 int RTF_CLONING ; 
 int RTF_PRCLONING ; 
 int RTF_PROXY ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rnh_lock ; 
 int /*<<< orphan*/  rt_fixdelete ; 
 TYPE_1__* rt_key (struct rtentry*) ; 
 scalar_t__ rt_mask (struct rtentry*) ; 
 struct radix_node_head** rt_tables ; 
 int /*<<< orphan*/  stub1 (struct radix_node_head*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,struct rtentry*) ; 

void
rt_set_proxy(struct rtentry *rt, boolean_t set)
{
	lck_mtx_lock(rnh_lock);
	RT_LOCK(rt);
	/*
	 * Search for any cloned routes which might have
	 * been formed from this node, and delete them.
	 */
	if (rt->rt_flags & (RTF_CLONING | RTF_PRCLONING)) {
		struct radix_node_head *rnh = rt_tables[rt_key(rt)->sa_family];

		if (set)
			rt->rt_flags |= RTF_PROXY;
		else
			rt->rt_flags &= ~RTF_PROXY;

		RT_UNLOCK(rt);
		if (rnh != NULL && rt_mask(rt)) {
			rnh->rnh_walktree_from(rnh, rt_key(rt), rt_mask(rt),
			    rt_fixdelete, rt);
		}
	} else {
		RT_UNLOCK(rt);
	}
	lck_mtx_unlock(rnh_lock);
}