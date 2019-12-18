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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * backing_dev_info; } ;
struct inode {int i_state; int i_flags; int i_generation; int i_mode; TYPE_1__ i_data; } ;
struct fuse_inode {int /*<<< orphan*/  nlookup; } ;
struct fuse_conn {int /*<<< orphan*/  lock; int /*<<< orphan*/  bdi; } ;
struct fuse_attr {int mode; } ;

/* Variables and functions */
 int I_NEW ; 
 int S_IFMT ; 
 int S_NOATIME ; 
 int S_NOCMTIME ; 
 int /*<<< orphan*/  fuse_change_attributes (struct inode*,struct fuse_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_init_inode (struct inode*,struct fuse_attr*) ; 
 int /*<<< orphan*/  fuse_inode_eq ; 
 int /*<<< orphan*/  fuse_inode_set ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *fuse_iget(struct super_block *sb, u64 nodeid,
			int generation, struct fuse_attr *attr,
			u64 attr_valid, u64 attr_version)
{
	struct inode *inode;
	struct fuse_inode *fi;
	struct fuse_conn *fc = get_fuse_conn_super(sb);

 retry:
	inode = iget5_locked(sb, nodeid, fuse_inode_eq, fuse_inode_set, &nodeid);
	if (!inode)
		return NULL;

	if ((inode->i_state & I_NEW)) {
		inode->i_flags |= S_NOATIME|S_NOCMTIME;
		inode->i_generation = generation;
		inode->i_data.backing_dev_info = &fc->bdi;
		fuse_init_inode(inode, attr);
		unlock_new_inode(inode);
	} else if ((inode->i_mode ^ attr->mode) & S_IFMT) {
		/* Inode has changed type, any I/O on the old should fail */
		make_bad_inode(inode);
		iput(inode);
		goto retry;
	}

	fi = get_fuse_inode(inode);
	spin_lock(&fc->lock);
	fi->nlookup++;
	spin_unlock(&fc->lock);
	fuse_change_attributes(inode, attr, attr_valid, attr_version);

	return inode;
}