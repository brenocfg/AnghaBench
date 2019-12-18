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
struct super_block {int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_magic; TYPE_1__* s_bdev; } ;
struct minix_sb_info {int s_nzones; int s_firstdatazone; int s_log_zone_size; int /*<<< orphan*/  s_namelen; int /*<<< orphan*/  s_ninodes; } ;
struct TYPE_4__ {void** val; } ;
struct kstatfs {int f_blocks; TYPE_2__ f_fsid; int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int huge_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minix_count_free_blocks (struct minix_sb_info*) ; 
 int /*<<< orphan*/  minix_count_free_inodes (struct minix_sb_info*) ; 
 struct minix_sb_info* minix_sb (struct super_block*) ; 

__attribute__((used)) static int minix_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct minix_sb_info *sbi = minix_sb(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);
	buf->f_type = sb->s_magic;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = (sbi->s_nzones - sbi->s_firstdatazone) << sbi->s_log_zone_size;
	buf->f_bfree = minix_count_free_blocks(sbi);
	buf->f_bavail = buf->f_bfree;
	buf->f_files = sbi->s_ninodes;
	buf->f_ffree = minix_count_free_inodes(sbi);
	buf->f_namelen = sbi->s_namelen;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);

	return 0;
}