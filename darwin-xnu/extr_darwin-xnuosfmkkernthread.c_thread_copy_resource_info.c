#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_4__ {int /*<<< orphan*/ * thread_io_stats; int /*<<< orphan*/  t_threadledger; int /*<<< orphan*/  syscalls_mach; int /*<<< orphan*/  syscalls_unix; int /*<<< orphan*/  vtimer_qos_save; int /*<<< orphan*/  vtimer_rlim_save; int /*<<< orphan*/  vtimer_prof_save; int /*<<< orphan*/  vtimer_user_save; int /*<<< orphan*/  runnable_timer; int /*<<< orphan*/  system_timer_save; int /*<<< orphan*/  system_timer; int /*<<< orphan*/  user_timer_save; int /*<<< orphan*/  user_timer; int /*<<< orphan*/  precise_user_kernel_time; int /*<<< orphan*/  ps_switch; int /*<<< orphan*/  p_switch; int /*<<< orphan*/  c_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ledger_rollup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
thread_copy_resource_info(
	thread_t dst_thread,
	thread_t src_thread)
{
	dst_thread->c_switch = src_thread->c_switch;
	dst_thread->p_switch = src_thread->p_switch;
	dst_thread->ps_switch = src_thread->ps_switch;
	dst_thread->precise_user_kernel_time = src_thread->precise_user_kernel_time;
	dst_thread->user_timer = src_thread->user_timer;
	dst_thread->user_timer_save = src_thread->user_timer_save;
	dst_thread->system_timer = src_thread->system_timer;
	dst_thread->system_timer_save = src_thread->system_timer_save;
	dst_thread->runnable_timer = src_thread->runnable_timer;
	dst_thread->vtimer_user_save = src_thread->vtimer_user_save;
	dst_thread->vtimer_prof_save = src_thread->vtimer_prof_save;
	dst_thread->vtimer_rlim_save = src_thread->vtimer_rlim_save;
	dst_thread->vtimer_qos_save = src_thread->vtimer_qos_save;
	dst_thread->syscalls_unix = src_thread->syscalls_unix;
	dst_thread->syscalls_mach = src_thread->syscalls_mach;
	ledger_rollup(dst_thread->t_threadledger, src_thread->t_threadledger);
	*dst_thread->thread_io_stats = *src_thread->thread_io_stats;
}