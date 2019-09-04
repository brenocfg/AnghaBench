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
struct radix_node_head {scalar_t__ (* rnh_walktree ) (struct radix_node_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  nstat_msg_add_all_srcs ;
typedef  int /*<<< orphan*/  nstat_control_state ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int AF_MAX ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nstat_route_walktree_add ; 
 int /*<<< orphan*/  nstat_route_watchers ; 
 scalar_t__ nstat_set_provider_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rnh_lock ; 
 struct radix_node_head** rt_tables ; 
 scalar_t__ stub1 (struct radix_node_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static errno_t
nstat_route_add_watcher(
	nstat_control_state	*state,
	nstat_msg_add_all_srcs *req)
{
	int i;
	errno_t result = 0;

	lck_mtx_lock(rnh_lock);

	result = nstat_set_provider_filter(state, req);
	if (result == 0)
	{
		OSIncrementAtomic(&nstat_route_watchers);

		for (i = 1; i < AF_MAX; i++)
		{
			struct radix_node_head *rnh;
			rnh = rt_tables[i];
			if (!rnh) continue;

			result = rnh->rnh_walktree(rnh, nstat_route_walktree_add, state);
			if (result != 0)
			{
				// This is probably resource exhaustion.
				// There currently isn't a good way to recover from this.
				// Least bad seems to be to give up on the add-all but leave
				// the watcher in place.
				break;
			}
		}
	}
	lck_mtx_unlock(rnh_lock);

	return result;
}