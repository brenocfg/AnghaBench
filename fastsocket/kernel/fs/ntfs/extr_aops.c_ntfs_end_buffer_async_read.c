#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void u8 ;
typedef  unsigned int u32 ;
struct page {scalar_t__ index; TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_size; int /*<<< orphan*/  b_state; struct buffer_head* b_this_page; scalar_t__ b_blocknr; struct page* b_page; } ;
typedef  scalar_t__ s64 ;
struct TYPE_10__ {unsigned int block_size; } ;
struct TYPE_11__ {TYPE_3__ index; } ;
struct TYPE_12__ {scalar_t__ initialized_size; TYPE_4__ itype; TYPE_2__* vol; int /*<<< orphan*/  size_lock; } ;
typedef  TYPE_5__ ntfs_inode ;
typedef  scalar_t__ loff_t ;
struct TYPE_9__ {int /*<<< orphan*/  sb; } ;
struct TYPE_8__ {struct inode* host; } ;
typedef  int /*<<< orphan*/  NTFS_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  BH_Uptodate_Lock ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  KM_BIO_SRC_IRQ ; 
 int /*<<< orphan*/  NInoMstProtected (TYPE_5__*) ; 
 TYPE_5__* NTFS_I (struct inode*) ; 
 scalar_t__ PAGE_CACHE_SHIFT ; 
 unsigned int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageError (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  bit_spin_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bit_spin_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_async_read (struct buffer_head*) ; 
 int buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_async_read (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ntfs_error (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  post_read_mst_fixup (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void ntfs_end_buffer_async_read(struct buffer_head *bh, int uptodate)
{
	unsigned long flags;
	struct buffer_head *first, *tmp;
	struct page *page;
	struct inode *vi;
	ntfs_inode *ni;
	int page_uptodate = 1;

	page = bh->b_page;
	vi = page->mapping->host;
	ni = NTFS_I(vi);

	if (likely(uptodate)) {
		loff_t i_size;
		s64 file_ofs, init_size;

		set_buffer_uptodate(bh);

		file_ofs = ((s64)page->index << PAGE_CACHE_SHIFT) +
				bh_offset(bh);
		read_lock_irqsave(&ni->size_lock, flags);
		init_size = ni->initialized_size;
		i_size = i_size_read(vi);
		read_unlock_irqrestore(&ni->size_lock, flags);
		if (unlikely(init_size > i_size)) {
			/* Race with shrinking truncate. */
			init_size = i_size;
		}
		/* Check for the current buffer head overflowing. */
		if (unlikely(file_ofs + bh->b_size > init_size)) {
			int ofs;
			void *kaddr;

			ofs = 0;
			if (file_ofs < init_size)
				ofs = init_size - file_ofs;
			local_irq_save(flags);
			kaddr = kmap_atomic(page, KM_BIO_SRC_IRQ);
			memset(kaddr + bh_offset(bh) + ofs, 0,
					bh->b_size - ofs);
			flush_dcache_page(page);
			kunmap_atomic(kaddr, KM_BIO_SRC_IRQ);
			local_irq_restore(flags);
		}
	} else {
		clear_buffer_uptodate(bh);
		SetPageError(page);
		ntfs_error(ni->vol->sb, "Buffer I/O error, logical block "
				"0x%llx.", (unsigned long long)bh->b_blocknr);
	}
	first = page_buffers(page);
	local_irq_save(flags);
	bit_spin_lock(BH_Uptodate_Lock, &first->b_state);
	clear_buffer_async_read(bh);
	unlock_buffer(bh);
	tmp = bh;
	do {
		if (!buffer_uptodate(tmp))
			page_uptodate = 0;
		if (buffer_async_read(tmp)) {
			if (likely(buffer_locked(tmp)))
				goto still_busy;
			/* Async buffers must be locked. */
			BUG();
		}
		tmp = tmp->b_this_page;
	} while (tmp != bh);
	bit_spin_unlock(BH_Uptodate_Lock, &first->b_state);
	local_irq_restore(flags);
	/*
	 * If none of the buffers had errors then we can set the page uptodate,
	 * but we first have to perform the post read mst fixups, if the
	 * attribute is mst protected, i.e. if NInoMstProteced(ni) is true.
	 * Note we ignore fixup errors as those are detected when
	 * map_mft_record() is called which gives us per record granularity
	 * rather than per page granularity.
	 */
	if (!NInoMstProtected(ni)) {
		if (likely(page_uptodate && !PageError(page)))
			SetPageUptodate(page);
	} else {
		u8 *kaddr;
		unsigned int i, recs;
		u32 rec_size;

		rec_size = ni->itype.index.block_size;
		recs = PAGE_CACHE_SIZE / rec_size;
		/* Should have been verified before we got here... */
		BUG_ON(!recs);
		local_irq_save(flags);
		kaddr = kmap_atomic(page, KM_BIO_SRC_IRQ);
		for (i = 0; i < recs; i++)
			post_read_mst_fixup((NTFS_RECORD*)(kaddr +
					i * rec_size), rec_size);
		kunmap_atomic(kaddr, KM_BIO_SRC_IRQ);
		local_irq_restore(flags);
		flush_dcache_page(page);
		if (likely(page_uptodate && !PageError(page)))
			SetPageUptodate(page);
	}
	unlock_page(page);
	return;
still_busy:
	bit_spin_unlock(BH_Uptodate_Lock, &first->b_state);
	local_irq_restore(flags);
	return;
}