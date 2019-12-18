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
struct dio {TYPE_1__* inode; } ;
struct buffer_head {unsigned int b_size; scalar_t__ b_blocknr; int /*<<< orphan*/  b_bdev; } ;
struct TYPE_2__ {unsigned int i_blkbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  unmap_underlying_metadata (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void clean_blockdev_aliases(struct dio *dio, struct buffer_head *map_bh)
{
	unsigned i;
	unsigned nblocks;

	nblocks = map_bh->b_size >> dio->inode->i_blkbits;

	for (i = 0; i < nblocks; i++) {
		unmap_underlying_metadata(map_bh->b_bdev,
					  map_bh->b_blocknr + i);
	}
}