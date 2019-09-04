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
typedef  int pid_t ;

/* Variables and functions */
 int KPERF_SAMPLER_KSTACK ; 
 int KPERF_SAMPLER_USTACK ; 
 unsigned int NSEC_PER_MSEC ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kperf_action_count_set (int) ; 
 int /*<<< orphan*/  kperf_action_filter_set_by_pid (int,int) ; 
 int /*<<< orphan*/  kperf_action_samplers_set (int,int) ; 
 int /*<<< orphan*/  kperf_ns_to_ticks (unsigned int) ; 
 int /*<<< orphan*/  kperf_reset () ; 
 int /*<<< orphan*/  kperf_timer_action_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kperf_timer_count_set (int) ; 
 int /*<<< orphan*/  kperf_timer_period_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
configure_kperf_stacks_timer(pid_t pid, unsigned int period_ms)
{
    kperf_reset();

    (void)kperf_action_count_set(1);
    (void)kperf_timer_count_set(1);

    T_ASSERT_POSIX_SUCCESS(kperf_action_samplers_set(1,
        KPERF_SAMPLER_USTACK | KPERF_SAMPLER_KSTACK), NULL);

    if (pid != -1) {
        T_ASSERT_POSIX_SUCCESS(kperf_action_filter_set_by_pid(1, pid), NULL);
    }

    T_ASSERT_POSIX_SUCCESS(kperf_timer_action_set(0, 1), NULL);
    T_ASSERT_POSIX_SUCCESS(kperf_timer_period_set(0,
        kperf_ns_to_ticks(period_ms * NSEC_PER_MSEC)), NULL);
}