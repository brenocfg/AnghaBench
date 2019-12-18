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
typedef  scalar_t__ cputime64_t ;
struct TYPE_3__ {int /*<<< orphan*/  nice; int /*<<< orphan*/  steal; int /*<<< orphan*/  softirq; int /*<<< orphan*/  irq; int /*<<< orphan*/  system; scalar_t__ user; } ;
struct TYPE_4__ {TYPE_1__ cpustat; } ;

/* Variables and functions */
 scalar_t__ cputime64_add (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ cputime64_sub (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 scalar_t__ jiffies64_to_cputime64 (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies_to_usecs (scalar_t__) ; 
 TYPE_2__ kstat_cpu (unsigned int) ; 

__attribute__((used)) static inline cputime64_t get_cpu_idle_time_jiffy(unsigned int cpu,
							cputime64_t *wall)
{
	cputime64_t idle_time;
	cputime64_t cur_wall_time;
	cputime64_t busy_time;

	cur_wall_time = jiffies64_to_cputime64(get_jiffies_64());
	busy_time = cputime64_add(kstat_cpu(cpu).cpustat.user,
			kstat_cpu(cpu).cpustat.system);

	busy_time = cputime64_add(busy_time, kstat_cpu(cpu).cpustat.irq);
	busy_time = cputime64_add(busy_time, kstat_cpu(cpu).cpustat.softirq);
	busy_time = cputime64_add(busy_time, kstat_cpu(cpu).cpustat.steal);
	busy_time = cputime64_add(busy_time, kstat_cpu(cpu).cpustat.nice);

	idle_time = cputime64_sub(cur_wall_time, busy_time);
	if (wall)
		*wall = (cputime64_t)jiffies_to_usecs(cur_wall_time);

	return (cputime64_t)jiffies_to_usecs(idle_time);
}