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
struct cpuidle_governor {int /*<<< orphan*/  governor_list; int /*<<< orphan*/  rating; } ;

/* Variables and functions */
 struct cpuidle_governor* cpuidle_curr_governor ; 
 int /*<<< orphan*/  cpuidle_lock ; 
 struct cpuidle_governor* cpuidle_replace_governor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuidle_switch_governor (struct cpuidle_governor*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cpuidle_unregister_governor(struct cpuidle_governor *gov)
{
	if (!gov)
		return;

	mutex_lock(&cpuidle_lock);
	if (gov == cpuidle_curr_governor) {
		struct cpuidle_governor *new_gov;
		new_gov = cpuidle_replace_governor(gov->rating);
		cpuidle_switch_governor(new_gov);
	}
	list_del(&gov->governor_list);
	mutex_unlock(&cpuidle_lock);
}