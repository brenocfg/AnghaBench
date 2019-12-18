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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  do_perf_sw_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ) ; 
 int perf_swevent_get_recursion_context () ; 
 int /*<<< orphan*/  perf_swevent_put_recursion_context (int) ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 

void __perf_sw_event(u32 event_id, u64 nr, struct pt_regs *regs, u64 addr)
{
	struct perf_sample_data data;
	int rctx;

	preempt_disable_notrace();
	rctx = perf_swevent_get_recursion_context();
	if (rctx < 0)
		return;

	perf_sample_data_init(&data, addr);

	do_perf_sw_event(PERF_TYPE_SOFTWARE, event_id, nr, &data, regs);

	perf_swevent_put_recursion_context(rctx);
	preempt_enable_notrace();
}