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
struct flow_flush_info {int /*<<< orphan*/  completion; int /*<<< orphan*/  cpuleft; int /*<<< orphan*/ * cache; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_cache_flush_per_cpu ; 
 int /*<<< orphan*/  flow_cache_flush_tasklet (unsigned long) ; 
 int /*<<< orphan*/  flow_cache_global ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,struct flow_flush_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void flow_cache_flush(void)
{
	struct flow_flush_info info;
	static DEFINE_MUTEX(flow_flush_sem);

	/* Don't want cpus going down or up during this. */
	get_online_cpus();
	mutex_lock(&flow_flush_sem);
	info.cache = &flow_cache_global;
	atomic_set(&info.cpuleft, num_online_cpus());
	init_completion(&info.completion);

	local_bh_disable();
	smp_call_function(flow_cache_flush_per_cpu, &info, 0);
	flow_cache_flush_tasklet((unsigned long)&info);
	local_bh_enable();

	wait_for_completion(&info.completion);
	mutex_unlock(&flow_flush_sem);
	put_online_cpus();
}