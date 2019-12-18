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
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_ino; int i_nlink; struct super_block* i_sb; } ;
struct dentry {scalar_t__ d_fsdata; struct inode* d_inode; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  link_chain; int /*<<< orphan*/  stype; int /*<<< orphan*/  name; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 TYPE_1__* AFFS_TAIL (struct super_block*,struct buffer_head*) ; 
 int EIO ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
#define  ST_LINKDIR 129 
#define  ST_LINKFILE 128 
 int /*<<< orphan*/  affs_adjust_checksum (struct buffer_head*,scalar_t__) ; 
 struct buffer_head* affs_bread (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  affs_fix_dcache (struct dentry*,scalar_t__) ; 
 int /*<<< orphan*/  affs_free_block (struct super_block*,scalar_t__) ; 
 struct inode* affs_iget (struct super_block*,scalar_t__) ; 
 int affs_insert_hash (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  affs_lock_dir (struct inode*) ; 
 int affs_remove_hash (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  affs_unlock_dir (struct inode*) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

__attribute__((used)) static int
affs_remove_link(struct dentry *dentry)
{
	struct inode *dir, *inode = dentry->d_inode;
	struct super_block *sb = inode->i_sb;
	struct buffer_head *bh = NULL, *link_bh = NULL;
	u32 link_ino, ino;
	int retval;

	pr_debug("AFFS: remove_link(key=%ld)\n", inode->i_ino);
	retval = -EIO;
	bh = affs_bread(sb, inode->i_ino);
	if (!bh)
		goto done;

	link_ino = (u32)(long)dentry->d_fsdata;
	if (inode->i_ino == link_ino) {
		/* we can't remove the head of the link, as its blocknr is still used as ino,
		 * so we remove the block of the first link instead.
		 */ 
		link_ino = be32_to_cpu(AFFS_TAIL(sb, bh)->link_chain);
		link_bh = affs_bread(sb, link_ino);
		if (!link_bh)
			goto done;

		dir = affs_iget(sb, be32_to_cpu(AFFS_TAIL(sb, link_bh)->parent));
		if (IS_ERR(dir)) {
			retval = PTR_ERR(dir);
			goto done;
		}

		affs_lock_dir(dir);
		affs_fix_dcache(dentry, link_ino);
		retval = affs_remove_hash(dir, link_bh);
		if (retval) {
			affs_unlock_dir(dir);
			goto done;
		}
		mark_buffer_dirty_inode(link_bh, inode);

		memcpy(AFFS_TAIL(sb, bh)->name, AFFS_TAIL(sb, link_bh)->name, 32);
		retval = affs_insert_hash(dir, bh);
		if (retval) {
			affs_unlock_dir(dir);
			goto done;
		}
		mark_buffer_dirty_inode(bh, inode);

		affs_unlock_dir(dir);
		iput(dir);
	} else {
		link_bh = affs_bread(sb, link_ino);
		if (!link_bh)
			goto done;
	}

	while ((ino = be32_to_cpu(AFFS_TAIL(sb, bh)->link_chain)) != 0) {
		if (ino == link_ino) {
			__be32 ino2 = AFFS_TAIL(sb, link_bh)->link_chain;
			AFFS_TAIL(sb, bh)->link_chain = ino2;
			affs_adjust_checksum(bh, be32_to_cpu(ino2) - link_ino);
			mark_buffer_dirty_inode(bh, inode);
			retval = 0;
			/* Fix the link count, if bh is a normal header block without links */
			switch (be32_to_cpu(AFFS_TAIL(sb, bh)->stype)) {
			case ST_LINKDIR:
			case ST_LINKFILE:
				break;
			default:
				if (!AFFS_TAIL(sb, bh)->link_chain)
					inode->i_nlink = 1;
			}
			affs_free_block(sb, link_ino);
			goto done;
		}
		affs_brelse(bh);
		bh = affs_bread(sb, ino);
		if (!bh)
			goto done;
	}
	retval = -ENOENT;
done:
	affs_brelse(link_bh);
	affs_brelse(bh);
	return retval;
}