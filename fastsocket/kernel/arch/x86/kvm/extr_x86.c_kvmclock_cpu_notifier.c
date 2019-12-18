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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  CPU_DOWN_FAILED 130 
#define  CPU_DOWN_PREPARE 129 
#define  CPU_ONLINE 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tsc_bad ; 
 int /*<<< orphan*/  tsc_khz_changed ; 

__attribute__((used)) static int kvmclock_cpu_notifier(struct notifier_block *nfb,
					unsigned long action, void *hcpu)
{
	unsigned int cpu = (unsigned long)hcpu;

	switch (action) {
		case CPU_ONLINE:
		case CPU_DOWN_FAILED:
			smp_call_function_single(cpu, tsc_khz_changed, NULL, 1);
			break;
		case CPU_DOWN_PREPARE:
			smp_call_function_single(cpu, tsc_bad, NULL, 1);
			break;
	}
	return NOTIFY_OK;
}