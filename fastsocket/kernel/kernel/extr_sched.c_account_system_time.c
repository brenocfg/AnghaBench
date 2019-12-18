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
struct task_struct {int flags; void* stimescaled; void* stime; } ;
struct cpu_usage_stat {void* system; void* softirq; void* irq; } ;
typedef  int /*<<< orphan*/  cputime_t ;
typedef  int /*<<< orphan*/  cputime64_t ;
struct TYPE_2__ {struct cpu_usage_stat cpustat; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUACCT_STAT_SYSTEM ; 
 int PF_VCPU ; 
 int /*<<< orphan*/  account_group_system_time (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_guest_time (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acct_update_integrals (struct task_struct*) ; 
 int /*<<< orphan*/  cpuacct_update_stats (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cputime64_add (void*,int /*<<< orphan*/ ) ; 
 void* cputime_add (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_to_cputime64 (int /*<<< orphan*/ ) ; 
 int hardirq_count () ; 
 scalar_t__ in_serving_softirq () ; 
 int irq_count () ; 
 TYPE_1__ kstat_this_cpu ; 

void account_system_time(struct task_struct *p, int hardirq_offset,
			 cputime_t cputime, cputime_t cputime_scaled)
{
	struct cpu_usage_stat *cpustat = &kstat_this_cpu.cpustat;
	cputime64_t tmp;

	if ((p->flags & PF_VCPU) && (irq_count() - hardirq_offset == 0)) {
		account_guest_time(p, cputime, cputime_scaled);
		return;
	}

	/* Add system time to process. */
	p->stime = cputime_add(p->stime, cputime);
	p->stimescaled = cputime_add(p->stimescaled, cputime_scaled);
	account_group_system_time(p, cputime);

	/* Add system time to cpustat. */
	tmp = cputime_to_cputime64(cputime);
	if (hardirq_count() - hardirq_offset)
		cpustat->irq = cputime64_add(cpustat->irq, tmp);
	else if (in_serving_softirq())
		cpustat->softirq = cputime64_add(cpustat->softirq, tmp);
	else
		cpustat->system = cputime64_add(cpustat->system, tmp);

	cpuacct_update_stats(p, CPUACCT_STAT_SYSTEM, cputime);

	/* Account for system time used */
	acct_update_integrals(p);
}