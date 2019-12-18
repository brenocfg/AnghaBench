#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  gpnum; int /*<<< orphan*/  completed; } ;
struct TYPE_5__ {int /*<<< orphan*/  gpnum; int /*<<< orphan*/  completed; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpnum; int /*<<< orphan*/  completed; } ;

/* Variables and functions */
 TYPE_3__ rcu_bh_state ; 
 TYPE_2__ rcu_preempt_state ; 
 TYPE_1__ rcu_sched_state ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_rcugp(struct seq_file *m, void *unused)
{
#ifdef CONFIG_TREE_PREEMPT_RCU
	seq_printf(m, "rcu_preempt: completed=%ld  gpnum=%ld\n",
		   rcu_preempt_state.completed, rcu_preempt_state.gpnum);
#endif /* #ifdef CONFIG_TREE_PREEMPT_RCU */
	seq_printf(m, "rcu_sched: completed=%ld  gpnum=%ld\n",
		   rcu_sched_state.completed, rcu_sched_state.gpnum);
	seq_printf(m, "rcu_bh: completed=%ld  gpnum=%ld\n",
		   rcu_bh_state.completed, rcu_bh_state.gpnum);
	return 0;
}