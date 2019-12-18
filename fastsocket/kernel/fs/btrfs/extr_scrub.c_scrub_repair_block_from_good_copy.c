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
struct scrub_block {int page_count; } ;

/* Variables and functions */
 int scrub_repair_page_from_good_copy (struct scrub_block*,struct scrub_block*,int,int) ; 

__attribute__((used)) static int scrub_repair_block_from_good_copy(struct scrub_block *sblock_bad,
					     struct scrub_block *sblock_good,
					     int force_write)
{
	int page_num;
	int ret = 0;

	for (page_num = 0; page_num < sblock_bad->page_count; page_num++) {
		int ret_sub;

		ret_sub = scrub_repair_page_from_good_copy(sblock_bad,
							   sblock_good,
							   page_num,
							   force_write);
		if (ret_sub)
			ret = ret_sub;
	}

	return ret;
}