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
struct cpufreq_policy {scalar_t__ policy; TYPE_1__* governor; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_NAME_LEN ; 
 scalar_t__ CPUFREQ_POLICY_PERFORMANCE ; 
 scalar_t__ CPUFREQ_POLICY_POWERSAVE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t show_scaling_governor(struct cpufreq_policy *policy, char *buf)
{
	if (policy->policy == CPUFREQ_POLICY_POWERSAVE)
		return sprintf(buf, "powersave\n");
	else if (policy->policy == CPUFREQ_POLICY_PERFORMANCE)
		return sprintf(buf, "performance\n");
	else if (policy->governor)
		return scnprintf(buf, CPUFREQ_NAME_LEN, "%s\n",
				policy->governor->name);
	return -EINVAL;
}