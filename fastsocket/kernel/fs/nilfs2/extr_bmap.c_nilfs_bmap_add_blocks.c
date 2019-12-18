#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nilfs_bmap {TYPE_1__* b_inode; } ;
struct TYPE_5__ {int i_blkbits; } ;

/* Variables and functions */
 scalar_t__ NILFS_MDT (TYPE_1__*) ; 
 int /*<<< orphan*/  inode_add_bytes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (TYPE_1__*) ; 

void nilfs_bmap_add_blocks(const struct nilfs_bmap *bmap, int n)
{
	inode_add_bytes(bmap->b_inode, (1 << bmap->b_inode->i_blkbits) * n);
	if (NILFS_MDT(bmap->b_inode))
		nilfs_mdt_mark_dirty(bmap->b_inode);
	else
		mark_inode_dirty(bmap->b_inode);
}