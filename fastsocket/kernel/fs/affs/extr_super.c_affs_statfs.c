#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
struct super_block {int /*<<< orphan*/  s_blocksize; TYPE_1__* s_bdev; } ;
struct TYPE_5__ {void** val; } ;
struct kstatfs {int f_bfree; int f_bavail; int f_namelen; TYPE_2__ f_fsid; scalar_t__ f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_6__ {scalar_t__ s_reserved; scalar_t__ s_partition_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 TYPE_3__* AFFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  AFFS_SUPER_MAGIC ; 
 int affs_count_free_blocks (struct super_block*) ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
affs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	int		 free;
	u64		 id = huge_encode_dev(sb->s_bdev->bd_dev);

	pr_debug("AFFS: statfs() partsize=%d, reserved=%d\n",AFFS_SB(sb)->s_partition_size,
	     AFFS_SB(sb)->s_reserved);

	free          = affs_count_free_blocks(sb);
	buf->f_type    = AFFS_SUPER_MAGIC;
	buf->f_bsize   = sb->s_blocksize;
	buf->f_blocks  = AFFS_SB(sb)->s_partition_size - AFFS_SB(sb)->s_reserved;
	buf->f_bfree   = free;
	buf->f_bavail  = free;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	buf->f_namelen = 30;
	return 0;
}