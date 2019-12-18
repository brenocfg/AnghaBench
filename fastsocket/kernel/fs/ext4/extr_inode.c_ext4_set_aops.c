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
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DELALLOC ; 
#define  EXT4_INODE_JOURNAL_DATA_MODE 130 
#define  EXT4_INODE_ORDER_DATA_MODE 129 
#define  EXT4_INODE_WRITEBACK_DATA_MODE 128 
 int /*<<< orphan*/  ext4_da_aops ; 
 int ext4_inode_journal_mode (struct inode*) ; 
 int /*<<< orphan*/  ext4_journalled_aops ; 
 int /*<<< orphan*/  ext4_ordered_aops ; 
 int /*<<< orphan*/  ext4_writeback_aops ; 
 int /*<<< orphan*/  test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ext4_set_aops(struct inode *inode)
{
	switch (ext4_inode_journal_mode(inode)) {
	case EXT4_INODE_ORDER_DATA_MODE:
		if (test_opt(inode->i_sb, DELALLOC))
			inode->i_mapping->a_ops = &ext4_da_aops;
		else
			inode->i_mapping->a_ops = &ext4_ordered_aops;
		break;
	case EXT4_INODE_WRITEBACK_DATA_MODE:
		if (test_opt(inode->i_sb, DELALLOC))
			inode->i_mapping->a_ops = &ext4_da_aops;
		else
			inode->i_mapping->a_ops = &ext4_writeback_aops;
		break;
	case EXT4_INODE_JOURNAL_DATA_MODE:
		inode->i_mapping->a_ops = &ext4_journalled_aops;
		break;
	default:
		BUG();
	}
}