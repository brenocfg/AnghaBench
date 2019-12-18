#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;
typedef  scalar_t__ u16 ;
struct super_block {unsigned long s_blocksize; unsigned char s_blocksize_bits; } ;
struct page {unsigned long index; int /*<<< orphan*/ * b_data; int /*<<< orphan*/  b_end_io; struct address_space* mapping; } ;
struct buffer_head {unsigned long index; int /*<<< orphan*/ * b_data; int /*<<< orphan*/  b_end_io; struct address_space* mapping; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  unsigned long s64 ;
struct TYPE_14__ {unsigned long vcn; scalar_t__ length; } ;
typedef  TYPE_4__ runlist_element ;
struct TYPE_15__ {unsigned long cluster_size_bits; unsigned char cluster_size; struct super_block* sb; } ;
typedef  TYPE_5__ ntfs_volume ;
struct TYPE_13__ {int /*<<< orphan*/  lock; TYPE_4__* rl; } ;
struct TYPE_11__ {unsigned long block_size; unsigned long block_size_bits; unsigned int block_clusters; } ;
struct TYPE_12__ {TYPE_1__ compressed; } ;
struct TYPE_16__ {scalar_t__ type; int name_len; unsigned long initialized_size; TYPE_3__ runlist; int /*<<< orphan*/  mft_no; TYPE_2__ itype; int /*<<< orphan*/  size_lock; TYPE_5__* vol; } ;
typedef  TYPE_6__ ntfs_inode ;
typedef  int loff_t ;
typedef  unsigned long VCN ;
typedef  unsigned char LCN ;

/* Variables and functions */
 scalar_t__ AT_DATA ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int EIO ; 
 int ENOMEM ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned char LCN_HOLE ; 
 unsigned char LCN_RL_NOT_MAPPED ; 
 TYPE_6__* NTFS_I (int /*<<< orphan*/ ) ; 
 int PAGE_CACHE_MASK ; 
 unsigned long PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  VFS_I (TYPE_6__*) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  blk_run_address_space (struct address_space*) ; 
 int /*<<< orphan*/  brelse (struct page*) ; 
 int buffer_uptodate (struct page*) ; 
 int /*<<< orphan*/  clear_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  get_bh (struct page*) ; 
 struct page* grab_cache_page_nowait (struct address_space*,unsigned long) ; 
 int /*<<< orphan*/  handle_bounds_compressed_page (struct page*,int,unsigned long) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 scalar_t__ likely (unsigned char) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ntfs_cb_lock ; 
 int /*<<< orphan*/ * ntfs_compression_buffer ; 
 int /*<<< orphan*/  ntfs_debug (char*,...) ; 
 int ntfs_decompress (struct page**,unsigned int*,unsigned int*,int,unsigned int,unsigned int,unsigned char*,int /*<<< orphan*/ *,unsigned long,int,unsigned long) ; 
 int /*<<< orphan*/  ntfs_error (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  ntfs_map_runlist (TYPE_6__*,unsigned long) ; 
 unsigned char ntfs_rl_vcn_to_lcn (TYPE_4__*,unsigned long) ; 
 int /*<<< orphan*/  ntfs_warning (struct super_block*,char*) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  put_bh (struct page*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct page* sb_getblk (struct super_block*,int) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  trylock_buffer (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_buffer (struct page*) ; 
 int /*<<< orphan*/  zero_user (struct page*,int /*<<< orphan*/ ,int) ; 

int ntfs_read_compressed_block(struct page *page)
{
	loff_t i_size;
	s64 initialized_size;
	struct address_space *mapping = page->mapping;
	ntfs_inode *ni = NTFS_I(mapping->host);
	ntfs_volume *vol = ni->vol;
	struct super_block *sb = vol->sb;
	runlist_element *rl;
	unsigned long flags, block_size = sb->s_blocksize;
	unsigned char block_size_bits = sb->s_blocksize_bits;
	u8 *cb, *cb_pos, *cb_end;
	struct buffer_head **bhs;
	unsigned long offset, index = page->index;
	u32 cb_size = ni->itype.compressed.block_size;
	u64 cb_size_mask = cb_size - 1UL;
	VCN vcn;
	LCN lcn;
	/* The first wanted vcn (minimum alignment is PAGE_CACHE_SIZE). */
	VCN start_vcn = (((s64)index << PAGE_CACHE_SHIFT) & ~cb_size_mask) >>
			vol->cluster_size_bits;
	/*
	 * The first vcn after the last wanted vcn (minumum alignment is again
	 * PAGE_CACHE_SIZE.
	 */
	VCN end_vcn = ((((s64)(index + 1UL) << PAGE_CACHE_SHIFT) + cb_size - 1)
			& ~cb_size_mask) >> vol->cluster_size_bits;
	/* Number of compression blocks (cbs) in the wanted vcn range. */
	unsigned int nr_cbs = (end_vcn - start_vcn) << vol->cluster_size_bits
			>> ni->itype.compressed.block_size_bits;
	/*
	 * Number of pages required to store the uncompressed data from all
	 * compression blocks (cbs) overlapping @page. Due to alignment
	 * guarantees of start_vcn and end_vcn, no need to round up here.
	 */
	unsigned int nr_pages = (end_vcn - start_vcn) <<
			vol->cluster_size_bits >> PAGE_CACHE_SHIFT;
	unsigned int xpage, max_page, cur_page, cur_ofs, i;
	unsigned int cb_clusters, cb_max_ofs;
	int block, max_block, cb_max_page, bhs_size, nr_bhs, err = 0;
	struct page **pages;
	unsigned char xpage_done = 0;

	ntfs_debug("Entering, page->index = 0x%lx, cb_size = 0x%x, nr_pages = "
			"%i.", index, cb_size, nr_pages);
	/*
	 * Bad things happen if we get here for anything that is not an
	 * unnamed $DATA attribute.
	 */
	BUG_ON(ni->type != AT_DATA);
	BUG_ON(ni->name_len);

	pages = kmalloc(nr_pages * sizeof(struct page *), GFP_NOFS);

	/* Allocate memory to store the buffer heads we need. */
	bhs_size = cb_size / block_size * sizeof(struct buffer_head *);
	bhs = kmalloc(bhs_size, GFP_NOFS);

	if (unlikely(!pages || !bhs)) {
		kfree(bhs);
		kfree(pages);
		unlock_page(page);
		ntfs_error(vol->sb, "Failed to allocate internal buffers.");
		return -ENOMEM;
	}

	/*
	 * We have already been given one page, this is the one we must do.
	 * Once again, the alignment guarantees keep it simple.
	 */
	offset = start_vcn << vol->cluster_size_bits >> PAGE_CACHE_SHIFT;
	xpage = index - offset;
	pages[xpage] = page;
	/*
	 * The remaining pages need to be allocated and inserted into the page
	 * cache, alignment guarantees keep all the below much simpler. (-8
	 */
	read_lock_irqsave(&ni->size_lock, flags);
	i_size = i_size_read(VFS_I(ni));
	initialized_size = ni->initialized_size;
	read_unlock_irqrestore(&ni->size_lock, flags);
	max_page = ((i_size + PAGE_CACHE_SIZE - 1) >> PAGE_CACHE_SHIFT) -
			offset;
	/* Is the page fully outside i_size? (truncate in progress) */
	if (xpage >= max_page) {
		kfree(bhs);
		kfree(pages);
		zero_user(page, 0, PAGE_CACHE_SIZE);
		ntfs_debug("Compressed read outside i_size - truncated?");
		SetPageUptodate(page);
		unlock_page(page);
		return 0;
	}
	if (nr_pages < max_page)
		max_page = nr_pages;
	for (i = 0; i < max_page; i++, offset++) {
		if (i != xpage)
			pages[i] = grab_cache_page_nowait(mapping, offset);
		page = pages[i];
		if (page) {
			/*
			 * We only (re)read the page if it isn't already read
			 * in and/or dirty or we would be losing data or at
			 * least wasting our time.
			 */
			if (!PageDirty(page) && (!PageUptodate(page) ||
					PageError(page))) {
				ClearPageError(page);
				kmap(page);
				continue;
			}
			unlock_page(page);
			page_cache_release(page);
			pages[i] = NULL;
		}
	}

	/*
	 * We have the runlist, and all the destination pages we need to fill.
	 * Now read the first compression block.
	 */
	cur_page = 0;
	cur_ofs = 0;
	cb_clusters = ni->itype.compressed.block_clusters;
do_next_cb:
	nr_cbs--;
	nr_bhs = 0;

	/* Read all cb buffer heads one cluster at a time. */
	rl = NULL;
	for (vcn = start_vcn, start_vcn += cb_clusters; vcn < start_vcn;
			vcn++) {
		bool is_retry = false;

		if (!rl) {
lock_retry_remap:
			down_read(&ni->runlist.lock);
			rl = ni->runlist.rl;
		}
		if (likely(rl != NULL)) {
			/* Seek to element containing target vcn. */
			while (rl->length && rl[1].vcn <= vcn)
				rl++;
			lcn = ntfs_rl_vcn_to_lcn(rl, vcn);
		} else
			lcn = LCN_RL_NOT_MAPPED;
		ntfs_debug("Reading vcn = 0x%llx, lcn = 0x%llx.",
				(unsigned long long)vcn,
				(unsigned long long)lcn);
		if (lcn < 0) {
			/*
			 * When we reach the first sparse cluster we have
			 * finished with the cb.
			 */
			if (lcn == LCN_HOLE)
				break;
			if (is_retry || lcn != LCN_RL_NOT_MAPPED)
				goto rl_err;
			is_retry = true;
			/*
			 * Attempt to map runlist, dropping lock for the
			 * duration.
			 */
			up_read(&ni->runlist.lock);
			if (!ntfs_map_runlist(ni, vcn))
				goto lock_retry_remap;
			goto map_rl_err;
		}
		block = lcn << vol->cluster_size_bits >> block_size_bits;
		/* Read the lcn from device in chunks of block_size bytes. */
		max_block = block + (vol->cluster_size >> block_size_bits);
		do {
			ntfs_debug("block = 0x%x.", block);
			if (unlikely(!(bhs[nr_bhs] = sb_getblk(sb, block))))
				goto getblk_err;
			nr_bhs++;
		} while (++block < max_block);
	}

	/* Release the lock if we took it. */
	if (rl)
		up_read(&ni->runlist.lock);

	/* Setup and initiate io on all buffer heads. */
	for (i = 0; i < nr_bhs; i++) {
		struct buffer_head *tbh = bhs[i];

		if (!trylock_buffer(tbh))
			continue;
		if (unlikely(buffer_uptodate(tbh))) {
			unlock_buffer(tbh);
			continue;
		}
		get_bh(tbh);
		tbh->b_end_io = end_buffer_read_sync;
		submit_bh(READ, tbh);
	}

	/* Wait for io completion on all buffer heads. */
	for (i = 0; i < nr_bhs; i++) {
		struct buffer_head *tbh = bhs[i];

		if (buffer_uptodate(tbh))
			continue;
		wait_on_buffer(tbh);
		/*
		 * We need an optimization barrier here, otherwise we start
		 * hitting the below fixup code when accessing a loopback
		 * mounted ntfs partition. This indicates either there is a
		 * race condition in the loop driver or, more likely, gcc
		 * overoptimises the code without the barrier and it doesn't
		 * do the Right Thing(TM).
		 */
		barrier();
		if (unlikely(!buffer_uptodate(tbh))) {
			ntfs_warning(vol->sb, "Buffer is unlocked but not "
					"uptodate! Unplugging the disk queue "
					"and rescheduling.");
			get_bh(tbh);
			blk_run_address_space(mapping);
			schedule();
			put_bh(tbh);
			if (unlikely(!buffer_uptodate(tbh)))
				goto read_err;
			ntfs_warning(vol->sb, "Buffer is now uptodate. Good.");
		}
	}

	/*
	 * Get the compression buffer. We must not sleep any more
	 * until we are finished with it.
	 */
	spin_lock(&ntfs_cb_lock);
	cb = ntfs_compression_buffer;

	BUG_ON(!cb);

	cb_pos = cb;
	cb_end = cb + cb_size;

	/* Copy the buffer heads into the contiguous buffer. */
	for (i = 0; i < nr_bhs; i++) {
		memcpy(cb_pos, bhs[i]->b_data, block_size);
		cb_pos += block_size;
	}

	/* Just a precaution. */
	if (cb_pos + 2 <= cb + cb_size)
		*(u16*)cb_pos = 0;

	/* Reset cb_pos back to the beginning. */
	cb_pos = cb;

	/* We now have both source (if present) and destination. */
	ntfs_debug("Successfully read the compression block.");

	/* The last page and maximum offset within it for the current cb. */
	cb_max_page = (cur_page << PAGE_CACHE_SHIFT) + cur_ofs + cb_size;
	cb_max_ofs = cb_max_page & ~PAGE_CACHE_MASK;
	cb_max_page >>= PAGE_CACHE_SHIFT;

	/* Catch end of file inside a compression block. */
	if (cb_max_page > max_page)
		cb_max_page = max_page;

	if (vcn == start_vcn - cb_clusters) {
		/* Sparse cb, zero out page range overlapping the cb. */
		ntfs_debug("Found sparse compression block.");
		/* We can sleep from now on, so we drop lock. */
		spin_unlock(&ntfs_cb_lock);
		if (cb_max_ofs)
			cb_max_page--;
		for (; cur_page < cb_max_page; cur_page++) {
			page = pages[cur_page];
			if (page) {
				/*
				 * FIXME: Using clear_page() will become wrong
				 * when we get PAGE_CACHE_SIZE != PAGE_SIZE but
				 * for now there is no problem.
				 */
				if (likely(!cur_ofs))
					clear_page(page_address(page));
				else
					memset(page_address(page) + cur_ofs, 0,
							PAGE_CACHE_SIZE -
							cur_ofs);
				flush_dcache_page(page);
				kunmap(page);
				SetPageUptodate(page);
				unlock_page(page);
				if (cur_page == xpage)
					xpage_done = 1;
				else
					page_cache_release(page);
				pages[cur_page] = NULL;
			}
			cb_pos += PAGE_CACHE_SIZE - cur_ofs;
			cur_ofs = 0;
			if (cb_pos >= cb_end)
				break;
		}
		/* If we have a partial final page, deal with it now. */
		if (cb_max_ofs && cb_pos < cb_end) {
			page = pages[cur_page];
			if (page)
				memset(page_address(page) + cur_ofs, 0,
						cb_max_ofs - cur_ofs);
			/*
			 * No need to update cb_pos at this stage:
			 *	cb_pos += cb_max_ofs - cur_ofs;
			 */
			cur_ofs = cb_max_ofs;
		}
	} else if (vcn == start_vcn) {
		/* We can't sleep so we need two stages. */
		unsigned int cur2_page = cur_page;
		unsigned int cur_ofs2 = cur_ofs;
		u8 *cb_pos2 = cb_pos;

		ntfs_debug("Found uncompressed compression block.");
		/* Uncompressed cb, copy it to the destination pages. */
		/*
		 * TODO: As a big optimization, we could detect this case
		 * before we read all the pages and use block_read_full_page()
		 * on all full pages instead (we still have to treat partial
		 * pages especially but at least we are getting rid of the
		 * synchronous io for the majority of pages.
		 * Or if we choose not to do the read-ahead/-behind stuff, we
		 * could just return block_read_full_page(pages[xpage]) as long
		 * as PAGE_CACHE_SIZE <= cb_size.
		 */
		if (cb_max_ofs)
			cb_max_page--;
		/* First stage: copy data into destination pages. */
		for (; cur_page < cb_max_page; cur_page++) {
			page = pages[cur_page];
			if (page)
				memcpy(page_address(page) + cur_ofs, cb_pos,
						PAGE_CACHE_SIZE - cur_ofs);
			cb_pos += PAGE_CACHE_SIZE - cur_ofs;
			cur_ofs = 0;
			if (cb_pos >= cb_end)
				break;
		}
		/* If we have a partial final page, deal with it now. */
		if (cb_max_ofs && cb_pos < cb_end) {
			page = pages[cur_page];
			if (page)
				memcpy(page_address(page) + cur_ofs, cb_pos,
						cb_max_ofs - cur_ofs);
			cb_pos += cb_max_ofs - cur_ofs;
			cur_ofs = cb_max_ofs;
		}
		/* We can sleep from now on, so drop lock. */
		spin_unlock(&ntfs_cb_lock);
		/* Second stage: finalize pages. */
		for (; cur2_page < cb_max_page; cur2_page++) {
			page = pages[cur2_page];
			if (page) {
				/*
				 * If we are outside the initialized size, zero
				 * the out of bounds page range.
				 */
				handle_bounds_compressed_page(page, i_size,
						initialized_size);
				flush_dcache_page(page);
				kunmap(page);
				SetPageUptodate(page);
				unlock_page(page);
				if (cur2_page == xpage)
					xpage_done = 1;
				else
					page_cache_release(page);
				pages[cur2_page] = NULL;
			}
			cb_pos2 += PAGE_CACHE_SIZE - cur_ofs2;
			cur_ofs2 = 0;
			if (cb_pos2 >= cb_end)
				break;
		}
	} else {
		/* Compressed cb, decompress it into the destination page(s). */
		unsigned int prev_cur_page = cur_page;

		ntfs_debug("Found compressed compression block.");
		err = ntfs_decompress(pages, &cur_page, &cur_ofs,
				cb_max_page, cb_max_ofs, xpage, &xpage_done,
				cb_pos,	cb_size - (cb_pos - cb), i_size,
				initialized_size);
		/*
		 * We can sleep from now on, lock already dropped by
		 * ntfs_decompress().
		 */
		if (err) {
			ntfs_error(vol->sb, "ntfs_decompress() failed in inode "
					"0x%lx with error code %i. Skipping "
					"this compression block.",
					ni->mft_no, -err);
			/* Release the unfinished pages. */
			for (; prev_cur_page < cur_page; prev_cur_page++) {
				page = pages[prev_cur_page];
				if (page) {
					flush_dcache_page(page);
					kunmap(page);
					unlock_page(page);
					if (prev_cur_page != xpage)
						page_cache_release(page);
					pages[prev_cur_page] = NULL;
				}
			}
		}
	}

	/* Release the buffer heads. */
	for (i = 0; i < nr_bhs; i++)
		brelse(bhs[i]);

	/* Do we have more work to do? */
	if (nr_cbs)
		goto do_next_cb;

	/* We no longer need the list of buffer heads. */
	kfree(bhs);

	/* Clean up if we have any pages left. Should never happen. */
	for (cur_page = 0; cur_page < max_page; cur_page++) {
		page = pages[cur_page];
		if (page) {
			ntfs_error(vol->sb, "Still have pages left! "
					"Terminating them with extreme "
					"prejudice.  Inode 0x%lx, page index "
					"0x%lx.", ni->mft_no, page->index);
			flush_dcache_page(page);
			kunmap(page);
			unlock_page(page);
			if (cur_page != xpage)
				page_cache_release(page);
			pages[cur_page] = NULL;
		}
	}

	/* We no longer need the list of pages. */
	kfree(pages);

	/* If we have completed the requested page, we return success. */
	if (likely(xpage_done))
		return 0;

	ntfs_debug("Failed. Returning error code %s.", err == -EOVERFLOW ?
			"EOVERFLOW" : (!err ? "EIO" : "unkown error"));
	return err < 0 ? err : -EIO;

read_err:
	ntfs_error(vol->sb, "IO error while reading compressed data.");
	/* Release the buffer heads. */
	for (i = 0; i < nr_bhs; i++)
		brelse(bhs[i]);
	goto err_out;

map_rl_err:
	ntfs_error(vol->sb, "ntfs_map_runlist() failed. Cannot read "
			"compression block.");
	goto err_out;

rl_err:
	up_read(&ni->runlist.lock);
	ntfs_error(vol->sb, "ntfs_rl_vcn_to_lcn() failed. Cannot read "
			"compression block.");
	goto err_out;

getblk_err:
	up_read(&ni->runlist.lock);
	ntfs_error(vol->sb, "getblk() failed. Cannot read compression block.");

err_out:
	kfree(bhs);
	for (i = cur_page; i < max_page; i++) {
		page = pages[i];
		if (page) {
			flush_dcache_page(page);
			kunmap(page);
			unlock_page(page);
			if (i != xpage)
				page_cache_release(page);
		}
	}
	kfree(pages);
	return -EIO;
}