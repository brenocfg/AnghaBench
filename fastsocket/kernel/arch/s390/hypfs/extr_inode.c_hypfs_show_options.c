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
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct seq_file {int dummy; } ;
struct hypfs_sb_info {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_2__ {struct hypfs_sb_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hypfs_show_options(struct seq_file *s, struct vfsmount *mnt)
{
	struct hypfs_sb_info *hypfs_info = mnt->mnt_sb->s_fs_info;

	seq_printf(s, ",uid=%u", hypfs_info->uid);
	seq_printf(s, ",gid=%u", hypfs_info->gid);
	return 0;
}