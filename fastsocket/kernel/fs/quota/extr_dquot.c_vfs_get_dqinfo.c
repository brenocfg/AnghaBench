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
struct super_block {int dummy; } ;
struct mem_dqinfo {int dqi_flags; int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; } ;
struct if_dqinfo {int dqi_flags; int /*<<< orphan*/  dqi_valid; int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqonoff_mutex; struct mem_dqinfo* info; } ;

/* Variables and functions */
 int DQF_MASK ; 
 int ESRCH ; 
 int /*<<< orphan*/  IIF_ALL ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_quota_active (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int vfs_get_dqinfo(struct super_block *sb, int type, struct if_dqinfo *ii)
{
	struct mem_dqinfo *mi;
  
	mutex_lock(&sb_dqopt(sb)->dqonoff_mutex);
	if (!sb_has_quota_active(sb, type)) {
		mutex_unlock(&sb_dqopt(sb)->dqonoff_mutex);
		return -ESRCH;
	}
	mi = sb_dqopt(sb)->info + type;
	spin_lock(&dq_data_lock);
	ii->dqi_bgrace = mi->dqi_bgrace;
	ii->dqi_igrace = mi->dqi_igrace;
	ii->dqi_flags = mi->dqi_flags & DQF_MASK;
	ii->dqi_valid = IIF_ALL;
	spin_unlock(&dq_data_lock);
	mutex_unlock(&sb_dqopt(sb)->dqonoff_mutex);
	return 0;
}