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
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 struct buffer_head* __find_get_block (struct block_device*,scalar_t__,unsigned int) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 

void write_boundary_block(struct block_device *bdev,
			sector_t bblock, unsigned blocksize)
{
	struct buffer_head *bh = __find_get_block(bdev, bblock + 1, blocksize);
	if (bh) {
		if (buffer_dirty(bh))
			ll_rw_block(WRITE, 1, &bh);
		put_bh(bh);
	}
}