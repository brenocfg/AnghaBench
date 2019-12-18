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
struct writeback_control {scalar_t__ sync_mode; } ;
struct page {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int BIO_RW_SYNCIO ; 
 int BIO_RW_UNPLUG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  PSWPOUT ; 
 scalar_t__ WB_SYNC_ALL ; 
 int WRITE ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_swap_bio_write ; 
 struct bio* get_swap_bio (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int /*<<< orphan*/  submit_bio (int,struct bio*) ; 
 scalar_t__ try_to_free_swap (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int swap_writepage(struct page *page, struct writeback_control *wbc)
{
	struct bio *bio;
	int ret = 0, rw = WRITE;

	if (try_to_free_swap(page)) {
		unlock_page(page);
		goto out;
	}
	bio = get_swap_bio(GFP_NOIO, page, end_swap_bio_write);
	if (bio == NULL) {
		set_page_dirty(page);
		unlock_page(page);
		ret = -ENOMEM;
		goto out;
	}
	if (wbc->sync_mode == WB_SYNC_ALL)
		rw |= (1 << BIO_RW_SYNCIO) | (1 << BIO_RW_UNPLUG);
	count_vm_event(PSWPOUT);
	set_page_writeback(page);
	unlock_page(page);
	submit_bio(rw, bio);
out:
	return ret;
}