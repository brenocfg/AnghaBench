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
 struct inode* get_new_inode_fast (struct super_block*,struct hlist_head*,unsigned long) ; 
 int hash (struct super_block*,unsigned long) ; 
 struct inode* ifind_fast (struct super_block*,struct hlist_head*,unsigned long) ; 
 struct hlist_head* inode_hashtable ; 

struct inode *iget_locked(struct super_block *sb, unsigned long ino)
{
	struct hlist_head *head = inode_hashtable + hash(sb, ino);
	struct inode *inode;

	inode = ifind_fast(sb, head, ino);
	if (inode)
		return inode;
	/*
	 * get_new_inode_fast() will do the right thing, re-trying the search
	 * in case it had to block at any point.
	 */
	return get_new_inode_fast(sb, head, ino);
}