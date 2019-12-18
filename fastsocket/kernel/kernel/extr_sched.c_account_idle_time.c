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
struct rq {int /*<<< orphan*/  nr_iowait; } ;
struct cpu_usage_stat {void* idle; void* iowait; } ;
typedef  int /*<<< orphan*/  cputime_t ;
typedef  int /*<<< orphan*/  cputime64_t ;
struct TYPE_2__ {struct cpu_usage_stat cpustat; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 void* cputime64_add (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_to_cputime64 (int /*<<< orphan*/ ) ; 
 TYPE_1__ kstat_this_cpu ; 
 struct rq* this_rq () ; 

void account_idle_time(cputime_t cputime)
{
	struct cpu_usage_stat *cpustat = &kstat_this_cpu.cpustat;
	cputime64_t cputime64 = cputime_to_cputime64(cputime);
	struct rq *rq = this_rq();

	if (atomic_read(&rq->nr_iowait) > 0)
		cpustat->iowait = cputime64_add(cpustat->iowait, cputime64);
	else
		cpustat->idle = cputime64_add(cpustat->idle, cputime64);
}