#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* dq_op; } ;
struct mem_dqinfo {int dqi_flags; int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; } ;
struct if_dqinfo {int dqi_valid; int dqi_flags; int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; } ;
struct TYPE_4__ {int /*<<< orphan*/  dqonoff_mutex; struct mem_dqinfo* info; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_info ) (struct super_block*,int) ;} ;

/* Variables and functions */
 int DQF_MASK ; 
 int ESRCH ; 
 int IIF_BGRACE ; 
 int IIF_FLAGS ; 
 int IIF_IGRACE ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  mark_info_dirty (struct super_block*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_quota_active (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int) ; 

int vfs_set_dqinfo(struct super_block *sb, int type, struct if_dqinfo *ii)
{
	struct mem_dqinfo *mi;
	int err = 0;

	mutex_lock(&sb_dqopt(sb)->dqonoff_mutex);
	if (!sb_has_quota_active(sb, type)) {
		err = -ESRCH;
		goto out;
	}
	mi = sb_dqopt(sb)->info + type;
	spin_lock(&dq_data_lock);
	if (ii->dqi_valid & IIF_BGRACE)
		mi->dqi_bgrace = ii->dqi_bgrace;
	if (ii->dqi_valid & IIF_IGRACE)
		mi->dqi_igrace = ii->dqi_igrace;
	if (ii->dqi_valid & IIF_FLAGS)
		mi->dqi_flags = (mi->dqi_flags & ~DQF_MASK) |
				(ii->dqi_flags & DQF_MASK);
	spin_unlock(&dq_data_lock);
	mark_info_dirty(sb, type);
	/* Force write to disk */
	sb->dq_op->write_info(sb, type);
out:
	mutex_unlock(&sb_dqopt(sb)->dqonoff_mutex);
	return err;
}