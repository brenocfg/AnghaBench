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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct kperf_thread_scheduling {int kpthsc_sched_priority; int kpthsc_state; int kpthsc_effective_qos; int kpthsc_requested_qos; int kpthsc_requested_qos_override; int /*<<< orphan*/  kpthsc_runnable_time; scalar_t__ kpthsc_requested_qos_sync_ipc_override; scalar_t__ kpthsc_requested_qos_ipc_override; scalar_t__ kpthsc_requested_qos_promote; scalar_t__ kpthsc_effective_latency_qos; scalar_t__ kpthsc_base_priority; int /*<<< orphan*/  kpthsc_system_time; int /*<<< orphan*/  kpthsc_user_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  LOWER_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_TI_SCHEDDATA1_32 ; 
 int /*<<< orphan*/  PERF_TI_SCHEDDATA2_32_2 ; 
 int /*<<< orphan*/  PERF_TI_SCHEDDATA3_32 ; 
 int /*<<< orphan*/  PERF_TI_SCHEDDATA_2 ; 
 int /*<<< orphan*/  PERF_TI_SCHEDDATA_3 ; 
 int /*<<< orphan*/  UPPER_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
kperf_thread_scheduling_log(struct kperf_thread_scheduling *thsc)
{
	assert(thsc != NULL);
#if defined(__LP64__)
	BUF_DATA(PERF_TI_SCHEDDATA_2, thsc->kpthsc_user_time,
			thsc->kpthsc_system_time,
			(((uint64_t)thsc->kpthsc_base_priority) << 48)
			| ((uint64_t)thsc->kpthsc_sched_priority << 32)
			| ((uint64_t)(thsc->kpthsc_state & 0xff) << 24)
			| (thsc->kpthsc_effective_qos << 6)
			| (thsc->kpthsc_requested_qos << 3)
			| thsc->kpthsc_requested_qos_override,
			((uint64_t)thsc->kpthsc_effective_latency_qos << 61)
			| ((uint64_t)thsc->kpthsc_requested_qos_promote << 58)
			| ((uint64_t)thsc->kpthsc_requested_qos_ipc_override << 55)
			| ((uint64_t)thsc->kpthsc_requested_qos_sync_ipc_override << 52)
			);
	BUF_DATA(PERF_TI_SCHEDDATA_3, thsc->kpthsc_runnable_time);
#else
	BUF_DATA(PERF_TI_SCHEDDATA1_32, UPPER_32(thsc->kpthsc_user_time),
			LOWER_32(thsc->kpthsc_user_time),
			UPPER_32(thsc->kpthsc_system_time),
			LOWER_32(thsc->kpthsc_system_time)
			);
	BUF_DATA(PERF_TI_SCHEDDATA2_32_2, (((uint32_t)thsc->kpthsc_base_priority) << 16)
			| thsc->kpthsc_sched_priority,
			((thsc->kpthsc_state & 0xff) << 24)
			| (thsc->kpthsc_effective_qos << 6)
			| (thsc->kpthsc_requested_qos << 3)
			| thsc->kpthsc_requested_qos_override,
			((uint32_t)thsc->kpthsc_effective_latency_qos << 29)
			| ((uint32_t)thsc->kpthsc_requested_qos_promote << 26)
			| ((uint32_t)thsc->kpthsc_requested_qos_ipc_override << 23)
			| ((uint32_t)thsc->kpthsc_requested_qos_sync_ipc_override << 20)
			);
	BUF_DATA(PERF_TI_SCHEDDATA3_32, UPPER_32(thsc->kpthsc_runnable_time),
			LOWER_32(thsc->kpthsc_runnable_time));
#endif /* defined(__LP64__) */
}