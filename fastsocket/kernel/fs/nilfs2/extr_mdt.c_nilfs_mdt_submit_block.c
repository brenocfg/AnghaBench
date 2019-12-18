#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct buffer_head {int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_end_io; scalar_t__ b_blocknr; int /*<<< orphan*/  b_bdev; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_6__ {int /*<<< orphan*/  i_bmap; } ;
struct TYPE_5__ {TYPE_1__* mi_nilfs; } ;
struct TYPE_4__ {int /*<<< orphan*/  ns_bdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int ENOMEM ; 
 TYPE_3__* NILFS_I (struct inode*) ; 
 TYPE_2__* NILFS_MDT (struct inode*) ; 
 int READA ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int nilfs_bmap_lookup (int /*<<< orphan*/ ,unsigned long,scalar_t__*) ; 
 struct buffer_head* nilfs_grab_buffer (struct inode*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int,struct buffer_head*) ; 
 int /*<<< orphan*/  trylock_buffer (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nilfs_mdt_submit_block(struct inode *inode, unsigned long blkoff,
		       int mode, struct buffer_head **out_bh)
{
	struct buffer_head *bh;
	__u64 blknum = 0;
	int ret = -ENOMEM;

	bh = nilfs_grab_buffer(inode, inode->i_mapping, blkoff, 0);
	if (unlikely(!bh))
		goto failed;

	ret = -EEXIST; /* internal code */
	if (buffer_uptodate(bh))
		goto out;

	if (mode == READA) {
		if (!trylock_buffer(bh)) {
			ret = -EBUSY;
			goto failed_bh;
		}
	} else /* mode == READ */
		lock_buffer(bh);

	if (buffer_uptodate(bh)) {
		unlock_buffer(bh);
		goto out;
	}

	ret = nilfs_bmap_lookup(NILFS_I(inode)->i_bmap, blkoff, &blknum);
	if (unlikely(ret)) {
		unlock_buffer(bh);
		goto failed_bh;
	}
	bh->b_bdev = NILFS_MDT(inode)->mi_nilfs->ns_bdev;
	bh->b_blocknr = (sector_t)blknum;
	set_buffer_mapped(bh);

	bh->b_end_io = end_buffer_read_sync;
	get_bh(bh);
	submit_bh(mode, bh);
	ret = 0;
 out:
	get_bh(bh);
	*out_bh = bh;

 failed_bh:
	unlock_page(bh->b_page);
	page_cache_release(bh->b_page);
	brelse(bh);
 failed:
	return ret;
}