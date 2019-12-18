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
struct TYPE_2__ {int /*<<< orphan*/  xs_qm_dqinact_reclaims; int /*<<< orphan*/  xs_qm_dqshake_reclaims; int /*<<< orphan*/  xs_qm_dqwants; int /*<<< orphan*/  xs_qm_dqcachehits; int /*<<< orphan*/  xs_qm_dqcachemisses; int /*<<< orphan*/  xs_qm_dquot_dups; int /*<<< orphan*/  xs_qm_dqreclaim_misses; int /*<<< orphan*/  xs_qm_dqreclaims; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ xqmstats ; 

__attribute__((used)) static int xqmstat_proc_show(struct seq_file *m, void *v)
{
	/* quota performance statistics */
	seq_printf(m, "qm %u %u %u %u %u %u %u %u\n",
			xqmstats.xs_qm_dqreclaims,
			xqmstats.xs_qm_dqreclaim_misses,
			xqmstats.xs_qm_dquot_dups,
			xqmstats.xs_qm_dqcachemisses,
			xqmstats.xs_qm_dqcachehits,
			xqmstats.xs_qm_dqwants,
			xqmstats.xs_qm_dqshake_reclaims,
			xqmstats.xs_qm_dqinact_reclaims);
	return 0;
}