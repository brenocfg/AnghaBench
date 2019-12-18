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
struct ocfs2_mem_dqinfo {int /*<<< orphan*/ * dqi_gqi_bh; int /*<<< orphan*/  dqi_gqi_count; int /*<<< orphan*/  dqi_gqinode; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ocfs2_unlock_global_qf(struct ocfs2_mem_dqinfo *oinfo, int ex)
{
	ocfs2_inode_unlock(oinfo->dqi_gqinode, ex);
	brelse(oinfo->dqi_gqi_bh);
	spin_lock(&dq_data_lock);
	if (!--oinfo->dqi_gqi_count)
		oinfo->dqi_gqi_bh = NULL;
	spin_unlock(&dq_data_lock);
}