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
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  nmi_cpu_down ; 
 int /*<<< orphan*/  nmi_cpu_up ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int oprofile_cpu_notifier(struct notifier_block *b, unsigned long action,
				 void *data)
{
	int cpu = (unsigned long)data;
	switch (action) {
	case CPU_DOWN_FAILED:
	case CPU_ONLINE:
		smp_call_function_single(cpu, nmi_cpu_up, NULL, 0);
		break;
	case CPU_DOWN_PREPARE:
		smp_call_function_single(cpu, nmi_cpu_down, NULL, 1);
		break;
	}
	return NOTIFY_DONE;
}