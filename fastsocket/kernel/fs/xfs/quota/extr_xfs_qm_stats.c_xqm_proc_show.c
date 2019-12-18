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
struct TYPE_2__ {int /*<<< orphan*/  qm_dqfrlist_cnt; int /*<<< orphan*/  qm_dqfree_ratio; int /*<<< orphan*/  qm_totaldquots; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndquot ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xfs_Gqm ; 

__attribute__((used)) static int xqm_proc_show(struct seq_file *m, void *v)
{
	/* maximum; incore; ratio free to inuse; freelist */
	seq_printf(m, "%d\t%d\t%d\t%u\n",
			ndquot,
			xfs_Gqm? atomic_read(&xfs_Gqm->qm_totaldquots) : 0,
			xfs_Gqm? xfs_Gqm->qm_dqfree_ratio : 0,
			xfs_Gqm? xfs_Gqm->qm_dqfrlist_cnt : 0);
	return 0;
}