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
struct inode {int dummy; } ;
struct TYPE_2__ {unsigned long mi_blocks_per_group; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode const*) ; 
 unsigned long nilfs_palloc_desc_blkoff (struct inode const*,unsigned long) ; 
 unsigned long nilfs_palloc_groups_per_desc_block (struct inode const*) ; 

__attribute__((used)) static unsigned long
nilfs_palloc_bitmap_blkoff(const struct inode *inode, unsigned long group)
{
	unsigned long desc_offset =
		group % nilfs_palloc_groups_per_desc_block(inode);
	return nilfs_palloc_desc_blkoff(inode, group) + 1 +
		desc_offset * NILFS_MDT(inode)->mi_blocks_per_group;
}