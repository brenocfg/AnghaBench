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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int EIO ; 
 int NILFS_MDT_MAX_RA_BLOCKS ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  READA ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ likely (int) ; 
 int nilfs_mdt_submit_block (struct inode*,unsigned long,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static int nilfs_mdt_read_block(struct inode *inode, unsigned long block,
				struct buffer_head **out_bh)
{
	struct buffer_head *first_bh, *bh;
	unsigned long blkoff;
	int i, nr_ra_blocks = NILFS_MDT_MAX_RA_BLOCKS;
	int err;

	err = nilfs_mdt_submit_block(inode, block, READ, &first_bh);
	if (err == -EEXIST) /* internal code */
		goto out;

	if (unlikely(err))
		goto failed;

	blkoff = block + 1;
	for (i = 0; i < nr_ra_blocks; i++, blkoff++) {
		err = nilfs_mdt_submit_block(inode, blkoff, READA, &bh);
		if (likely(!err || err == -EEXIST))
			brelse(bh);
		else if (err != -EBUSY)
			break; /* abort readahead if bmap lookup failed */

		if (!buffer_locked(first_bh))
			goto out_no_wait;
	}

	wait_on_buffer(first_bh);

 out_no_wait:
	err = -EIO;
	if (!buffer_uptodate(first_bh))
		goto failed_bh;
 out:
	*out_bh = first_bh;
	return 0;

 failed_bh:
	brelse(first_bh);
 failed:
	return err;
}