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
struct task_struct {void* gtime; void* utimescaled; void* utime; } ;
struct cpu_usage_stat {void* guest; void* user; } ;
typedef  int /*<<< orphan*/  cputime_t ;
typedef  int /*<<< orphan*/  cputime64_t ;
struct TYPE_2__ {struct cpu_usage_stat cpustat; } ;

/* Variables and functions */
 int /*<<< orphan*/  account_group_user_time (struct task_struct*,int /*<<< orphan*/ ) ; 
 void* cputime64_add (void*,int /*<<< orphan*/ ) ; 
 void* cputime_add (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_to_cputime64 (int /*<<< orphan*/ ) ; 
 TYPE_1__ kstat_this_cpu ; 

__attribute__((used)) static void account_guest_time(struct task_struct *p, cputime_t cputime,
			       cputime_t cputime_scaled)
{
	cputime64_t tmp;
	struct cpu_usage_stat *cpustat = &kstat_this_cpu.cpustat;

	tmp = cputime_to_cputime64(cputime);

	/* Add guest time to process. */
	p->utime = cputime_add(p->utime, cputime);
	p->utimescaled = cputime_add(p->utimescaled, cputime_scaled);
	account_group_user_time(p, cputime);
	p->gtime = cputime_add(p->gtime, cputime);

	/* Add guest time to cpustat. */
	cpustat->user = cputime64_add(cpustat->user, tmp);
	cpustat->guest = cputime64_add(cpustat->guest, tmp);
}