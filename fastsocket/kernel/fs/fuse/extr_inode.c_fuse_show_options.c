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
struct fuse_conn {int flags; int /*<<< orphan*/  max_read; int /*<<< orphan*/  group_id; int /*<<< orphan*/  user_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; scalar_t__ s_bdev; } ;

/* Variables and functions */
 int FUSE_ALLOW_OTHER ; 
 int /*<<< orphan*/  FUSE_DEFAULT_BLKSIZE ; 
 int FUSE_DEFAULT_PERMISSIONS ; 
 struct fuse_conn* get_fuse_conn_super (TYPE_1__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int fuse_show_options(struct seq_file *m, struct vfsmount *mnt)
{
	struct fuse_conn *fc = get_fuse_conn_super(mnt->mnt_sb);

	seq_printf(m, ",user_id=%u", fc->user_id);
	seq_printf(m, ",group_id=%u", fc->group_id);
	if (fc->flags & FUSE_DEFAULT_PERMISSIONS)
		seq_puts(m, ",default_permissions");
	if (fc->flags & FUSE_ALLOW_OTHER)
		seq_puts(m, ",allow_other");
	if (fc->max_read != ~0)
		seq_printf(m, ",max_read=%u", fc->max_read);
	if (mnt->mnt_sb->s_bdev &&
	    mnt->mnt_sb->s_blocksize != FUSE_DEFAULT_BLKSIZE)
		seq_printf(m, ",blksize=%lu", mnt->mnt_sb->s_blocksize);
	return 0;
}