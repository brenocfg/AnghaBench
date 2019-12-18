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
typedef  void* __be32 ;
struct TYPE_4__ {void** table; } ;
struct TYPE_3__ {void* hash_chain; scalar_t__ parent; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_2__* AFFS_HEAD (struct buffer_head*) ; 
 TYPE_1__* AFFS_TAIL (struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  affs_adjust_checksum (struct buffer_head*,scalar_t__) ; 
 struct buffer_head* affs_bread (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int affs_hash_name (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,int) ; 

int
affs_remove_hash(struct inode *dir, struct buffer_head *rem_bh)
{
	struct super_block *sb;
	struct buffer_head *bh;
	u32 rem_ino, hash_ino;
	__be32 ino;
	int offset, retval;

	sb = dir->i_sb;
	rem_ino = rem_bh->b_blocknr;
	offset = affs_hash_name(sb, AFFS_TAIL(sb, rem_bh)->name+1, AFFS_TAIL(sb, rem_bh)->name[0]);
	pr_debug("AFFS: remove_hash(dir=%d, ino=%d, hashval=%d)\n", (u32)dir->i_ino, rem_ino, offset);

	bh = affs_bread(sb, dir->i_ino);
	if (!bh)
		return -EIO;

	retval = -ENOENT;
	hash_ino = be32_to_cpu(AFFS_HEAD(bh)->table[offset]);
	while (hash_ino) {
		if (hash_ino == rem_ino) {
			ino = AFFS_TAIL(sb, rem_bh)->hash_chain;
			if (dir->i_ino == bh->b_blocknr)
				AFFS_HEAD(bh)->table[offset] = ino;
			else
				AFFS_TAIL(sb, bh)->hash_chain = ino;
			affs_adjust_checksum(bh, be32_to_cpu(ino) - hash_ino);
			mark_buffer_dirty_inode(bh, dir);
			AFFS_TAIL(sb, rem_bh)->parent = 0;
			retval = 0;
			break;
		}
		affs_brelse(bh);
		bh = affs_bread(sb, hash_ino);
		if (!bh)
			return -EIO;
		hash_ino = be32_to_cpu(AFFS_TAIL(sb, bh)->hash_chain);
	}

	affs_brelse(bh);

	dir->i_mtime = dir->i_ctime = CURRENT_TIME_SEC;
	dir->i_version++;
	mark_inode_dirty(dir);

	return retval;
}