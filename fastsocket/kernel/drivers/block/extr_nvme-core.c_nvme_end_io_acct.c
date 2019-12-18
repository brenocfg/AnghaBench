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
struct gendisk {int /*<<< orphan*/  part0; } ;
struct bio {TYPE_1__* bi_bdev; } ;
struct TYPE_2__ {struct gendisk* bd_disk; } ;

/* Variables and functions */
 int bio_data_dir (struct bio*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  part_dec_in_flight (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  part_round_stats (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  part_stat_add (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int /*<<< orphan*/ * ticks ; 

__attribute__((used)) static void nvme_end_io_acct(struct bio *bio, unsigned long start_time)
{
	struct gendisk *disk = bio->bi_bdev->bd_disk;
	const int rw = bio_data_dir(bio);
	unsigned long duration = jiffies - start_time;
	int cpu = part_stat_lock();
	part_stat_add(cpu, &disk->part0, ticks[rw], duration);
	part_round_stats(cpu, &disk->part0);
	part_dec_in_flight(&disk->part0, rw);
	part_stat_unlock();
}