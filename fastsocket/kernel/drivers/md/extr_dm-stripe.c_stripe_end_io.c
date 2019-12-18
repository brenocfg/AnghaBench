#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union map_info {int dummy; } map_info ;
struct stripe_c {unsigned int stripes; int /*<<< orphan*/  kstriped_ws; TYPE_3__* stripe; } ;
struct dm_target {struct stripe_c* private; } ;
struct bio {TYPE_1__* bi_bdev; } ;
typedef  int /*<<< orphan*/  major_minor ;
struct TYPE_6__ {int /*<<< orphan*/  error_count; TYPE_2__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_RW_AHEAD ; 
 scalar_t__ DM_IO_ERROR_THRESHOLD ; 
 int EOPNOTSUPP ; 
 int EWOULDBLOCK ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_rw_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstriped ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int stripe_end_io(struct dm_target *ti, struct bio *bio,
			 int error, union map_info *map_context)
{
	unsigned i;
	char major_minor[16];
	struct stripe_c *sc = ti->private;

	if (!error)
		return 0; /* I/O complete */

	if ((error == -EWOULDBLOCK) && bio_rw_flagged(bio, BIO_RW_AHEAD))
		return error;

	if (error == -EOPNOTSUPP)
		return error;

	memset(major_minor, 0, sizeof(major_minor));
	sprintf(major_minor, "%d:%d",
		MAJOR(disk_devt(bio->bi_bdev->bd_disk)),
		MINOR(disk_devt(bio->bi_bdev->bd_disk)));

	/*
	 * Test to see which stripe drive triggered the event
	 * and increment error count for all stripes on that device.
	 * If the error count for a given device exceeds the threshold
	 * value we will no longer trigger any further events.
	 */
	for (i = 0; i < sc->stripes; i++)
		if (!strcmp(sc->stripe[i].dev->name, major_minor)) {
			atomic_inc(&(sc->stripe[i].error_count));
			if (atomic_read(&(sc->stripe[i].error_count)) <
			    DM_IO_ERROR_THRESHOLD)
				queue_work(kstriped, &sc->kstriped_ws);
		}

	return error;
}