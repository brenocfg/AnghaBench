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
struct vfsmount {TYPE_2__* mnt_sb; } ;
struct seq_file {int dummy; } ;
struct inode {scalar_t__ i_uid; scalar_t__ i_gid; } ;
struct autofs_sb_info {int exp_timeout; int /*<<< orphan*/  type; int /*<<< orphan*/  max_proto; int /*<<< orphan*/  min_proto; int /*<<< orphan*/  oz_pgrp; int /*<<< orphan*/  pipefd; } ;
struct TYPE_4__ {TYPE_1__* s_root; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int HZ ; 
 struct autofs_sb_info* autofs4_sbi (TYPE_2__*) ; 
 scalar_t__ autofs_type_direct (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_type_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int autofs4_show_options(struct seq_file *m, struct vfsmount *mnt)
{
	struct autofs_sb_info *sbi = autofs4_sbi(mnt->mnt_sb);
	struct inode *root_inode = mnt->mnt_sb->s_root->d_inode;

	if (!sbi)
		return 0;

	seq_printf(m, ",fd=%d", sbi->pipefd);
	if (root_inode->i_uid != 0)
		seq_printf(m, ",uid=%u", root_inode->i_uid);
	if (root_inode->i_gid != 0)
		seq_printf(m, ",gid=%u", root_inode->i_gid);
	seq_printf(m, ",pgrp=%d", sbi->oz_pgrp);
	seq_printf(m, ",timeout=%lu", sbi->exp_timeout/HZ);
	seq_printf(m, ",minproto=%d", sbi->min_proto);
	seq_printf(m, ",maxproto=%d", sbi->max_proto);

	if (autofs_type_offset(sbi->type))
		seq_printf(m, ",offset");
	else if (autofs_type_direct(sbi->type))
		seq_printf(m, ",direct");
	else
		seq_printf(m, ",indirect");

	return 0;
}