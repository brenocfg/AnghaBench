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
struct wf_control {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct wf_control* cpufreq_clamp ; 
 struct wf_control* fan_cpu_main ; 
 struct wf_control* fan_hd ; 
 struct wf_control* fan_system ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wf_get_control (struct wf_control*) ; 
 int wf_smu_all_controls_ok ; 
 int wf_smu_mach_model ; 

__attribute__((used)) static void wf_smu_new_control(struct wf_control *ct)
{
	if (wf_smu_all_controls_ok)
		return;

	if (fan_cpu_main == NULL && !strcmp(ct->name, "cpu-fan")) {
		if (wf_get_control(ct) == 0)
			fan_cpu_main = ct;
	}

	if (fan_system == NULL && !strcmp(ct->name, "system-fan")) {
		if (wf_get_control(ct) == 0)
			fan_system = ct;
	}

	if (cpufreq_clamp == NULL && !strcmp(ct->name, "cpufreq-clamp")) {
		if (wf_get_control(ct) == 0)
			cpufreq_clamp = ct;
	}

	/* Darwin property list says the HD fan is only for model ID
	 * 0, 1, 2 and 3
	 */

	if (wf_smu_mach_model > 3) {
		if (fan_system && fan_cpu_main && cpufreq_clamp)
			wf_smu_all_controls_ok = 1;
		return;
	}

	if (fan_hd == NULL && !strcmp(ct->name, "drive-bay-fan")) {
		if (wf_get_control(ct) == 0)
			fan_hd = ct;
	}

	if (fan_system && fan_hd && fan_cpu_main && cpufreq_clamp)
		wf_smu_all_controls_ok = 1;
}