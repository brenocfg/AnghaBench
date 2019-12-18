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
typedef  union map_info {int dummy; } map_info ;
struct dm_target {struct dm_dev* private; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;
struct bio {int bi_rw; int /*<<< orphan*/  bi_bdev; } ;

/* Variables and functions */
 int BIO_FLUSH ; 
 int DM_MAPIO_REMAPPED ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_rw (struct bio*) ; 
 int do_origin (struct dm_dev*,struct bio*) ; 

__attribute__((used)) static int origin_map(struct dm_target *ti, struct bio *bio,
		      union map_info *map_context)
{
	struct dm_dev *dev = ti->private;
	bio->bi_bdev = dev->bdev;

	if (bio->bi_rw & BIO_FLUSH)
		return DM_MAPIO_REMAPPED;

	/* Only tell snapshots if this is a write */
	return (bio_rw(bio) == WRITE) ? do_origin(dev, bio) : DM_MAPIO_REMAPPED;
}