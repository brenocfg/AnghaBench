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
struct msdos_sb_info {int /*<<< orphan*/  inode_hash_lock; struct hlist_head* inode_hashtable; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct hlist_head {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_fat_hash; int /*<<< orphan*/  i_pos; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_I (struct inode*) ; 
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int fat_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fat_attach(struct inode *inode, loff_t i_pos)
{
	struct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	struct hlist_head *head = sbi->inode_hashtable + fat_hash(i_pos);

	spin_lock(&sbi->inode_hash_lock);
	MSDOS_I(inode)->i_pos = i_pos;
	hlist_add_head(&MSDOS_I(inode)->i_fat_hash, head);
	spin_unlock(&sbi->inode_hash_lock);
}