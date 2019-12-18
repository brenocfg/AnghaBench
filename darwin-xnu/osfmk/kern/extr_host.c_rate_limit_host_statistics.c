#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  host_info64_t ;
typedef  int /*<<< orphan*/  host_flavor_t ;
struct TYPE_6__ {scalar_t__ last_access; int current_requests; scalar_t__ max_requests; } ;
struct TYPE_5__ {int t_flags; } ;

/* Variables and functions */
 int FALSE ; 
 int HOST_STATISTICS_MAX_REQUESTS ; 
 int HOST_STATISTICS_MIN_REQUESTS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int TF_PLATFORM ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_task () ; 
 TYPE_3__* g_host_stats_cache ; 
 int /*<<< orphan*/  get_cached_info (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_host_info_data_index (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_statistics_lck ; 
 scalar_t__ host_statistics_time_window ; 
 TYPE_1__* kernel_task ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int mach_absolute_time () ; 
 scalar_t__ mach_continuous_time () ; 

__attribute__((used)) static bool
rate_limit_host_statistics(bool is_stat64, host_flavor_t flavor, host_info64_t info, mach_msg_type_number_t* count, kern_return_t* ret, int *pindex)
{
	task_t task = current_task();

	assert(task != kernel_task);

	*ret = KERN_SUCCESS;

	/* Access control only for third party applications */
	if (task->t_flags & TF_PLATFORM) {
		return FALSE;
	}

	/* Rate limit to HOST_STATISTICS_MAX_REQUESTS queries for each HOST_STATISTICS_TIME_WINDOW window of time */
	bool rate_limited = FALSE;
	bool set_last_access = TRUE;

	/* there is a cache for every flavor */
	int index = get_host_info_data_index(is_stat64, flavor, count, ret);
	if (index == -1)
		goto out;

	*pindex = index;
	lck_mtx_lock(&host_statistics_lck);
	if (g_host_stats_cache[index].last_access > mach_continuous_time() - host_statistics_time_window) {
		set_last_access = FALSE;
		if (g_host_stats_cache[index].current_requests++ >= g_host_stats_cache[index].max_requests) {
			rate_limited = TRUE;
			get_cached_info(index, info, count);
		}
	}
	if (set_last_access) {
		g_host_stats_cache[index].current_requests = 1;
		/*
		 * select a random number of requests (included between HOST_STATISTICS_MIN_REQUESTS and HOST_STATISTICS_MAX_REQUESTS)
		 * to let query host_statistics.
		 * In this way it is not possible to infer looking at when the a cached copy changes if host_statistics was called on
		 * the provious window.
		 */
		g_host_stats_cache[index].max_requests = (mach_absolute_time() % (HOST_STATISTICS_MAX_REQUESTS - HOST_STATISTICS_MIN_REQUESTS + 1)) + HOST_STATISTICS_MIN_REQUESTS;
		g_host_stats_cache[index].last_access = mach_continuous_time();
	}
	lck_mtx_unlock(&host_statistics_lck);
out:
	return rate_limited;
}