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
 int /*<<< orphan*/  PRINT_RCU_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct seq_file*) ; 
 int /*<<< orphan*/  print_one_rcu_data_csv ; 
 int /*<<< orphan*/  rcu_bh_data ; 
 int /*<<< orphan*/  rcu_preempt_data ; 
 int /*<<< orphan*/  rcu_sched_data ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int show_rcudata_csv(struct seq_file *m, void *unused)
{
	seq_puts(m, "\"CPU\",\"Online?\",\"c\",\"g\",\"pq\",\"pqc\",\"pq\",");
#ifdef CONFIG_NO_HZ
	seq_puts(m, "\"dt\",\"dt nesting\",\"dn\",\"df\",");
#endif /* #ifdef CONFIG_NO_HZ */
	seq_puts(m, "\"of\",\"ri\",\"ql\",\"b\"\n");
#ifdef CONFIG_TREE_PREEMPT_RCU
	seq_puts(m, "\"rcu_preempt:\"\n");
	PRINT_RCU_DATA(rcu_preempt_data, print_one_rcu_data_csv, m);
#endif /* #ifdef CONFIG_TREE_PREEMPT_RCU */
	seq_puts(m, "\"rcu_sched:\"\n");
	PRINT_RCU_DATA(rcu_sched_data, print_one_rcu_data_csv, m);
	seq_puts(m, "\"rcu_bh:\"\n");
	PRINT_RCU_DATA(rcu_bh_data, print_one_rcu_data_csv, m);
	return 0;
}