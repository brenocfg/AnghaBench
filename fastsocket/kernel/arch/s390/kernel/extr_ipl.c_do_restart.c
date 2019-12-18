#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* action; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fn ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  crash_kexec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_locks_off () ; 
 int /*<<< orphan*/  lgr_info_log () ; 
 TYPE_2__ on_restart_trigger ; 
 int /*<<< orphan*/  smp_restart_with_online_cpu () ; 
 int /*<<< orphan*/  smp_send_stop () ; 
 int /*<<< orphan*/  stop_run (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  tracing_off () ; 

void do_restart(void)
{
	tracing_off();
	debug_locks_off();
	lgr_info_log();
	smp_restart_with_online_cpu();
	smp_send_stop();
#ifdef CONFIG_CRASH_DUMP
	crash_kexec(NULL);
#endif
	on_restart_trigger.action->fn(&on_restart_trigger);
	stop_run(&on_restart_trigger);
}