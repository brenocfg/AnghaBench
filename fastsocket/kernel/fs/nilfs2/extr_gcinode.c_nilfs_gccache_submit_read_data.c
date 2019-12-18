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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct buffer_head {int /*<<< orphan*/  b_page; scalar_t__ b_blocknr; int /*<<< orphan*/  b_end_io; int /*<<< orphan*/  b_bdev; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  ns_bdev; struct inode* ns_dat; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* NILFS_I_NILFS (struct inode*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int nilfs_dat_translate (struct inode*,scalar_t__,scalar_t__*) ; 
 struct buffer_head* nilfs_grab_buffer (struct inode*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

int nilfs_gccache_submit_read_data(struct inode *inode, sector_t blkoff,
				   sector_t pbn, __u64 vbn,
				   struct buffer_head **out_bh)
{
	struct buffer_head *bh;
	int err;

	bh = nilfs_grab_buffer(inode, inode->i_mapping, blkoff, 0);
	if (unlikely(!bh))
		return -ENOMEM;

	if (buffer_uptodate(bh))
		goto out;

	if (pbn == 0) {
		struct inode *dat_inode = NILFS_I_NILFS(inode)->ns_dat;
					  /* use original dat, not gc dat. */
		err = nilfs_dat_translate(dat_inode, vbn, &pbn);
		if (unlikely(err)) { /* -EIO, -ENOMEM, -ENOENT */
			brelse(bh);
			goto failed;
		}
	}

	lock_buffer(bh);
	if (buffer_uptodate(bh)) {
		unlock_buffer(bh);
		goto out;
	}

	if (!buffer_mapped(bh)) {
		bh->b_bdev = NILFS_I_NILFS(inode)->ns_bdev;
		set_buffer_mapped(bh);
	}
	bh->b_blocknr = pbn;
	bh->b_end_io = end_buffer_read_sync;
	get_bh(bh);
	submit_bh(READ, bh);
	if (vbn)
		bh->b_blocknr = vbn;
 out:
	err = 0;
	*out_bh = bh;

 failed:
	unlock_page(bh->b_page);
	page_cache_release(bh->b_page);
	return err;
}