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
struct inode {int dummy; } ;

/* Variables and functions */
 int ext4_journal_blocks_per_page (struct inode*) ; 
 int ext4_meta_trans_blocks (struct inode*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 

int ext4_writepage_trans_blocks(struct inode *inode)
{
	int bpp = ext4_journal_blocks_per_page(inode);
	int ret;

	ret = ext4_meta_trans_blocks(inode, bpp, 0);

	/* Account for data blocks for journalled mode */
	if (ext4_should_journal_data(inode))
		ret += bpp;
	return ret;
}