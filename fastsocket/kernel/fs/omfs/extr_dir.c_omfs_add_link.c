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
struct omfs_inode {void* i_parent; void* i_sibling; scalar_t__ i_name; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {char* name; int len; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_parent; } ;
struct buffer_head {int /*<<< orphan*/ * b_data; } ;
typedef  void* __be64 ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int ENOMEM ; 
 scalar_t__ OMFS_NAMELEN ; 
 int /*<<< orphan*/  OMFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (void*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clus_to_blk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct buffer_head* omfs_get_bucket (struct inode*,char const*,int,int*) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omfs_add_link(struct dentry *dentry, struct inode *inode)
{
	struct inode *dir = dentry->d_parent->d_inode;
	const char *name = dentry->d_name.name;
	int namelen = dentry->d_name.len;
	struct omfs_inode *oi;
	struct buffer_head *bh;
	u64 block;
	__be64 *entry;
	int ofs;

	/* just prepend to head of queue in proper bucket */
	bh = omfs_get_bucket(dir, name, namelen, &ofs);
	if (!bh)
		goto out;

	entry = (__be64 *) &bh->b_data[ofs];
	block = be64_to_cpu(*entry);
	*entry = cpu_to_be64(inode->i_ino);
	mark_buffer_dirty(bh);
	brelse(bh);

	/* now set the sibling and parent pointers on the new inode */
	bh = sb_bread(dir->i_sb, clus_to_blk(OMFS_SB(dir->i_sb), inode->i_ino));
	if (!bh)
		goto out;

	oi = (struct omfs_inode *) bh->b_data;
	memcpy(oi->i_name, name, namelen);
	memset(oi->i_name + namelen, 0, OMFS_NAMELEN - namelen);
	oi->i_sibling = cpu_to_be64(block);
	oi->i_parent = cpu_to_be64(dir->i_ino);
	mark_buffer_dirty(bh);
	brelse(bh);

	dir->i_ctime = CURRENT_TIME_SEC;

	/* mark affected inodes dirty to rebuild checksums */
	mark_inode_dirty(dir);
	mark_inode_dirty(inode);
	return 0;
out:
	return -ENOMEM;
}