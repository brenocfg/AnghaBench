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
struct bio {int /*<<< orphan*/  bi_bdev; } ;

/* Variables and functions */
 int bdev_integrity_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_data_dir (struct bio*) ; 
 scalar_t__ bio_integrity (struct bio*) ; 

int bio_integrity_enabled(struct bio *bio)
{
	/* Already protected? */
	if (bio_integrity(bio))
		return 0;

	return bdev_integrity_enabled(bio->bi_bdev, bio_data_dir(bio));
}