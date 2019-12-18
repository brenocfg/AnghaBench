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
struct vfsmount {struct super_block* mnt_sb; } ;
struct super_block {int s_blocksize; } ;
struct kstat {int blocks; int blksize; int /*<<< orphan*/  size; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int sysv_nblocks (struct super_block*,int /*<<< orphan*/ ) ; 

int sysv_getattr(struct vfsmount *mnt, struct dentry *dentry, struct kstat *stat)
{
	struct super_block *s = mnt->mnt_sb;
	generic_fillattr(dentry->d_inode, stat);
	stat->blocks = (s->s_blocksize / 512) * sysv_nblocks(s, stat->size);
	stat->blksize = s->s_blocksize;
	return 0;
}