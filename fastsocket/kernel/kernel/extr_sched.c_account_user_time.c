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
struct task_struct {void* utimescaled; void* utime; } ;
struct cpu_usage_stat {void* user; void* nice; } ;
typedef  int /*<<< orphan*/  cputime_t ;
typedef  int /*<<< orphan*/  cputime64_t ;
struct TYPE_2__ {struct cpu_usage_stat cpustat; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUACCT_STAT_USER ; 
 scalar_t__ TASK_NICE (struct task_struct*) ; 
 int /*<<< orphan*/  account_group_user_time (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acct_update_integrals (struct task_struct*) ; 
 int /*<<< orphan*/  cpuacct_update_stats (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cputime64_add (void*,int /*<<< orphan*/ ) ; 
 void* cputime_add (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_to_cputime64 (int /*<<< orphan*/ ) ; 
 TYPE_1__ kstat_this_cpu ; 

void account_user_time(struct task_struct *p, cputime_t cputime,
		       cputime_t cputime_scaled)
{
	struct cpu_usage_stat *cpustat = &kstat_this_cpu.cpustat;
	cputime64_t tmp;

	/* Add user time to process. */
	p->utime = cputime_add(p->utime, cputime);
	p->utimescaled = cputime_add(p->utimescaled, cputime_scaled);
	account_group_user_time(p, cputime);

	/* Add user time to cpustat. */
	tmp = cputime_to_cputime64(cputime);
	if (TASK_NICE(p) > 0)
		cpustat->nice = cputime64_add(cpustat->nice, tmp);
	else
		cpustat->user = cputime64_add(cpustat->user, tmp);

	cpuacct_update_stats(p, CPUACCT_STAT_USER, cputime);
	/* Account for user time used */
	acct_update_integrals(p);
}