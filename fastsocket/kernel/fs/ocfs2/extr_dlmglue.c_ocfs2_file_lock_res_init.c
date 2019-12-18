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
struct ocfs2_lock_res {int /*<<< orphan*/  l_flags; int /*<<< orphan*/  l_name; } ;
struct ocfs2_inode_info {int /*<<< orphan*/  ip_blkno; } ;
struct ocfs2_file_private {TYPE_2__* fp_file; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_generation; } ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_LOCK_NOCACHE ; 
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_FLOCK ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_build_lock_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_flock_lops ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_common (int /*<<< orphan*/ ,struct ocfs2_lock_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_file_private*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_once (struct ocfs2_lock_res*) ; 

void ocfs2_file_lock_res_init(struct ocfs2_lock_res *lockres,
			      struct ocfs2_file_private *fp)
{
	struct inode *inode = fp->fp_file->f_mapping->host;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);

	ocfs2_lock_res_init_once(lockres);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_FLOCK, oi->ip_blkno,
			      inode->i_generation, lockres->l_name);
	ocfs2_lock_res_init_common(OCFS2_SB(inode->i_sb), lockres,
				   OCFS2_LOCK_TYPE_FLOCK, &ocfs2_flock_lops,
				   fp);
	lockres->l_flags |= OCFS2_LOCK_NOCACHE;
}