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
struct inode {int /*<<< orphan*/  i_hash; int /*<<< orphan*/  i_sb; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int hash (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 struct hlist_head* inode_hashtable ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __insert_inode_hash(struct inode *inode, unsigned long hashval)
{
	struct hlist_head *head = inode_hashtable + hash(inode->i_sb, hashval);
	spin_lock(&inode_lock);
	hlist_add_head(&inode->i_hash, head);
	spin_unlock(&inode_lock);
}