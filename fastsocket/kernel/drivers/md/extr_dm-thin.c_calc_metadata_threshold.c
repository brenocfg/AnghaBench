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
struct pool_c {TYPE_1__* metadata_dev; } ;
typedef  int dm_block_t ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int get_metadata_dev_size_in_blocks (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

__attribute__((used)) static dm_block_t calc_metadata_threshold(struct pool_c *pt)
{
	/*
	 * 4M is ample for all ops with the possible exception of thin
	 * device deletion which is harmless if it fails (just retry the
	 * delete after you've grown the device).
	 */
	dm_block_t quarter = get_metadata_dev_size_in_blocks(pt->metadata_dev->bdev) / 4;
	return min((dm_block_t)1024ULL /* 4M */, quarter);
}