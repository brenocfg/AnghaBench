#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int encountered_congestion; scalar_t__ range_start; scalar_t__ range_end; scalar_t__ sync_mode; scalar_t__ nr_to_write; scalar_t__ range_cyclic; scalar_t__ nonblocking; } ;
struct page {scalar_t__ index; struct address_space* mapping; } ;
struct cifs_writedata {scalar_t__ sync_mode; unsigned int nr_pages; int pagesz; int /*<<< orphan*/  refcount; struct page** pages; TYPE_2__* cfile; int /*<<< orphan*/  pid; scalar_t__ tailsz; scalar_t__ bytes; scalar_t__ offset; } ;
struct cifs_sb_info {int wsize; } ;
struct backing_dev_info {int dummy; } ;
struct address_space {scalar_t__ writeback_index; TYPE_1__* host; struct backing_dev_info* backing_dev_info; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_I (TYPE_1__*) ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBADF ; 
 int ENOMEM ; 
 scalar_t__ LLONG_MAX ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 scalar_t__ PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 scalar_t__ WB_SYNC_ALL ; 
 scalar_t__ WB_SYNC_NONE ; 
 scalar_t__ bdi_write_congested (struct backing_dev_info*) ; 
 int /*<<< orphan*/  cERROR (int,char*) ; 
 int /*<<< orphan*/  cifsFileInfo_put (TYPE_2__*) ; 
 int cifs_async_writev (struct cifs_writedata*) ; 
 struct cifs_writedata* cifs_writedata_alloc (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_writedata_release ; 
 int /*<<< orphan*/  cifs_writev_complete_ops ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 unsigned int find_get_pages_tag (struct address_space*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,struct page**) ; 
 TYPE_2__* find_writable_file (int /*<<< orphan*/ ,int) ; 
 int generic_writepages (struct address_space*,struct writeback_control*) ; 
 scalar_t__ i_size_read (TYPE_1__*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mapping_set_error (struct address_space*,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static int cifs_writepages(struct address_space *mapping,
			   struct writeback_control *wbc)
{
	struct backing_dev_info *bdi = mapping->backing_dev_info;
	struct cifs_sb_info *cifs_sb = CIFS_SB(mapping->host->i_sb);
	bool done = false, scanned = false, range_whole = false;
	pgoff_t end, index;
	struct cifs_writedata *wdata;
	struct page *page;
	int rc = 0;

	/*
	 * BB: Is this meaningful for a non-block-device file system?
	 * If it is, we should test it again after we do I/O
	 */
	if (wbc->nonblocking && bdi_write_congested(bdi)) {
		wbc->encountered_congestion = 1;
		return 0;
	}

	/*
	 * If wsize is smaller than the page cache size, default to writing
	 * one page at a time via cifs_writepage
	 */
	if (cifs_sb->wsize < PAGE_CACHE_SIZE)
		return generic_writepages(mapping, wbc);

	if (wbc->range_cyclic) {
		index = mapping->writeback_index; /* Start from prev offset */
		end = -1;
	} else {
		index = wbc->range_start >> PAGE_CACHE_SHIFT;
		end = wbc->range_end >> PAGE_CACHE_SHIFT;
		if (wbc->range_start == 0 && wbc->range_end == LLONG_MAX)
			range_whole = true;
		scanned = true;
	}
retry:
	while (!done && index <= end) {
		unsigned int i, nr_pages, found_pages;
		pgoff_t next = 0, tofind;
		struct page **pages;

		tofind = min((cifs_sb->wsize / PAGE_CACHE_SIZE) - 1,
				end - index) + 1;

		wdata = cifs_writedata_alloc((unsigned int)tofind,
					     &cifs_writev_complete_ops);
		if (!wdata) {
			rc = -ENOMEM;
			break;
		}

		/*
		 * find_get_pages_tag seems to return a max of 256 on each
		 * iteration, so we must call it several times in order to
		 * fill the array or the wsize is effectively limited to
		 * 256 * PAGE_CACHE_SIZE.
		 */
		found_pages = 0;
		pages = wdata->pages;
		do {
			nr_pages = find_get_pages_tag(mapping, &index,
							PAGECACHE_TAG_DIRTY,
							tofind, pages);
			found_pages += nr_pages;
			tofind -= nr_pages;
			pages += nr_pages;
		} while (nr_pages && tofind && index <= end);

		if (found_pages == 0) {
			kref_put(&wdata->refcount, cifs_writedata_release);
			break;
		}

		nr_pages = 0;
		for (i = 0; i < found_pages; i++) {
			page = wdata->pages[i];
			/*
			 * At this point we hold neither mapping->tree_lock nor
			 * lock on the page itself: the page may be truncated or
			 * invalidated (changing page->mapping to NULL), or even
			 * swizzled back from swapper_space to tmpfs file
			 * mapping
			 */

			if (nr_pages == 0)
				lock_page(page);
			else if (!trylock_page(page))
				break;

			if (unlikely(page->mapping != mapping)) {
				unlock_page(page);
				break;
			}

			if (!wbc->range_cyclic && page->index > end) {
				done = true;
				unlock_page(page);
				break;
			}

			if (next && (page->index != next)) {
				/* Not next consecutive page */
				unlock_page(page);
				break;
			}

			if (wbc->sync_mode != WB_SYNC_NONE)
				wait_on_page_writeback(page);

			if (PageWriteback(page) ||
					!clear_page_dirty_for_io(page)) {
				unlock_page(page);
				break;
			}

			/*
			 * This actually clears the dirty bit in the radix tree.
			 * See cifs_writepage() for more commentary.
			 */
			set_page_writeback(page);

			if (page_offset(page) >= i_size_read(mapping->host)) {
				done = true;
				unlock_page(page);
				end_page_writeback(page);
				break;
			}

			wdata->pages[i] = page;
			next = page->index + 1;
			++nr_pages;
		}

		/* reset index to refind any pages skipped */
		if (nr_pages == 0)
			index = wdata->pages[0]->index + 1;

		/* put any pages we aren't going to use */
		for (i = nr_pages; i < found_pages; i++) {
			page_cache_release(wdata->pages[i]);
			wdata->pages[i] = NULL;
		}

		/* nothing to write? */
		if (nr_pages == 0) {
			kref_put(&wdata->refcount, cifs_writedata_release);
			continue;
		}

		wdata->sync_mode = wbc->sync_mode;
		wdata->nr_pages = nr_pages;
		wdata->offset = page_offset(wdata->pages[0]);
		wdata->pagesz = PAGE_CACHE_SIZE;
		wdata->tailsz =
			min(i_size_read(mapping->host) -
			    page_offset(wdata->pages[nr_pages - 1]),
			    (loff_t)PAGE_CACHE_SIZE);
		wdata->bytes = ((nr_pages - 1) * PAGE_CACHE_SIZE) +
					wdata->tailsz;

		do {
			if (wdata->cfile != NULL)
				cifsFileInfo_put(wdata->cfile);
			wdata->cfile = find_writable_file(CIFS_I(mapping->host),
							  false);
			if (!wdata->cfile) {
				cERROR(1, "No writable handles for inode");
				rc = -EBADF;
				break;
			}
			wdata->pid = wdata->cfile->pid;
			rc = cifs_async_writev(wdata);
		} while (wbc->sync_mode == WB_SYNC_ALL && rc == -EAGAIN);

		for (i = 0; i < nr_pages; ++i)
			unlock_page(wdata->pages[i]);

		/* send failure -- clean up the mess */
		if (rc != 0) {
			for (i = 0; i < nr_pages; ++i) {
				if (rc == -EAGAIN)
					redirty_page_for_writepage(wbc,
							   wdata->pages[i]);
				else
					SetPageError(wdata->pages[i]);
				end_page_writeback(wdata->pages[i]);
				page_cache_release(wdata->pages[i]);
			}
			if (rc != -EAGAIN)
				mapping_set_error(mapping, rc);
		}
		kref_put(&wdata->refcount, cifs_writedata_release);

		wbc->nr_to_write -= nr_pages;
		if (wbc->nr_to_write <= 0)
			done = true;

		index = next;
	}

	if (!scanned && !done) {
		/*
		 * We hit the last page and there is more work to be done: wrap
		 * back to the start of the file
		 */
		scanned = true;
		index = 0;
		goto retry;
	}

	if (wbc->range_cyclic || (range_whole && wbc->nr_to_write > 0))
		mapping->writeback_index = index;

	return rc;
}