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
typedef  int /*<<< orphan*/  cputime64_t ;
struct TYPE_3__ {int /*<<< orphan*/  nice; int /*<<< orphan*/  iowait; int /*<<< orphan*/  idle; } ;
struct TYPE_4__ {TYPE_1__ cpustat; } ;

/* Variables and functions */
 int /*<<< orphan*/  cputime64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ kstat_cpu (unsigned int) ; 
 scalar_t__ rackmeter_ignore_nice ; 

__attribute__((used)) static inline cputime64_t get_cpu_idle_time(unsigned int cpu)
{
	cputime64_t retval;

	retval = cputime64_add(kstat_cpu(cpu).cpustat.idle,
			kstat_cpu(cpu).cpustat.iowait);

	if (rackmeter_ignore_nice)
		retval = cputime64_add(retval, kstat_cpu(cpu).cpustat.nice);

	return retval;
}