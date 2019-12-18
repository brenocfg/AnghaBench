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
struct TYPE_2__ {int /*<<< orphan*/  invalid_io; } ;
struct zram {int /*<<< orphan*/  init_lock; TYPE_1__ stats; int /*<<< orphan*/  init_done; } ;
struct request_queue {struct zram* queuedata; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __zram_make_request (struct zram*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valid_io_request (struct zram*,struct bio*) ; 
 scalar_t__ zram_init_device (struct zram*) ; 
 int /*<<< orphan*/  zram_stat64_inc (struct zram*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zram_make_request(struct request_queue *queue, struct bio *bio)
{
	struct zram *zram = queue->queuedata;

	if (unlikely(!zram->init_done) && zram_init_device(zram))
		goto error;

	down_read(&zram->init_lock);
	if (unlikely(!zram->init_done))
		goto error_unlock;

	if (!valid_io_request(zram, bio)) {
		zram_stat64_inc(zram, &zram->stats.invalid_io);
		goto error_unlock;
	}

	__zram_make_request(zram, bio, bio_data_dir(bio));
	up_read(&zram->init_lock);

	return 0;

error_unlock:
	up_read(&zram->init_lock);
error:
	bio_io_error(bio);
	return 0;
}