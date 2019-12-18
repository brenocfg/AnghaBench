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
struct TYPE_2__ {unsigned long file_pages; scalar_t__ file; int /*<<< orphan*/ * filemap; } ;
struct bitmap {int /*<<< orphan*/  flags; int /*<<< orphan*/  mddev; int /*<<< orphan*/  pending_writes; int /*<<< orphan*/  write_wait; TYPE_1__ storage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_PAGE_DIRTY ; 
 int /*<<< orphan*/  BITMAP_PAGE_NEEDWRITE ; 
 int /*<<< orphan*/  BITMAP_PAGE_PENDING ; 
 int /*<<< orphan*/  BITMAP_STALE ; 
 int /*<<< orphan*/  BITMAP_WRITE_ERROR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_file_kick (struct bitmap*) ; 
 int /*<<< orphan*/  clear_page_attr (struct bitmap*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_super_wait (int /*<<< orphan*/ ) ; 
 int test_and_clear_page_attr (struct bitmap*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_page (struct bitmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bitmap_unplug(struct bitmap *bitmap)
{
	unsigned long i;
	int dirty, need_write;
	int wait = 0;

	if (!bitmap || !bitmap->storage.filemap ||
	    test_bit(BITMAP_STALE, &bitmap->flags))
		return;

	/* look at each page to see if there are any set bits that need to be
	 * flushed out to disk */
	for (i = 0; i < bitmap->storage.file_pages; i++) {
		if (!bitmap->storage.filemap)
			return;
		dirty = test_and_clear_page_attr(bitmap, i, BITMAP_PAGE_DIRTY);
		need_write = test_and_clear_page_attr(bitmap, i,
						      BITMAP_PAGE_NEEDWRITE);
		if (dirty || need_write) {
			clear_page_attr(bitmap, i, BITMAP_PAGE_PENDING);
			write_page(bitmap, bitmap->storage.filemap[i], 0);
		}
		if (dirty)
			wait = 1;
	}
	if (wait) { /* if any writes were performed, we need to wait on them */
		if (bitmap->storage.file)
			wait_event(bitmap->write_wait,
				   atomic_read(&bitmap->pending_writes)==0);
		else
			md_super_wait(bitmap->mddev);
	}
	if (test_bit(BITMAP_WRITE_ERROR, &bitmap->flags))
		bitmap_file_kick(bitmap);
}