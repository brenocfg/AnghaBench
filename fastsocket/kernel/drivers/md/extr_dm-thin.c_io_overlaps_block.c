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
struct pool {int sectors_per_block; } ;
struct bio {int bi_size; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 

__attribute__((used)) static int io_overlaps_block(struct pool *pool, struct bio *bio)
{
	return bio->bi_size == (pool->sectors_per_block << SECTOR_SHIFT);
}