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
struct dio_submit {int cur_page_len; scalar_t__ cur_page_offset; int blkbits; scalar_t__ cur_page_block; scalar_t__ final_block_in_bio; int /*<<< orphan*/  cur_page; int /*<<< orphan*/  pages_in_io; int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int bio_add_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  page_cache_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dio_bio_add_page(struct dio_submit *sdio)
{
	int ret;

	ret = bio_add_page(sdio->bio, sdio->cur_page,
			sdio->cur_page_len, sdio->cur_page_offset);
	if (ret == sdio->cur_page_len) {
		/*
		 * Decrement count only, if we are done with this page
		 */
		if ((sdio->cur_page_len + sdio->cur_page_offset) == PAGE_SIZE)
			sdio->pages_in_io--;
		page_cache_get(sdio->cur_page);
		sdio->final_block_in_bio = sdio->cur_page_block +
			(sdio->cur_page_len >> sdio->blkbits);
		ret = 0;
	} else {
		ret = 1;
	}
	return ret;
}