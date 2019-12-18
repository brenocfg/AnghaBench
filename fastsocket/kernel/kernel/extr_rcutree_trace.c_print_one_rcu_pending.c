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
struct rcu_data {int /*<<< orphan*/  n_rp_need_nothing; int /*<<< orphan*/  n_rp_need_fqs; int /*<<< orphan*/  n_rp_gp_started; int /*<<< orphan*/  n_rp_gp_completed; int /*<<< orphan*/  n_rp_cpu_needs_gp; int /*<<< orphan*/  n_rp_cb_ready; int /*<<< orphan*/  n_rp_qs_pending; int /*<<< orphan*/  n_rcu_pending; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 scalar_t__ cpu_is_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_one_rcu_pending(struct seq_file *m, struct rcu_data *rdp)
{
	seq_printf(m, "%3d%cnp=%ld "
		   "qsp=%ld cbr=%ld cng=%ld gpc=%ld gps=%ld nf=%ld nn=%ld\n",
		   rdp->cpu,
		   cpu_is_offline(rdp->cpu) ? '!' : ' ',
		   rdp->n_rcu_pending,
		   rdp->n_rp_qs_pending,
		   rdp->n_rp_cb_ready,
		   rdp->n_rp_cpu_needs_gp,
		   rdp->n_rp_gp_completed,
		   rdp->n_rp_gp_started,
		   rdp->n_rp_need_fqs,
		   rdp->n_rp_need_nothing);
}