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
struct seq_file {int dummy; } ;
struct rcu_data {int /*<<< orphan*/  blimit; int /*<<< orphan*/  qlen; int /*<<< orphan*/  resched_ipi; int /*<<< orphan*/  offline_fqs; int /*<<< orphan*/  dynticks_fqs; TYPE_1__* dynticks; int /*<<< orphan*/  qs_pending; int /*<<< orphan*/  passed_quiesc_completed; int /*<<< orphan*/  passed_quiesc; int /*<<< orphan*/  gpnum; int /*<<< orphan*/  completed; int /*<<< orphan*/  cpu; int /*<<< orphan*/  beenonline; } ;
struct TYPE_2__ {int /*<<< orphan*/  dynticks_nmi; int /*<<< orphan*/  dynticks_nesting; int /*<<< orphan*/  dynticks; } ;

/* Variables and functions */
 scalar_t__ cpu_is_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,char,...) ; 

__attribute__((used)) static void print_one_rcu_data(struct seq_file *m, struct rcu_data *rdp)
{
	if (!rdp->beenonline)
		return;
	seq_printf(m, "%3d%cc=%ld g=%ld pq=%d pqc=%ld qp=%d",
		   rdp->cpu,
		   cpu_is_offline(rdp->cpu) ? '!' : ' ',
		   rdp->completed, rdp->gpnum,
		   rdp->passed_quiesc, rdp->passed_quiesc_completed,
		   rdp->qs_pending);
#ifdef CONFIG_NO_HZ
	seq_printf(m, " dt=%d/%d dn=%d df=%lu",
		   rdp->dynticks->dynticks,
		   rdp->dynticks->dynticks_nesting,
		   rdp->dynticks->dynticks_nmi,
		   rdp->dynticks_fqs);
#endif /* #ifdef CONFIG_NO_HZ */
	seq_printf(m, " of=%lu ri=%lu", rdp->offline_fqs, rdp->resched_ipi);
	seq_printf(m, " ql=%ld b=%ld\n", rdp->qlen, rdp->blimit);
}