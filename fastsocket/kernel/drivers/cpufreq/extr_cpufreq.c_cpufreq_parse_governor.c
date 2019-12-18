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
struct cpufreq_governor {int dummy; } ;
struct TYPE_2__ {scalar_t__ target; scalar_t__ setpolicy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_NAME_LEN ; 
 unsigned int CPUFREQ_POLICY_PERFORMANCE ; 
 unsigned int CPUFREQ_POLICY_POWERSAVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cpufreq_governor* __find_governor (char*) ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  cpufreq_governor_mutex ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_module (char*,char*) ; 
 int /*<<< orphan*/  strnicmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_parse_governor(char *str_governor, unsigned int *policy,
				struct cpufreq_governor **governor)
{
	int err = -EINVAL;

	if (!cpufreq_driver)
		goto out;

	if (cpufreq_driver->setpolicy) {
		if (!strnicmp(str_governor, "performance", CPUFREQ_NAME_LEN)) {
			*policy = CPUFREQ_POLICY_PERFORMANCE;
			err = 0;
		} else if (!strnicmp(str_governor, "powersave",
						CPUFREQ_NAME_LEN)) {
			*policy = CPUFREQ_POLICY_POWERSAVE;
			err = 0;
		}
	} else if (cpufreq_driver->target) {
		struct cpufreq_governor *t;

		mutex_lock(&cpufreq_governor_mutex);

		t = __find_governor(str_governor);

		if (t == NULL) {
			char *name = kasprintf(GFP_KERNEL, "cpufreq_%s",
								str_governor);

			if (name) {
				int ret;

				mutex_unlock(&cpufreq_governor_mutex);
				ret = request_module("%s", name);
				mutex_lock(&cpufreq_governor_mutex);

				if (ret == 0)
					t = __find_governor(str_governor);
			}

			kfree(name);
		}

		if (t != NULL) {
			*governor = t;
			err = 0;
		}

		mutex_unlock(&cpufreq_governor_mutex);
	}
out:
	return err;
}