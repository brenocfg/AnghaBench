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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PROFILE_MUNMAP ; 
 int /*<<< orphan*/  PROFILE_TASK_EXIT ; 
 int /*<<< orphan*/  buffer_mutex ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marked_cpus ; 
 int /*<<< orphan*/  module_load_nb ; 
 int /*<<< orphan*/  munmap_nb ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int profile_event_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_event_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int register_module_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_cpu_work () ; 
 int /*<<< orphan*/  task_exit_nb ; 
 int /*<<< orphan*/  task_free_nb ; 
 int task_handoff_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_handoff_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sync_start(void)
{
	int err;

	if (!zalloc_cpumask_var(&marked_cpus, GFP_KERNEL))
		return -ENOMEM;

	mutex_lock(&buffer_mutex);

	err = task_handoff_register(&task_free_nb);
	if (err)
		goto out1;
	err = profile_event_register(PROFILE_TASK_EXIT, &task_exit_nb);
	if (err)
		goto out2;
	err = profile_event_register(PROFILE_MUNMAP, &munmap_nb);
	if (err)
		goto out3;
	err = register_module_notifier(&module_load_nb);
	if (err)
		goto out4;

	start_cpu_work();

out:
	mutex_unlock(&buffer_mutex);
	return err;
out4:
	profile_event_unregister(PROFILE_MUNMAP, &munmap_nb);
out3:
	profile_event_unregister(PROFILE_TASK_EXIT, &task_exit_nb);
out2:
	task_handoff_unregister(&task_free_nb);
out1:
	free_cpumask_var(marked_cpus);
	goto out;
}