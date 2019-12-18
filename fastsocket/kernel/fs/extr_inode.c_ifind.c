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
 struct inode* find_inode (struct super_block*,struct hlist_head*,int (*) (struct inode*,void*),void*) ; 
 int /*<<< orphan*/  inode_lock ; 
 scalar_t__ likely (int const) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_inode (struct inode*) ; 

__attribute__((used)) static struct inode *ifind(struct super_block *sb,
		struct hlist_head *head, int (*test)(struct inode *, void *),
		void *data, const int wait)
{
	struct inode *inode;

	spin_lock(&inode_lock);
	inode = find_inode(sb, head, test, data);
	if (inode) {
		__iget(inode);
		spin_unlock(&inode_lock);
		if (likely(wait))
			wait_on_inode(inode);
		return inode;
	}
	spin_unlock(&inode_lock);
	return NULL;
}