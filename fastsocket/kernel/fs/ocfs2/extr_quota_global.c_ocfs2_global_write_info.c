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
struct ocfs2_mem_dqinfo {int dummy; } ;
struct TYPE_2__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 int __ocfs2_global_write_info (struct super_block*,int) ; 
 int ocfs2_qinfo_lock (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/  ocfs2_qinfo_unlock (struct ocfs2_mem_dqinfo*,int) ; 
 TYPE_1__* sb_dqinfo (struct super_block*,int) ; 

int ocfs2_global_write_info(struct super_block *sb, int type)
{
	int err;
	struct ocfs2_mem_dqinfo *info = sb_dqinfo(sb, type)->dqi_priv;

	err = ocfs2_qinfo_lock(info, 1);
	if (err < 0)
		return err;
	err = __ocfs2_global_write_info(sb, type);
	ocfs2_qinfo_unlock(info, 1);
	return err;
}