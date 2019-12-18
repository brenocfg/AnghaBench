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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DATA_FLAGS ; 
 int /*<<< orphan*/  DELALLOC ; 
 int /*<<< orphan*/  EXT4_INODE_JOURNAL_DATA ; 
 int EXT4_INODE_JOURNAL_DATA_MODE ; 
 int EXT4_INODE_ORDER_DATA_MODE ; 
 int EXT4_INODE_WRITEBACK_DATA_MODE ; 
 int /*<<< orphan*/ * EXT4_JOURNAL (struct inode*) ; 
 scalar_t__ EXT4_MOUNT_JOURNAL_DATA ; 
 scalar_t__ EXT4_MOUNT_ORDERED_DATA ; 
 scalar_t__ EXT4_MOUNT_WRITEBACK_DATA ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ext4_inode_journal_mode(struct inode *inode)
{
	if (EXT4_JOURNAL(inode) == NULL)
		return EXT4_INODE_WRITEBACK_DATA_MODE;	/* writeback */
	/* We do not support data journalling with delayed allocation */
	if ((!S_ISREG(inode->i_mode)) ||
	   (test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA) ||
	   (ext4_test_inode_flag(inode, EXT4_INODE_JOURNAL_DATA) &&
	   (!test_opt(inode->i_sb, DELALLOC))))
		return EXT4_INODE_JOURNAL_DATA_MODE;	/* journal data */
	if (test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_ORDERED_DATA)
		return EXT4_INODE_ORDER_DATA_MODE;		/* ordered */
	if (test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_WRITEBACK_DATA)
		return EXT4_INODE_WRITEBACK_DATA_MODE;	/* writeback */
	else
		BUG();
}