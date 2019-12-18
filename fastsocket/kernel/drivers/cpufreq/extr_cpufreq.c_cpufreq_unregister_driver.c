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
struct cpufreq_driver {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_sysdev_class ; 
 int /*<<< orphan*/  cpufreq_cpu_notifier ; 
 int /*<<< orphan*/  cpufreq_debug_disable_ratelimit () ; 
 int /*<<< orphan*/  cpufreq_debug_enable_ratelimit () ; 
 struct cpufreq_driver* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_driver_lock ; 
 int /*<<< orphan*/  cpufreq_sysdev_driver ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysdev_driver_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_hotcpu_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpufreq_unregister_driver(struct cpufreq_driver *driver)
{
	unsigned long flags;

	cpufreq_debug_disable_ratelimit();

	if (!cpufreq_driver || (driver != cpufreq_driver)) {
		cpufreq_debug_enable_ratelimit();
		return -EINVAL;
	}

	dprintk("unregistering driver %s\n", driver->name);

	sysdev_driver_unregister(&cpu_sysdev_class, &cpufreq_sysdev_driver);
	unregister_hotcpu_notifier(&cpufreq_cpu_notifier);

	write_lock_irqsave(&cpufreq_driver_lock, flags);
	cpufreq_driver = NULL;
	write_unlock_irqrestore(&cpufreq_driver_lock, flags);

	return 0;
}