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
struct ocfs2_mem_dqinfo {int dummy; } ;
struct dquot {int /*<<< orphan*/  dq_type; int /*<<< orphan*/  dq_id; int /*<<< orphan*/  dq_sb; } ;
struct TYPE_2__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 int dquot_acquire (struct dquot*) ; 
 int /*<<< orphan*/  mlog_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_lock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/  ocfs2_unlock_global_qf (struct ocfs2_mem_dqinfo*,int) ; 
 TYPE_1__* sb_dqinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_acquire_dquot(struct dquot *dquot)
{
	struct ocfs2_mem_dqinfo *oinfo =
			sb_dqinfo(dquot->dq_sb, dquot->dq_type)->dqi_priv;
	int status = 0;

	mlog_entry("id=%u, type=%d", dquot->dq_id, dquot->dq_type);
	/* We need an exclusive lock, because we're going to update use count
	 * and instantiate possibly new dquot structure */
	status = ocfs2_lock_global_qf(oinfo, 1);
	if (status < 0)
		goto out;
	status = dquot_acquire(dquot);
	ocfs2_unlock_global_qf(oinfo, 1);
out:
	mlog_exit(status);
	return status;
}