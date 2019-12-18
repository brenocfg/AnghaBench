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
struct thin_c {TYPE_1__* pool_dev; struct pool* pool; } ;
struct pool {int sectors_per_block_shift; int sectors_per_block; } ;
struct bio {int bi_sector; int /*<<< orphan*/  bi_bdev; } ;
typedef  int sector_t ;
typedef  int dm_block_t ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 scalar_t__ block_size_is_power_of_two (struct pool*) ; 
 int sector_div (int,int) ; 

__attribute__((used)) static void remap(struct thin_c *tc, struct bio *bio, dm_block_t block)
{
	struct pool *pool = tc->pool;
	sector_t bi_sector = bio->bi_sector;

	bio->bi_bdev = tc->pool_dev->bdev;
	if (block_size_is_power_of_two(pool))
		bio->bi_sector = (block << pool->sectors_per_block_shift) |
				(bi_sector & (pool->sectors_per_block - 1));
	else
		bio->bi_sector = (block * pool->sectors_per_block) +
				 sector_div(bi_sector, pool->sectors_per_block);
}