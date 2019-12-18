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
struct inode {int i_state; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int I_LOCK ; 
 int I_NEW ; 
 int /*<<< orphan*/  __iget (struct inode*) ; 
 int /*<<< orphan*/  __inode_add_to_lists (struct super_block*,struct hlist_head*,struct inode*) ; 
 struct inode* alloc_inode (struct super_block*) ; 
 int /*<<< orphan*/  destroy_inode (struct inode*) ; 
 struct inode* find_inode (struct super_block*,struct hlist_head*,int (*) (struct inode*,void*),void*) ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_inode (struct inode*) ; 

__attribute__((used)) static struct inode *get_new_inode(struct super_block *sb,
				struct hlist_head *head,
				int (*test)(struct inode *, void *),
				int (*set)(struct inode *, void *),
				void *data)
{
	struct inode *inode;

	inode = alloc_inode(sb);
	if (inode) {
		struct inode *old;

		spin_lock(&inode_lock);
		/* We released the lock, so.. */
		old = find_inode(sb, head, test, data);
		if (!old) {
			if (set(inode, data))
				goto set_failed;

			__inode_add_to_lists(sb, head, inode);
			inode->i_state = I_LOCK|I_NEW;
			spin_unlock(&inode_lock);

			/* Return the locked inode with I_NEW set, the
			 * caller is responsible for filling in the contents
			 */
			return inode;
		}

		/*
		 * Uhhuh, somebody else created the same inode under
		 * us. Use the old inode instead of the one we just
		 * allocated.
		 */
		__iget(old);
		spin_unlock(&inode_lock);
		destroy_inode(inode);
		inode = old;
		wait_on_inode(inode);
	}
	return inode;

set_failed:
	spin_unlock(&inode_lock);
	destroy_inode(inode);
	return NULL;
}