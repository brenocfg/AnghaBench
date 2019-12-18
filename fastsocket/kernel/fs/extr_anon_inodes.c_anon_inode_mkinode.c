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
struct inode {int i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_state; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_DIRTY ; 
 int S_IFREG ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  anon_aops ; 
 int /*<<< orphan*/  anon_inode_fops ; 
 TYPE_2__* anon_inode_mnt ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *anon_inode_mkinode(void)
{
	struct inode *inode = new_inode(anon_inode_mnt->mnt_sb);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	inode->i_fop = &anon_inode_fops;

	inode->i_mapping->a_ops = &anon_aops;

	/*
	 * Mark the inode dirty from the very beginning,
	 * that way it will never be moved to the dirty
	 * list because mark_inode_dirty() will think
	 * that it already _is_ on the dirty list.
	 */
	inode->i_state = I_DIRTY;
	inode->i_mode = S_IFREG | S_IRUSR | S_IWUSR;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
	return inode;
}