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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_rcu_pendings (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_bh_state ; 
 int /*<<< orphan*/  rcu_preempt_state ; 
 int /*<<< orphan*/  rcu_sched_state ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int show_rcu_pending(struct seq_file *m, void *unused)
{
#ifdef CONFIG_TREE_PREEMPT_RCU
	seq_puts(m, "rcu_preempt:\n");
	print_rcu_pendings(m, &rcu_preempt_state);
#endif /* #ifdef CONFIG_TREE_PREEMPT_RCU */
	seq_puts(m, "rcu_sched:\n");
	print_rcu_pendings(m, &rcu_sched_state);
	seq_puts(m, "rcu_bh:\n");
	print_rcu_pendings(m, &rcu_bh_state);
	return 0;
}