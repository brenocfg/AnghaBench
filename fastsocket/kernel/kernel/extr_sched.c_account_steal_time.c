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
struct cpu_usage_stat {int /*<<< orphan*/  steal; } ;
typedef  int /*<<< orphan*/  cputime_t ;
typedef  int /*<<< orphan*/  cputime64_t ;
struct TYPE_2__ {struct cpu_usage_stat cpustat; } ;

/* Variables and functions */
 int /*<<< orphan*/  cputime64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_to_cputime64 (int /*<<< orphan*/ ) ; 
 TYPE_1__ kstat_this_cpu ; 

void account_steal_time(cputime_t cputime)
{
	struct cpu_usage_stat *cpustat = &kstat_this_cpu.cpustat;
	cputime64_t cputime64 = cputime_to_cputime64(cputime);

	cpustat->steal = cputime64_add(cpustat->steal, cputime64);
}