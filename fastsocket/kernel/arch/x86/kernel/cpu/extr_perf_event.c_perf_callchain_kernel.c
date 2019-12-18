#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int /*<<< orphan*/  ip; } ;
struct perf_callchain_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* is_in_guest ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  backtrace_ops ; 
 int /*<<< orphan*/  dump_trace (int /*<<< orphan*/ *,struct pt_regs*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct perf_callchain_entry*) ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry*,int /*<<< orphan*/ ) ; 
 TYPE_1__* perf_guest_cbs ; 
 scalar_t__ stub1 () ; 

void
perf_callchain_kernel(struct perf_callchain_entry *entry, struct pt_regs *regs)
{
	if (perf_guest_cbs && perf_guest_cbs->is_in_guest()) {
		/* TODO: We don't support guest os callchain now */
		return;
	}

	perf_callchain_store(entry, regs->ip);

	dump_trace(NULL, regs, NULL, &backtrace_ops, entry);
}