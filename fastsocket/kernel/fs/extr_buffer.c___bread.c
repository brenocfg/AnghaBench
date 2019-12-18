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
 struct buffer_head* __bread_slow (struct buffer_head*) ; 
 struct buffer_head* __getblk (struct block_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ likely (struct buffer_head*) ; 

struct buffer_head *
__bread(struct block_device *bdev, sector_t block, unsigned size)
{
	struct buffer_head *bh = __getblk(bdev, block, size);

	if (likely(bh) && !buffer_uptodate(bh))
		bh = __bread_slow(bh);
	return bh;
}