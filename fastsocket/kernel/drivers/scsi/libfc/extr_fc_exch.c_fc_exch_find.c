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
typedef  scalar_t__ u16 ;
struct fc_exch_pool {int /*<<< orphan*/  lock; } ;
struct fc_exch_mgr {scalar_t__ min_xid; scalar_t__ max_xid; int /*<<< orphan*/  pool; } ;
struct fc_exch {scalar_t__ xid; } ;

/* Variables and functions */
 scalar_t__ fc_cpu_mask ; 
 scalar_t__ fc_cpu_order ; 
 int /*<<< orphan*/  fc_exch_hold (struct fc_exch*) ; 
 struct fc_exch* fc_exch_ptr_get (struct fc_exch_pool*,scalar_t__) ; 
 struct fc_exch_pool* per_cpu_ptr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fc_exch *fc_exch_find(struct fc_exch_mgr *mp, u16 xid)
{
	struct fc_exch_pool *pool;
	struct fc_exch *ep = NULL;

	if ((xid >= mp->min_xid) && (xid <= mp->max_xid)) {
		pool = per_cpu_ptr(mp->pool, xid & fc_cpu_mask);
		spin_lock_bh(&pool->lock);
		ep = fc_exch_ptr_get(pool, (xid - mp->min_xid) >> fc_cpu_order);
		if (ep && ep->xid == xid)
			fc_exch_hold(ep);
		spin_unlock_bh(&pool->lock);
	}
	return ep;
}