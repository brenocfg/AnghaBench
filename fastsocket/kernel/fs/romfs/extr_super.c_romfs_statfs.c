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
typedef  int u64 ;
typedef  void* u32 ;
struct super_block {TYPE_1__* s_bdev; } ;
struct TYPE_4__ {void** val; } ;
struct kstatfs {int f_bsize; int f_blocks; TYPE_2__ f_fsid; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int ROMBSBITS ; 
 int ROMBSIZE ; 
 int /*<<< orphan*/  ROMFS_MAGIC ; 
 int /*<<< orphan*/  ROMFS_MAXFN ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 
 int romfs_maxsize (struct super_block*) ; 

__attribute__((used)) static int romfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = ROMFS_MAGIC;
	buf->f_namelen = ROMFS_MAXFN;
	buf->f_bsize = ROMBSIZE;
	buf->f_bfree = buf->f_bavail = buf->f_ffree;
	buf->f_blocks =
		(romfs_maxsize(dentry->d_sb) + ROMBSIZE - 1) >> ROMBSBITS;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	return 0;
}