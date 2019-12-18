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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __inode_add_to_lists (struct super_block*,struct hlist_head*,struct inode*) ; 
 int hash (struct super_block*,int /*<<< orphan*/ ) ; 
 struct hlist_head* inode_hashtable ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void inode_add_to_lists(struct super_block *sb, struct inode *inode)
{
	struct hlist_head *head = inode_hashtable + hash(sb, inode->i_ino);

	spin_lock(&inode_lock);
	__inode_add_to_lists(sb, head, inode);
	spin_unlock(&inode_lock);
}