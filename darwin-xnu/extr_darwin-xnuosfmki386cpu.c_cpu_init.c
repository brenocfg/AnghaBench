#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  deadline; int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_subtype; int /*<<< orphan*/  cpu_type; TYPE_1__ rtclock_timer; } ;
typedef  TYPE_2__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  EndOfAllTime ; 
 int /*<<< orphan*/  cpuid_cpusubtype () ; 
 int /*<<< orphan*/  cpuid_cputype () ; 
 TYPE_2__* current_cpu_datap () ; 
 int /*<<< orphan*/  i386_activate_cpu () ; 
 int /*<<< orphan*/  timer_call_queue_init (int /*<<< orphan*/ *) ; 

void
cpu_init(void)
{
	cpu_data_t	*cdp = current_cpu_datap();

	timer_call_queue_init(&cdp->rtclock_timer.queue);
	cdp->rtclock_timer.deadline = EndOfAllTime;

	cdp->cpu_type = cpuid_cputype();
	cdp->cpu_subtype = cpuid_cpusubtype();

	i386_activate_cpu();
}