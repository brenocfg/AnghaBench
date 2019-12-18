#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_size; TYPE_2__* i_sb; struct address_space* i_mapping; } ;
struct gfs2_sbd {int sd_fsb2bb_shift; } ;
struct TYPE_3__ {int qb_value; void* qb_limit; void* qb_warn; } ;
struct gfs2_quota_data {TYPE_1__ qd_qb; } ;
struct gfs2_quota {int qu_value; void* qu_limit; void* qu_warn; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; struct inode i_inode; } ;
struct fs_disk_quota {int d_fieldmask; int d_blk_softlimit; int d_blk_hardlimit; int d_bcount; } ;
struct buffer_head {int /*<<< orphan*/  b_size; struct buffer_head* b_this_page; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  q ;
typedef  int loff_t ;
struct TYPE_4__ {unsigned int s_blocksize; int s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EIO ; 
 int ENOMEM ; 
 int FS_DQ_BCOUNT ; 
 int FS_DQ_BHARD ; 
 int FS_DQ_BSOFT ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  READ_META ; 
 int be64_to_cpu (int) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  create_empty_buffers (struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 struct page* find_or_create_page (struct address_space*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  gfs2_block_map (struct inode*,unsigned int,struct buffer_head*,int) ; 
 int gfs2_internal_read (struct gfs2_inode*,int /*<<< orphan*/ *,char*,int*,int) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_trans_add_data (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_unstuff_dinode (struct gfs2_inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (struct gfs2_quota*,int /*<<< orphan*/ ,int) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_adjust_quota(struct gfs2_inode *ip, loff_t loc,
			     s64 change, struct gfs2_quota_data *qd,
			     struct fs_disk_quota *fdq)
{
	struct inode *inode = &ip->i_inode;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct address_space *mapping = inode->i_mapping;
	unsigned long index = loc >> PAGE_CACHE_SHIFT;
	unsigned offset = loc & (PAGE_CACHE_SIZE - 1);
	unsigned blocksize, iblock, pos;
	struct buffer_head *bh;
	struct page *page;
	void *kaddr, *ptr;
	struct gfs2_quota q, *qp;
	int err, nbytes;
	u64 size;

	if (gfs2_is_stuffed(ip)) {
		err = gfs2_unstuff_dinode(ip, NULL);
		if (err)
			return err;
	}

	memset(&q, 0, sizeof(struct gfs2_quota));
	err = gfs2_internal_read(ip, NULL, (char *)&q, &loc, sizeof(q));
	if (err < 0)
		return err;

	err = -EIO;
	qp = &q;
	qp->qu_value = be64_to_cpu(qp->qu_value);
	qp->qu_value += change;
	qp->qu_value = cpu_to_be64(qp->qu_value);
	qd->qd_qb.qb_value = qp->qu_value;
	if (fdq) {
		if (fdq->d_fieldmask & FS_DQ_BSOFT) {
			qp->qu_warn = cpu_to_be64(fdq->d_blk_softlimit >> sdp->sd_fsb2bb_shift);
			qd->qd_qb.qb_warn = qp->qu_warn;
		}
		if (fdq->d_fieldmask & FS_DQ_BHARD) {
			qp->qu_limit = cpu_to_be64(fdq->d_blk_hardlimit >> sdp->sd_fsb2bb_shift);
			qd->qd_qb.qb_limit = qp->qu_limit;
		}
		if (fdq->d_fieldmask & FS_DQ_BCOUNT) {
			qp->qu_value = cpu_to_be64(fdq->d_bcount >> sdp->sd_fsb2bb_shift);
			qd->qd_qb.qb_value = qp->qu_value;
		}
	}

	/* Write the quota into the quota file on disk */
	ptr = qp;
	nbytes = sizeof(struct gfs2_quota);
get_a_page:
	page = find_or_create_page(mapping, index, GFP_NOFS);
	if (!page)
		return -ENOMEM;

	blocksize = inode->i_sb->s_blocksize;
	iblock = index << (PAGE_CACHE_SHIFT - inode->i_sb->s_blocksize_bits);

	if (!page_has_buffers(page))
		create_empty_buffers(page, blocksize, 0);

	bh = page_buffers(page);
	pos = blocksize;
	while (offset >= pos) {
		bh = bh->b_this_page;
		iblock++;
		pos += blocksize;
	}

	if (!buffer_mapped(bh)) {
		gfs2_block_map(inode, iblock, bh, 1);
		if (!buffer_mapped(bh))
			goto unlock_out;
		/* If it's a newly allocated disk block for quota, zero it */
		if (buffer_new(bh))
			zero_user(page, pos - blocksize, bh->b_size);
	}

	if (PageUptodate(page))
		set_buffer_uptodate(bh);

	if (!buffer_uptodate(bh)) {
		ll_rw_block(READ_META, 1, &bh);
		wait_on_buffer(bh);
		if (!buffer_uptodate(bh))
			goto unlock_out;
	}

	gfs2_trans_add_data(ip->i_gl, bh);

	kaddr = kmap_atomic(page, KM_USER0);
	if (offset + sizeof(struct gfs2_quota) > PAGE_CACHE_SIZE)
		nbytes = PAGE_CACHE_SIZE - offset;
	memcpy(kaddr + offset, ptr, nbytes);
	flush_dcache_page(page);
	kunmap_atomic(kaddr, KM_USER0);
	unlock_page(page);
	page_cache_release(page);

	/* If quota straddles page boundary, we need to update the rest of the
	 * quota at the beginning of the next page */
	if ((offset + sizeof(struct gfs2_quota)) > PAGE_CACHE_SIZE) {
		ptr = ptr + nbytes;
		nbytes = sizeof(struct gfs2_quota) - nbytes;
		offset = 0;
		index++;
		goto get_a_page;
	}

	size = loc + sizeof(struct gfs2_quota);
	if (size > inode->i_size)
		i_size_write(inode, size);
	inode->i_mtime = inode->i_atime = CURRENT_TIME;
	mark_inode_dirty(inode);
	return 0;

unlock_out:
	unlock_page(page);
	page_cache_release(page);
	return err;
}