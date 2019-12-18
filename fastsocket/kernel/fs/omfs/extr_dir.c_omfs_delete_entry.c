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
typedef  int /*<<< orphan*/  u64 ;
struct omfs_inode {int /*<<< orphan*/  i_sibling; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * b_data; } ;
struct TYPE_4__ {char* name; int len; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_parent; } ;
struct buffer_head {int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  OMFS_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct inode*) ; 
 int /*<<< orphan*/  clus_to_blk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct inode* omfs_get_bucket (struct inode*,char const*,int,int*) ; 
 struct inode* omfs_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* omfs_scan_list (struct inode*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 struct inode* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omfs_delete_entry(struct dentry *dentry)
{
	struct inode *dir = dentry->d_parent->d_inode;
	struct inode *dirty;
	const char *name = dentry->d_name.name;
	int namelen = dentry->d_name.len;
	struct omfs_inode *oi;
	struct buffer_head *bh, *bh2;
	__be64 *entry, next;
	u64 block, prev;
	int ofs;
	int err = -ENOMEM;

	/* delete the proper node in the bucket's linked list */
	bh = omfs_get_bucket(dir, name, namelen, &ofs);
	if (!bh)
		goto out;

	entry = (__be64 *) &bh->b_data[ofs];
	block = be64_to_cpu(*entry);

	bh2 = omfs_scan_list(dir, block, name, namelen, &prev);
	if (IS_ERR(bh2)) {
		err = PTR_ERR(bh2);
		goto out_free_bh;
	}

	oi = (struct omfs_inode *) bh2->b_data;
	next = oi->i_sibling;
	brelse(bh2);

	if (prev != ~0) {
		/* found in middle of list, get list ptr */
		brelse(bh);
		bh = sb_bread(dir->i_sb,
			clus_to_blk(OMFS_SB(dir->i_sb), prev));
		if (!bh)
			goto out;

		oi = (struct omfs_inode *) bh->b_data;
		entry = &oi->i_sibling;
	}

	*entry = next;
	mark_buffer_dirty(bh);

	if (prev != ~0) {
		dirty = omfs_iget(dir->i_sb, prev);
		if (!IS_ERR(dirty)) {
			mark_inode_dirty(dirty);
			iput(dirty);
		}
	}

	err = 0;
out_free_bh:
	brelse(bh);
out:
	return err;
}