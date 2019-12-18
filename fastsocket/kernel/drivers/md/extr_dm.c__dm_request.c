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
struct request_queue {struct mapped_device* queuedata; } ;
struct mapped_device {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  flags; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_BLOCK_IO_FOR_SUSPEND ; 
 scalar_t__ READA ; 
 int /*<<< orphan*/  __split_and_process_bio (struct mapped_device*,struct bio*) ; 
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 scalar_t__ bio_rw (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 TYPE_1__* dm_disk (struct mapped_device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ios ; 
 int /*<<< orphan*/  part_stat_add (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_stat_inc (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int part_stat_lock () ; 
 int /*<<< orphan*/  part_stat_unlock () ; 
 int /*<<< orphan*/  queue_io (struct mapped_device*,struct bio*) ; 
 int /*<<< orphan*/ * sectors ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _dm_request(struct request_queue *q, struct bio *bio)
{
	int rw = bio_data_dir(bio);
	struct mapped_device *md = q->queuedata;
	int cpu;

	down_read(&md->io_lock);

	cpu = part_stat_lock();
	part_stat_inc(cpu, &dm_disk(md)->part0, ios[rw]);
	part_stat_add(cpu, &dm_disk(md)->part0, sectors[rw], bio_sectors(bio));
	part_stat_unlock();

	/* if we're suspended, we have to queue this io for later */
	if (unlikely(test_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags))) {
		up_read(&md->io_lock);

		if (bio_rw(bio) != READA)
			queue_io(md, bio);
		else
			bio_io_error(bio);
		return 0;
	}

	__split_and_process_bio(md, bio);
	up_read(&md->io_lock);
	return 0;
}