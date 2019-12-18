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
struct page {int dummy; } ;
struct dio {int io_error; scalar_t__ rw; scalar_t__ is_async; } ;
struct bio_vec {struct page* bv_page; } ;
struct bio {int bi_vcnt; struct bio_vec* bi_io_vec; int /*<<< orphan*/  bi_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int EIO ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  bio_check_pages_dirty (struct bio*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dio_bio_complete(struct dio *dio, struct bio *bio)
{
	const int uptodate = test_bit(BIO_UPTODATE, &bio->bi_flags);
	struct bio_vec *bvec = bio->bi_io_vec;
	int page_no;

	if (!uptodate)
		dio->io_error = -EIO;

	if (dio->is_async && dio->rw == READ) {
		bio_check_pages_dirty(bio);	/* transfers ownership */
	} else {
		for (page_no = 0; page_no < bio->bi_vcnt; page_no++) {
			struct page *page = bvec[page_no].bv_page;

			if (dio->rw == READ && !PageCompound(page))
				set_page_dirty_lock(page);
			page_cache_release(page);
		}
		bio_put(bio);
	}
	return uptodate ? 0 : -EIO;
}