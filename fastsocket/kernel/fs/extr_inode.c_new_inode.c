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
struct inode {unsigned int i_ino; scalar_t__ i_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __inode_add_to_lists (struct super_block*,int /*<<< orphan*/ *,struct inode*) ; 
 struct inode* alloc_inode (struct super_block*) ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct inode *new_inode(struct super_block *sb)
{
	/*
	 * On a 32bit, non LFS stat() call, glibc will generate an EOVERFLOW
	 * error if st_ino won't fit in target struct field. Use 32bit counter
	 * here to attempt to avoid that.
	 */
	static unsigned int last_ino;
	struct inode *inode;

	spin_lock_prefetch(&inode_lock);

	inode = alloc_inode(sb);
	if (inode) {
		spin_lock(&inode_lock);
		__inode_add_to_lists(sb, NULL, inode);
		inode->i_ino = ++last_ino;
		inode->i_state = 0;
		spin_unlock(&inode_lock);
	}
	return inode;
}