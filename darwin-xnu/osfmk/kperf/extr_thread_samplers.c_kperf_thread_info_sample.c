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
typedef  int /*<<< orphan*/  thread_t ;
struct kperf_thread_info {int /*<<< orphan*/  kpthi_runmode; int /*<<< orphan*/  kpthi_dq_addr; scalar_t__ kpthi_tid; int /*<<< orphan*/  kpthi_pid; } ;
struct kperf_context {int /*<<< orphan*/  cur_pid; int /*<<< orphan*/  cur_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int,uintptr_t) ; 
 int /*<<< orphan*/  BUF_VERB (int) ; 
 int DBG_FUNC_END ; 
 int PERF_TI_SAMPLE ; 
 int /*<<< orphan*/  kperf_thread_info_runmode_legacy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_dispatchqaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_tid (int /*<<< orphan*/ ) ; 

void
kperf_thread_info_sample(struct kperf_thread_info *ti, struct kperf_context *context)
{
	thread_t cur_thread = context->cur_thread;

	BUF_INFO(PERF_TI_SAMPLE, (uintptr_t)thread_tid(cur_thread));

	ti->kpthi_pid = context->cur_pid;
	ti->kpthi_tid = thread_tid(cur_thread);
	ti->kpthi_dq_addr = thread_dispatchqaddr(cur_thread);
	ti->kpthi_runmode = kperf_thread_info_runmode_legacy(cur_thread);

	BUF_VERB(PERF_TI_SAMPLE | DBG_FUNC_END);
}