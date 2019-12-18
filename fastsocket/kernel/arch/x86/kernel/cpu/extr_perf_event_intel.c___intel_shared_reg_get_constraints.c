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
struct perf_event {int dummy; } ;
struct hw_perf_event_extra {int idx; int alloc; scalar_t__ config; int /*<<< orphan*/  reg; } ;
struct event_constraint {int dummy; } ;
struct er_account {scalar_t__ config; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; int /*<<< orphan*/  reg; } ;
struct cpu_hw_events {TYPE_1__* shared_regs; } ;
struct TYPE_2__ {struct er_account* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct event_constraint emptyconstraint ; 
 scalar_t__ intel_try_alt_er (struct perf_event*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct event_constraint *
__intel_shared_reg_get_constraints(struct cpu_hw_events *cpuc,
				   struct perf_event *event,
				   struct hw_perf_event_extra *reg)
{
	struct event_constraint *c = &emptyconstraint;
	struct er_account *era;
	unsigned long flags;
	int orig_idx = reg->idx;

	/* already allocated shared msr */
	if (reg->alloc)
		return NULL; /* call x86_get_event_constraint() */

again:
	era = &cpuc->shared_regs->regs[reg->idx];
	/*
	 * we use spin_lock_irqsave() to avoid lockdep issues when
	 * passing a fake cpuc
	 */
	spin_lock_irqsave(&era->lock, flags);

	if (!atomic_read(&era->ref) || era->config == reg->config) {

		/* lock in msr value */
		era->config = reg->config;
		era->reg = reg->reg;

		/* one more user */
		atomic_inc(&era->ref);

		/* no need to reallocate during incremental event scheduling */
		reg->alloc = 1;

		/*
		 * need to call x86_get_event_constraint()
		 * to check if associated event has constraints
		 */
		c = NULL;
	} else if (intel_try_alt_er(event, orig_idx)) {
		spin_unlock_irqrestore(&era->lock, flags);
		goto again;
	}
	spin_unlock_irqrestore(&era->lock, flags);

	return c;
}