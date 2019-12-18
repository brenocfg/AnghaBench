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
struct buffer_head {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct buffer_head* __find_get_block_slow (struct block_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lru_install (struct buffer_head*) ; 
 struct buffer_head* lookup_bh_lru (struct block_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  touch_buffer (struct buffer_head*) ; 

struct buffer_head *
__find_get_block(struct block_device *bdev, sector_t block, unsigned size)
{
	struct buffer_head *bh = lookup_bh_lru(bdev, block, size);

	if (bh == NULL) {
		bh = __find_get_block_slow(bdev, block);
		if (bh)
			bh_lru_install(bh);
	}
	if (bh)
		touch_buffer(bh);
	return bh;
}