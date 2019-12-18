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

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_setall (int /*<<< orphan*/ ) ; 
 scalar_t__ current ; 
 scalar_t__* fakewriter_tasks ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int nfakewriters ; 
 int nrealreaders ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int rcu_idle_cpu ; 
 scalar_t__* reader_tasks ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shuffle_tmp_mask ; 
 scalar_t__ stats_task ; 
 scalar_t__ writer_task ; 

__attribute__((used)) static void rcu_torture_shuffle_tasks(void)
{
	int i;

	cpumask_setall(shuffle_tmp_mask);
	get_online_cpus();

	/* No point in shuffling if there is only one online CPU (ex: UP) */
	if (num_online_cpus() == 1) {
		put_online_cpus();
		return;
	}

	if (rcu_idle_cpu != -1)
		cpumask_clear_cpu(rcu_idle_cpu, shuffle_tmp_mask);

	set_cpus_allowed_ptr(current, shuffle_tmp_mask);

	if (reader_tasks) {
		for (i = 0; i < nrealreaders; i++)
			if (reader_tasks[i])
				set_cpus_allowed_ptr(reader_tasks[i],
						     shuffle_tmp_mask);
	}

	if (fakewriter_tasks) {
		for (i = 0; i < nfakewriters; i++)
			if (fakewriter_tasks[i])
				set_cpus_allowed_ptr(fakewriter_tasks[i],
						     shuffle_tmp_mask);
	}

	if (writer_task)
		set_cpus_allowed_ptr(writer_task, shuffle_tmp_mask);

	if (stats_task)
		set_cpus_allowed_ptr(stats_task, shuffle_tmp_mask);

	if (rcu_idle_cpu == -1)
		rcu_idle_cpu = num_online_cpus() - 1;
	else
		rcu_idle_cpu--;

	put_online_cpus();
}