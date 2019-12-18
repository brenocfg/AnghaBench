#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mce {int finished; } ;
struct TYPE_4__ {TYPE_1__* entry; int /*<<< orphan*/  next; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int finished; } ;

/* Variables and functions */
 unsigned int MCE_LOG_LEN ; 
 int /*<<< orphan*/  MCE_OVERFLOW ; 
 int NOTIFY_STOP ; 
 int atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mce*) ; 
 unsigned int cmpxchg (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 unsigned long mce_need_notify ; 
 TYPE_2__ mcelog ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct mce*,int) ; 
 unsigned int rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  trace_mce_record (struct mce*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  x86_mce_decoder_chain ; 

void mce_log(struct mce *mce)
{
	unsigned next, entry;
	int ret = 0;

	/* Emit the trace record: */
	trace_mce_record(mce);

	ret = atomic_notifier_call_chain(&x86_mce_decoder_chain, 0, mce);
	if (ret == NOTIFY_STOP)
		return;

	mce->finished = 0;
	wmb();
	for (;;) {
		entry = rcu_dereference(mcelog.next);
		for (;;) {

			/*
			 * When the buffer fills up discard new entries.
			 * Assume that the earlier errors are the more
			 * interesting ones:
			 */
			if (entry >= MCE_LOG_LEN) {
				set_bit(MCE_OVERFLOW,
					(unsigned long *)&mcelog.flags);
				return;
			}
			/* Old left over entry. Skip: */
			if (mcelog.entry[entry].finished) {
				entry++;
				continue;
			}
			break;
		}
		smp_rmb();
		next = entry + 1;
		if (cmpxchg(&mcelog.next, entry, next) == entry)
			break;
	}
	memcpy(mcelog.entry + entry, mce, sizeof(struct mce));
	wmb();
	mcelog.entry[entry].finished = 1;
	wmb();

	mce->finished = 1;
	set_bit(0, &mce_need_notify);
}