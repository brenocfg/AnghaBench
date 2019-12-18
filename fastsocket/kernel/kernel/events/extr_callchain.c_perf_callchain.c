#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct perf_callchain_entry {scalar_t__ nr; } ;
struct TYPE_3__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_CONTEXT_KERNEL ; 
 int /*<<< orphan*/  PERF_CONTEXT_USER ; 
 TYPE_1__* current ; 
 struct perf_callchain_entry* get_callchain_entry (int*) ; 
 int /*<<< orphan*/  perf_callchain_kernel (struct perf_callchain_entry*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_callchain_user (struct perf_callchain_entry*,struct pt_regs*) ; 
 int /*<<< orphan*/  put_callchain_entry (int) ; 
 struct pt_regs* task_pt_regs (TYPE_1__*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

struct perf_callchain_entry *perf_callchain(struct pt_regs *regs)
{
	int rctx;
	struct perf_callchain_entry *entry;


	entry = get_callchain_entry(&rctx);
	if (rctx == -1)
		return NULL;

	if (!entry)
		goto exit_put;

	entry->nr = 0;

	if (!user_mode(regs)) {
		perf_callchain_store(entry, PERF_CONTEXT_KERNEL);
		perf_callchain_kernel(entry, regs);
		if (current->mm)
			regs = task_pt_regs(current);
		else
			regs = NULL;
	}

	if (regs) {
		perf_callchain_store(entry, PERF_CONTEXT_USER);
		perf_callchain_user(entry, regs);
	}

exit_put:
	put_callchain_entry(rctx);

	return entry;
}