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
struct writeback_control {int dummy; } ;
struct mpage_data {int use_writepage; int /*<<< orphan*/ * bio; int /*<<< orphan*/  get_block; int /*<<< orphan*/  last_block_in_bio; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  get_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  __mpage_writepage ; 
 int generic_writepages (struct address_space*,struct writeback_control*) ; 
 int /*<<< orphan*/  mpage_bio_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int write_cache_pages (struct address_space*,struct writeback_control*,int /*<<< orphan*/ ,struct mpage_data*) ; 

int
mpage_writepages(struct address_space *mapping,
		struct writeback_control *wbc, get_block_t get_block)
{
	int ret;

	if (!get_block)
		ret = generic_writepages(mapping, wbc);
	else {
		struct mpage_data mpd = {
			.bio = NULL,
			.last_block_in_bio = 0,
			.get_block = get_block,
			.use_writepage = 1,
		};

		ret = write_cache_pages(mapping, wbc, __mpage_writepage, &mpd);
		if (mpd.bio)
			mpage_bio_submit(WRITE, mpd.bio);
	}
	return ret;
}