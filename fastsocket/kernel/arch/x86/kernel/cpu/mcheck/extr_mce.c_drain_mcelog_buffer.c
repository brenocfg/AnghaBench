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
struct mce {int /*<<< orphan*/  finished; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; struct mce* entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mce*) ; 
 unsigned int cmpxchg (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 TYPE_1__ mcelog ; 
 int /*<<< orphan*/  memset (struct mce*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned int rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  x86_mce_decoder_chain ; 

__attribute__((used)) static void drain_mcelog_buffer(void)
{
	unsigned int next, i, prev = 0;

	next = rcu_dereference(mcelog.next);

	do {
		struct mce *m;

		/* drain what was logged during boot */
		for (i = prev; i < next; i++) {
			unsigned long start = jiffies;
			unsigned retries = 1;

			m = &mcelog.entry[i];

			while (!m->finished) {
				if (time_after_eq(jiffies, start + 2*retries))
					retries++;

				cpu_relax();

				if (!m->finished && retries >= 4) {
					pr_err("MCE: skipping error being logged currently!\n");
					break;
				}
			}
			smp_rmb();
			atomic_notifier_call_chain(&x86_mce_decoder_chain, 0, m);
		}

		memset(mcelog.entry + prev, 0, (next - prev) * sizeof(*m));
		prev = next;
		next = cmpxchg(&mcelog.next, prev, 0);
	} while (next != prev);
}