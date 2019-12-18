#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct work_struct {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 unsigned int NR_CPUS ; 
 int /*<<< orphan*/  __round_jiffies_relative (int,unsigned int) ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int /*<<< orphan*/  do_event_scan () ; 
 int /*<<< orphan*/  enable_surveillance (int) ; 
 int event_scan_delay ; 
 int /*<<< orphan*/  event_scan_work ; 
 unsigned int first_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ first_pass ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 unsigned int next_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int rtas_event_scan_rate ; 
 int /*<<< orphan*/  schedule_delayed_work_on (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int surveillance_timeout ; 

__attribute__((used)) static void rtas_event_scan(struct work_struct *w)
{
	unsigned int cpu;

	do_event_scan();

	get_online_cpus();

	cpu = next_cpu(smp_processor_id(), cpu_online_map);
	if (cpu == NR_CPUS) {
		cpu = first_cpu(cpu_online_map);

		if (first_pass) {
			first_pass = 0;
			event_scan_delay = 30*HZ/rtas_event_scan_rate;

			if (surveillance_timeout != -1) {
				pr_debug("rtasd: enabling surveillance\n");
				enable_surveillance(surveillance_timeout);
				pr_debug("rtasd: surveillance enabled\n");
			}
		}
	}

	schedule_delayed_work_on(cpu, &event_scan_work,
		__round_jiffies_relative(event_scan_delay, cpu));

	put_online_cpus();
}