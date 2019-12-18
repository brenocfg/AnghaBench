#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_cpu_data ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_driver_lock ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 unsigned int nr_cpu_ids ; 
 struct cpufreq_policy* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct cpufreq_policy *cpufreq_cpu_get(unsigned int cpu)
{
	struct cpufreq_policy *data;
	unsigned long flags;

	if (cpu >= nr_cpu_ids)
		goto err_out;

	/* get the cpufreq driver */
	read_lock_irqsave(&cpufreq_driver_lock, flags);

	if (!cpufreq_driver)
		goto err_out_unlock;

	if (!try_module_get(cpufreq_driver->owner))
		goto err_out_unlock;


	/* get the CPU */
	data = per_cpu(cpufreq_cpu_data, cpu);

	if (!data)
		goto err_out_put_module;

	if (!kobject_get(&data->kobj))
		goto err_out_put_module;

	read_unlock_irqrestore(&cpufreq_driver_lock, flags);
	return data;

err_out_put_module:
	module_put(cpufreq_driver->owner);
err_out_unlock:
	read_unlock_irqrestore(&cpufreq_driver_lock, flags);
err_out:
	return NULL;
}