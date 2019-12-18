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
struct page {int dummy; } ;
struct bio {TYPE_1__* bi_io_vec; struct bio* bi_private; } ;
struct TYPE_2__ {struct page* bv_page; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PageError (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_locked (struct page*) ; 

__attribute__((used)) static int wait_on_bio_chain(struct bio **bio_chain)
{
	struct bio *bio;
	struct bio *next_bio;
	int ret = 0;

	if (bio_chain == NULL)
		return 0;

	bio = *bio_chain;
	if (bio == NULL)
		return 0;
	while (bio) {
		struct page *page;

		next_bio = bio->bi_private;
		page = bio->bi_io_vec[0].bv_page;
		wait_on_page_locked(page);
		if (!PageUptodate(page) || PageError(page))
			ret = -EIO;
		put_page(page);
		bio_put(bio);
		bio = next_bio;
	}
	*bio_chain = NULL;
	return ret;
}