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
typedef  int u32 ;
struct crunch_state {int dummy; } ;
struct thread_info {struct crunch_state crunchstate; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_SYSCON_DEVCFG ; 
 int EP93XX_SYSCON_DEVCFG_CPENA ; 
 int /*<<< orphan*/  EP93XX_SYSCON_SWLOCK ; 
 int NOTIFY_DONE ; 
#define  THREAD_NOTIFY_FLUSH 130 
#define  THREAD_NOTIFY_RELEASE 129 
#define  THREAD_NOTIFY_SWITCH 128 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crunch_enabled (int) ; 
 struct crunch_state* crunch_owner ; 
 int /*<<< orphan*/  crunch_task_release (struct thread_info*) ; 
 int /*<<< orphan*/  memset (struct crunch_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int crunch_do(struct notifier_block *self, unsigned long cmd, void *t)
{
	struct thread_info *thread = (struct thread_info *)t;
	struct crunch_state *crunch_state;
	u32 devcfg;

	crunch_state = &thread->crunchstate;

	switch (cmd) {
	case THREAD_NOTIFY_FLUSH:
		memset(crunch_state, 0, sizeof(*crunch_state));

		/*
		 * FALLTHROUGH: Ensure we don't try to overwrite our newly
		 * initialised state information on the first fault.
		 */

	case THREAD_NOTIFY_RELEASE:
		crunch_task_release(thread);
		break;

	case THREAD_NOTIFY_SWITCH:
		devcfg = __raw_readl(EP93XX_SYSCON_DEVCFG);
		if (crunch_enabled(devcfg) || crunch_owner == crunch_state) {
			/*
			 * We don't use ep93xx_syscon_swlocked_write() here
			 * because we are on the context switch path and
			 * preemption is already disabled.
			 */
			devcfg ^= EP93XX_SYSCON_DEVCFG_CPENA;
			__raw_writel(0xaa, EP93XX_SYSCON_SWLOCK);
			__raw_writel(devcfg, EP93XX_SYSCON_DEVCFG);
		}
		break;
	}

	return NOTIFY_DONE;
}