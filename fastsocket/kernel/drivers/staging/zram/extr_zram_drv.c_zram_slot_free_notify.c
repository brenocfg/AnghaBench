#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notify_free; } ;
struct zram {TYPE_2__ stats; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_3__ {struct zram* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  zram_free_page (struct zram*,unsigned long) ; 
 int /*<<< orphan*/  zram_stat64_inc (struct zram*,int /*<<< orphan*/ *) ; 

void zram_slot_free_notify(struct block_device *bdev, unsigned long index)
{
	struct zram *zram;

	zram = bdev->bd_disk->private_data;
	zram_free_page(zram, index);
	zram_stat64_inc(zram, &zram->stats.notify_free);
}