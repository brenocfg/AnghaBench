#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext3_inode_info {int /*<<< orphan*/  i_block_group; scalar_t__* i_data; } ;
typedef  int ext3_grpblk_t ;
typedef  scalar_t__ ext3_fsblk_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_7__ {int pid; } ;
struct TYPE_6__ {TYPE_1__* bh; scalar_t__* p; } ;
struct TYPE_5__ {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
typedef  TYPE_2__ Indirect ;

/* Variables and functions */
 int EXT3_BLOCKS_PER_GROUP (int /*<<< orphan*/ ) ; 
 struct ext3_inode_info* EXT3_I (struct inode*) ; 
 TYPE_4__* current ; 
 scalar_t__ ext3_group_first_block_no (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static ext3_fsblk_t ext3_find_near(struct inode *inode, Indirect *ind)
{
	struct ext3_inode_info *ei = EXT3_I(inode);
	__le32 *start = ind->bh ? (__le32*) ind->bh->b_data : ei->i_data;
	__le32 *p;
	ext3_fsblk_t bg_start;
	ext3_grpblk_t colour;

	/* Try to find previous block */
	for (p = ind->p - 1; p >= start; p--) {
		if (*p)
			return le32_to_cpu(*p);
	}

	/* No such thing, so let's try location of indirect block */
	if (ind->bh)
		return ind->bh->b_blocknr;

	/*
	 * It is going to be referred to from the inode itself? OK, just put it
	 * into the same cylinder group then.
	 */
	bg_start = ext3_group_first_block_no(inode->i_sb, ei->i_block_group);
	colour = (current->pid % 16) *
			(EXT3_BLOCKS_PER_GROUP(inode->i_sb) / 16);
	return bg_start + colour;
}