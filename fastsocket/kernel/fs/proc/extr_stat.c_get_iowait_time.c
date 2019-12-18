#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  cputime64_t ;
struct TYPE_3__ {int /*<<< orphan*/  iowait; } ;
struct TYPE_4__ {TYPE_1__ cpustat; } ;

/* Variables and functions */
 unsigned long long get_cpu_iowait_time_us (int,int /*<<< orphan*/ *) ; 
 TYPE_2__ kstat_cpu (int) ; 
 int /*<<< orphan*/  usecs_to_cputime64 (unsigned long long) ; 

__attribute__((used)) static cputime64_t get_iowait_time(int cpu)
{
	u64 iowait_time = get_cpu_iowait_time_us(cpu, NULL);
	cputime64_t iowait;

	if (iowait_time == -1ULL)
		/* !NO_HZ so we can rely on cpustat.iowait */
		iowait = kstat_cpu(cpu).cpustat.iowait;
	else
		iowait = usecs_to_cputime64(iowait_time);

	return iowait;
}