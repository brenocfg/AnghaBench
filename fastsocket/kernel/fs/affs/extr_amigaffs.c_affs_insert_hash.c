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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;
struct TYPE_4__ {void** table; } ;
struct TYPE_3__ {void* hash_chain; void* parent; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_2__* AFFS_HEAD (struct buffer_head*) ; 
 TYPE_1__* AFFS_TAIL (struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EIO ; 
 int /*<<< orphan*/  affs_adjust_checksum (struct buffer_head*,scalar_t__) ; 
 struct buffer_head* affs_bread (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  affs_fix_checksum (struct super_block*,struct buffer_head*) ; 
 int affs_hash_name (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 

int
affs_insert_hash(struct inode *dir, struct buffer_head *bh)
{
	struct super_block *sb = dir->i_sb;
	struct buffer_head *dir_bh;
	u32 ino, hash_ino;
	int offset;

	ino = bh->b_blocknr;
	offset = affs_hash_name(sb, AFFS_TAIL(sb, bh)->name + 1, AFFS_TAIL(sb, bh)->name[0]);

	pr_debug("AFFS: insert_hash(dir=%u, ino=%d)\n", (u32)dir->i_ino, ino);

	dir_bh = affs_bread(sb, dir->i_ino);
	if (!dir_bh)
		return -EIO;

	hash_ino = be32_to_cpu(AFFS_HEAD(dir_bh)->table[offset]);
	while (hash_ino) {
		affs_brelse(dir_bh);
		dir_bh = affs_bread(sb, hash_ino);
		if (!dir_bh)
			return -EIO;
		hash_ino = be32_to_cpu(AFFS_TAIL(sb, dir_bh)->hash_chain);
	}
	AFFS_TAIL(sb, bh)->parent = cpu_to_be32(dir->i_ino);
	AFFS_TAIL(sb, bh)->hash_chain = 0;
	affs_fix_checksum(sb, bh);

	if (dir->i_ino == dir_bh->b_blocknr)
		AFFS_HEAD(dir_bh)->table[offset] = cpu_to_be32(ino);
	else
		AFFS_TAIL(sb, dir_bh)->hash_chain = cpu_to_be32(ino);

	affs_adjust_checksum(dir_bh, ino);
	mark_buffer_dirty_inode(dir_bh, dir);
	affs_brelse(dir_bh);

	dir->i_mtime = dir->i_ctime = CURRENT_TIME_SEC;
	dir->i_version++;
	mark_inode_dirty(dir);

	return 0;
}