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
struct list_blocks_struct {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_bread (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int update_extent_range (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,scalar_t__,struct list_blocks_struct*) ; 

__attribute__((used)) static int update_ind_extent_range(handle_t *handle, struct inode *inode,
				   ext4_fsblk_t pblock, ext4_lblk_t *blk_nump,
				   struct list_blocks_struct *lb)
{
	struct buffer_head *bh;
	__le32 *i_data;
	int i, retval = 0;
	ext4_lblk_t blk_count = *blk_nump;
	unsigned long max_entries = inode->i_sb->s_blocksize >> 2;

	if (!pblock) {
		/* Only update the file block number */
		*blk_nump += max_entries;
		return 0;
	}

	bh = sb_bread(inode->i_sb, pblock);
	if (!bh)
		return -EIO;

	i_data = (__le32 *)bh->b_data;
	for (i = 0; i < max_entries; i++, blk_count++) {
		if (i_data[i]) {
			retval = update_extent_range(handle, inode,
						le32_to_cpu(i_data[i]),
						blk_count, lb);
			if (retval)
				break;
		}
	}

	/* Update the file block number */
	*blk_nump = blk_count;
	put_bh(bh);
	return retval;

}