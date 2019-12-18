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
struct quota_info {int /*<<< orphan*/  dqio_mutex; TYPE_1__** ops; } ;
struct dquot {size_t dq_type; int /*<<< orphan*/  dq_flags; int /*<<< orphan*/  dq_sb; } ;
struct TYPE_2__ {int (* commit_dqblk ) (struct dquot*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_ACTIVE_B ; 
 int EIO ; 
 int /*<<< orphan*/  clear_dquot_dirty (struct dquot*) ; 
 int /*<<< orphan*/  dq_list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct quota_info* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct dquot*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dquot_commit(struct dquot *dquot)
{
	int ret = 0;
	struct quota_info *dqopt = sb_dqopt(dquot->dq_sb);

	mutex_lock(&dqopt->dqio_mutex);
	spin_lock(&dq_list_lock);
	if (!clear_dquot_dirty(dquot)) {
		spin_unlock(&dq_list_lock);
		goto out_sem;
	}
	spin_unlock(&dq_list_lock);
	/* Inactive dquot can be only if there was error during read/init
	 * => we have better not writing it */
	if (test_bit(DQ_ACTIVE_B, &dquot->dq_flags))
		ret = dqopt->ops[dquot->dq_type]->commit_dqblk(dquot);
	else
		ret = -EIO;
out_sem:
	mutex_unlock(&dqopt->dqio_mutex);
	return ret;
}