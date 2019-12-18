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
struct cpufreq_governor {int /*<<< orphan*/  governor_list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/ * __find_governor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_governor_list ; 
 int /*<<< orphan*/  cpufreq_governor_mutex ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cpufreq_register_governor(struct cpufreq_governor *governor)
{
	int err;

	if (!governor)
		return -EINVAL;

	mutex_lock(&cpufreq_governor_mutex);

	err = -EBUSY;
	if (__find_governor(governor->name) == NULL) {
		err = 0;
		list_add(&governor->governor_list, &cpufreq_governor_list);
	}

	mutex_unlock(&cpufreq_governor_mutex);
	return err;
}