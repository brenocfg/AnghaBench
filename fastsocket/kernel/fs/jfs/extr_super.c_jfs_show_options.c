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
struct vfsmount {int /*<<< orphan*/  mnt_sb; } ;
struct seq_file {int dummy; } ;
struct jfs_sb_info {int uid; int gid; int umask; int flag; TYPE_1__* nls_tab; } ;
struct TYPE_2__ {int /*<<< orphan*/  charset; } ;

/* Variables and functions */
 int JFS_ERR_CONTINUE ; 
 int JFS_ERR_PANIC ; 
 int JFS_GRPQUOTA ; 
 int JFS_NOINTEGRITY ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int JFS_USRQUOTA ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int jfs_show_options(struct seq_file *seq, struct vfsmount *vfs)
{
	struct jfs_sb_info *sbi = JFS_SBI(vfs->mnt_sb);

	if (sbi->uid != -1)
		seq_printf(seq, ",uid=%d", sbi->uid);
	if (sbi->gid != -1)
		seq_printf(seq, ",gid=%d", sbi->gid);
	if (sbi->umask != -1)
		seq_printf(seq, ",umask=%03o", sbi->umask);
	if (sbi->flag & JFS_NOINTEGRITY)
		seq_puts(seq, ",nointegrity");
	if (sbi->nls_tab)
		seq_printf(seq, ",iocharset=%s", sbi->nls_tab->charset);
	if (sbi->flag & JFS_ERR_CONTINUE)
		seq_printf(seq, ",errors=continue");
	if (sbi->flag & JFS_ERR_PANIC)
		seq_printf(seq, ",errors=panic");

#ifdef CONFIG_QUOTA
	if (sbi->flag & JFS_USRQUOTA)
		seq_puts(seq, ",usrquota");

	if (sbi->flag & JFS_GRPQUOTA)
		seq_puts(seq, ",grpquota");
#endif

	return 0;
}