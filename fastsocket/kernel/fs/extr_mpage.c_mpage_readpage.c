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
struct buffer_head {scalar_t__ b_size; scalar_t__ b_state; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  get_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 struct bio* do_mpage_readpage (struct bio*,struct page*,int,int /*<<< orphan*/ *,struct buffer_head*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpage_bio_submit (int /*<<< orphan*/ ,struct bio*) ; 

int mpage_readpage(struct page *page, get_block_t get_block)
{
	struct bio *bio = NULL;
	sector_t last_block_in_bio = 0;
	struct buffer_head map_bh;
	unsigned long first_logical_block = 0;

	map_bh.b_state = 0;
	map_bh.b_size = 0;
	bio = do_mpage_readpage(bio, page, 1, &last_block_in_bio,
			&map_bh, &first_logical_block, get_block);
	if (bio)
		mpage_bio_submit(READ, bio);
	return 0;
}