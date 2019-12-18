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
struct udf_inode_info {scalar_t__ i_next_alloc_block; int /*<<< orphan*/  i_next_alloc_goal; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 struct buffer_head* inode_getblk (struct inode*,scalar_t__,int*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 scalar_t__ udf_block_map (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int udf_get_block(struct inode *inode, sector_t block,
			 struct buffer_head *bh_result, int create)
{
	int err, new;
	struct buffer_head *bh;
	sector_t phys = 0;
	struct udf_inode_info *iinfo;

	if (!create) {
		phys = udf_block_map(inode, block);
		if (phys)
			map_bh(bh_result, inode->i_sb, phys);
		return 0;
	}

	err = -EIO;
	new = 0;
	bh = NULL;

	lock_kernel();

	iinfo = UDF_I(inode);
	if (block == iinfo->i_next_alloc_block + 1) {
		iinfo->i_next_alloc_block++;
		iinfo->i_next_alloc_goal++;
	}

	err = 0;

	bh = inode_getblk(inode, block, &err, &phys, &new);
	BUG_ON(bh);
	if (err)
		goto abort;
	BUG_ON(!phys);

	if (new)
		set_buffer_new(bh_result);
	map_bh(bh_result, inode->i_sb, phys);

abort:
	unlock_kernel();
	return err;
}