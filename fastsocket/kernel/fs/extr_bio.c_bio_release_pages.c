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
struct bio_vec {struct page* bv_page; } ;
struct bio {int bi_vcnt; struct bio_vec* bi_io_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static void bio_release_pages(struct bio *bio)
{
	struct bio_vec *bvec = bio->bi_io_vec;
	int i;

	for (i = 0; i < bio->bi_vcnt; i++) {
		struct page *page = bvec[i].bv_page;

		if (page)
			put_page(page);
	}
}