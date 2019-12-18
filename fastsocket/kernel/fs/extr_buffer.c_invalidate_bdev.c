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
struct block_device {TYPE_1__* bd_inode; } ;
struct address_space {scalar_t__ nrpages; } ;
struct TYPE_2__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  invalidate_bh_lrus () ; 
 int /*<<< orphan*/  invalidate_mapping_pages (struct address_space*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lru_add_drain_all () ; 

void invalidate_bdev(struct block_device *bdev)
{
	struct address_space *mapping = bdev->bd_inode->i_mapping;

	if (mapping->nrpages == 0)
		return;

	invalidate_bh_lrus();
	lru_add_drain_all();	/* make sure all lru add caches are flushed */
	invalidate_mapping_pages(mapping, 0, -1);
}