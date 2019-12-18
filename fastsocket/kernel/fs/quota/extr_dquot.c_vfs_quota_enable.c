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
struct super_block {int dummy; } ;
struct quota_info {int /*<<< orphan*/  dqonoff_mutex; int /*<<< orphan*/  flags; } ;
struct inode {struct super_block* i_sb; } ;

/* Variables and functions */
 unsigned int DQUOT_LIMITS_ENABLED ; 
 unsigned int DQUOT_SUSPENDED ; 
 unsigned int DQUOT_USAGE_ENABLED ; 
 int EBUSY ; 
 int /*<<< orphan*/  dq_state_lock ; 
 int /*<<< orphan*/  dquot_state_flag (unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 scalar_t__ sb_has_quota_limits_enabled (struct super_block*,int) ; 
 scalar_t__ sb_has_quota_loaded (struct super_block*,int) ; 
 scalar_t__ sb_has_quota_usage_enabled (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vfs_load_quota_inode (struct inode*,int,int,unsigned int) ; 
 int vfs_quota_on_remount (struct super_block*,int) ; 

int vfs_quota_enable(struct inode *inode, int type, int format_id,
		unsigned int flags)
{
	int ret = 0;
	struct super_block *sb = inode->i_sb;
	struct quota_info *dqopt = sb_dqopt(sb);

	/* Just unsuspend quotas? */
	if (flags & DQUOT_SUSPENDED)
		return vfs_quota_on_remount(sb, type);
	if (!flags)
		return 0;
	/* Just updating flags needed? */
	if (sb_has_quota_loaded(sb, type)) {
		mutex_lock(&dqopt->dqonoff_mutex);
		/* Now do a reliable test... */
		if (!sb_has_quota_loaded(sb, type)) {
			mutex_unlock(&dqopt->dqonoff_mutex);
			goto load_quota;
		}
		if (flags & DQUOT_USAGE_ENABLED &&
		    sb_has_quota_usage_enabled(sb, type)) {
			ret = -EBUSY;
			goto out_lock;
		}
		if (flags & DQUOT_LIMITS_ENABLED &&
		    sb_has_quota_limits_enabled(sb, type)) {
			ret = -EBUSY;
			goto out_lock;
		}
		spin_lock(&dq_state_lock);
		sb_dqopt(sb)->flags |= dquot_state_flag(flags, type);
		spin_unlock(&dq_state_lock);
out_lock:
		mutex_unlock(&dqopt->dqonoff_mutex);
		return ret;
	}

load_quota:
	return vfs_load_quota_inode(inode, type, format_id, flags);
}