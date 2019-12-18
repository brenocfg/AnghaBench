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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iget (struct inode*) ; 
 struct inode* find_inode_fast (struct super_block*,struct hlist_head*,unsigned long) ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_inode (struct inode*) ; 

__attribute__((used)) static struct inode *ifind_fast(struct super_block *sb,
		struct hlist_head *head, unsigned long ino)
{
	struct inode *inode;

	spin_lock(&inode_lock);
	inode = find_inode_fast(sb, head, ino);
	if (inode) {
		__iget(inode);
		spin_unlock(&inode_lock);
		wait_on_inode(inode);
		return inode;
	}
	spin_unlock(&inode_lock);
	return NULL;
}