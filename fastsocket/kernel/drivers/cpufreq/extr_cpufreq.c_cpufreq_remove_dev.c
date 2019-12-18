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
struct sys_device {unsigned int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int __cpufreq_remove_dev (struct sys_device*) ; 
 scalar_t__ cpu_is_offline (unsigned int) ; 
 int /*<<< orphan*/  lock_policy_rwsem_write (unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_remove_dev(struct sys_device *sys_dev)
{
	unsigned int cpu = sys_dev->id;
	int retval;

	if (cpu_is_offline(cpu))
		return 0;

	if (unlikely(lock_policy_rwsem_write(cpu)))
		BUG();

	retval = __cpufreq_remove_dev(sys_dev);
	return retval;
}