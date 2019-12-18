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
struct TYPE_2__ {int /*<<< orphan*/  tmfreq; int /*<<< orphan*/  tmirq; } ;
struct ipipe_sysinfo {int /*<<< orphan*/  cpufreq; TYPE_1__ archdep; int /*<<< orphan*/  ncpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPIPE_TIMER_IRQ ; 
 int /*<<< orphan*/  ipipe_cpu_freq () ; 
 int /*<<< orphan*/  num_online_cpus () ; 

int ipipe_get_sysinfo(struct ipipe_sysinfo *info)
{
	info->ncpus = num_online_cpus();
	info->cpufreq = ipipe_cpu_freq();
	info->archdep.tmirq = IPIPE_TIMER_IRQ;
	info->archdep.tmfreq = info->cpufreq;

	return 0;
}