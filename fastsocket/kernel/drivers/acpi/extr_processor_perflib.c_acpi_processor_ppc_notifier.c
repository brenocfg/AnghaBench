#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct cpufreq_policy {int /*<<< orphan*/  cpu; } ;
struct acpi_processor {TYPE_2__* performance; scalar_t__ performance_platform_limit; } ;
struct TYPE_4__ {unsigned int state_count; TYPE_1__* states; } ;
struct TYPE_3__ {int core_frequency; } ;

/* Variables and functions */
 unsigned long CPUFREQ_INCOMPATIBLE ; 
 unsigned long CPUFREQ_START ; 
 int /*<<< orphan*/  cpufreq_verify_within_limits (struct cpufreq_policy*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ignore_ppc ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct acpi_processor* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  performance_mutex ; 
 int /*<<< orphan*/  processors ; 

__attribute__((used)) static int acpi_processor_ppc_notifier(struct notifier_block *nb,
				       unsigned long event, void *data)
{
	struct cpufreq_policy *policy = data;
	struct acpi_processor *pr;
	unsigned int ppc = 0;

	if (event == CPUFREQ_START && ignore_ppc <= 0) {
		ignore_ppc = 0;
		return 0;
	}

	if (ignore_ppc)
		return 0;

	if (event != CPUFREQ_INCOMPATIBLE)
		return 0;

	mutex_lock(&performance_mutex);

	pr = per_cpu(processors, policy->cpu);
	if (!pr || !pr->performance)
		goto out;

	ppc = (unsigned int)pr->performance_platform_limit;

	if (ppc >= pr->performance->state_count)
		goto out;

	cpufreq_verify_within_limits(policy, 0,
				     pr->performance->states[ppc].
				     core_frequency * 1000);

      out:
	mutex_unlock(&performance_mutex);

	return 0;
}