#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_blkbits; scalar_t__ i_ino; } ;
struct buffer_head {int /*<<< orphan*/  b_page; void* b_blocknr; int /*<<< orphan*/  b_end_io; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_data; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  void* __u64 ;
struct TYPE_3__ {int /*<<< orphan*/  ns_bdev; } ;

/* Variables and functions */
 int BH_NILFS_Node ; 
 int /*<<< orphan*/  BUG () ; 
 int EEXIST ; 
 int ENOMEM ; 
 struct inode* NILFS_BTNC_I (struct address_space*) ; 
 scalar_t__ NILFS_DAT_INO ; 
 TYPE_1__* NILFS_I_NILFS (struct inode*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct inode* nilfs_dat_inode (TYPE_1__*) ; 
 int nilfs_dat_translate (struct inode*,void*,scalar_t__*) ; 
 struct buffer_head* nilfs_grab_buffer (struct inode*,struct address_space*,void*,int) ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

int nilfs_btnode_submit_block(struct address_space *btnc, __u64 blocknr,
			      sector_t pblocknr, struct buffer_head **pbh,
			      int newblk)
{
	struct buffer_head *bh;
	struct inode *inode = NILFS_BTNC_I(btnc);
	int err;

	bh = nilfs_grab_buffer(inode, btnc, blocknr, 1 << BH_NILFS_Node);
	if (unlikely(!bh))
		return -ENOMEM;

	err = -EEXIST; /* internal code */
	if (newblk) {
		if (unlikely(buffer_mapped(bh) || buffer_uptodate(bh) ||
			     buffer_dirty(bh))) {
			brelse(bh);
			BUG();
		}
		memset(bh->b_data, 0, 1 << inode->i_blkbits);
		bh->b_bdev = NILFS_I_NILFS(inode)->ns_bdev;
		bh->b_blocknr = blocknr;
		set_buffer_mapped(bh);
		set_buffer_uptodate(bh);
		goto found;
	}

	if (buffer_uptodate(bh) || buffer_dirty(bh))
		goto found;

	if (pblocknr == 0) {
		pblocknr = blocknr;
		if (inode->i_ino != NILFS_DAT_INO) {
			struct inode *dat =
				nilfs_dat_inode(NILFS_I_NILFS(inode));

			/* blocknr is a virtual block number */
			err = nilfs_dat_translate(dat, blocknr, &pblocknr);
			if (unlikely(err)) {
				brelse(bh);
				goto out_locked;
			}
		}
	}
	lock_buffer(bh);
	if (buffer_uptodate(bh)) {
		unlock_buffer(bh);
		err = -EEXIST; /* internal code */
		goto found;
	}
	set_buffer_mapped(bh);
	bh->b_bdev = NILFS_I_NILFS(inode)->ns_bdev;
	bh->b_blocknr = pblocknr; /* set block address for read */
	bh->b_end_io = end_buffer_read_sync;
	get_bh(bh);
	submit_bh(READ, bh);
	bh->b_blocknr = blocknr; /* set back to the given block address */
	err = 0;
found:
	*pbh = bh;

out_locked:
	unlock_page(bh->b_page);
	page_cache_release(bh->b_page);
	return err;
}