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
struct rcu_state {struct rcu_node* node; int /*<<< orphan*/  orphan_qlen; int /*<<< orphan*/  n_force_qs_lh; scalar_t__ n_force_qs_ngp; scalar_t__ n_force_qs; scalar_t__ jiffies_force_qs; int /*<<< orphan*/  signaled; int /*<<< orphan*/  gpnum; int /*<<< orphan*/  completed; } ;
struct rcu_node {int level; int /*<<< orphan*/  grpnum; int /*<<< orphan*/  grphi; int /*<<< orphan*/  grplo; int /*<<< orphan*/  qsmaskinit; int /*<<< orphan*/  qsmask; } ;

/* Variables and functions */
 int NUM_RCU_NODES ; 
 int jiffies ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void print_one_rcu_state(struct seq_file *m, struct rcu_state *rsp)
{
	int level = 0;
	struct rcu_node *rnp;

	seq_printf(m, "c=%ld g=%ld s=%d jfq=%ld j=%x "
		      "nfqs=%lu/nfqsng=%lu(%lu) fqlh=%lu oqlen=%ld\n",
		   rsp->completed, rsp->gpnum, rsp->signaled,
		   (long)(rsp->jiffies_force_qs - jiffies),
		   (int)(jiffies & 0xffff),
		   rsp->n_force_qs, rsp->n_force_qs_ngp,
		   rsp->n_force_qs - rsp->n_force_qs_ngp,
		   rsp->n_force_qs_lh, rsp->orphan_qlen);
	for (rnp = &rsp->node[0]; rnp - &rsp->node[0] < NUM_RCU_NODES; rnp++) {
		if (rnp->level != level) {
			seq_puts(m, "\n");
			level = rnp->level;
		}
		seq_printf(m, "%lx/%lx %d:%d ^%d    ",
			   rnp->qsmask, rnp->qsmaskinit,
			   rnp->grplo, rnp->grphi, rnp->grpnum);
	}
	seq_puts(m, "\n");
}