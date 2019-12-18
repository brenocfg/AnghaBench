#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pohmelfs_sb {int /*<<< orphan*/  ino_lock; } ;
struct pohmelfs_inode {int /*<<< orphan*/  inode_entry; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct pohmelfs_inode* POHMELFS_I (struct inode*) ; 
 struct pohmelfs_sb* POHMELFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_drop_inode (struct inode*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pohmelfs_drop_inode(struct inode *inode)
{
	struct pohmelfs_sb *psb = POHMELFS_SB(inode->i_sb);
	struct pohmelfs_inode *pi = POHMELFS_I(inode);

	spin_lock(&psb->ino_lock);
	list_del_init(&pi->inode_entry);
	spin_unlock(&psb->ino_lock);

	generic_drop_inode(inode);
}