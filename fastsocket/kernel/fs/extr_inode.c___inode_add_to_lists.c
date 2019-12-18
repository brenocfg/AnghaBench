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
struct super_block {int /*<<< orphan*/  s_inodes; } ;
struct inode {int /*<<< orphan*/  i_hash; int /*<<< orphan*/  i_sb_list; int /*<<< orphan*/  i_list; } ;
struct hlist_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_inodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  inode_in_use ; 
 TYPE_1__ inodes_stat ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
__inode_add_to_lists(struct super_block *sb, struct hlist_head *head,
			struct inode *inode)
{
	inodes_stat.nr_inodes++;
	list_add(&inode->i_list, &inode_in_use);
	list_add(&inode->i_sb_list, &sb->s_inodes);
	if (head)
		hlist_add_head(&inode->i_hash, head);
}