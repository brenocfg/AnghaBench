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
union map_info {unsigned int target_request_nr; } ;
typedef  size_t uint32_t ;
struct stripe_c {unsigned int stripes; TYPE_2__* stripe; } ;
struct dm_target {struct stripe_c* private; } ;
struct bio {int bi_rw; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_sector; } ;
struct TYPE_4__ {TYPE_1__* dev; scalar_t__ physical_start; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int BIO_FLUSH ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DM_MAPIO_REMAPPED ; 
 int stripe_map_discard (struct stripe_c*,struct bio*,unsigned int) ; 
 int /*<<< orphan*/  stripe_map_sector (struct stripe_c*,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int stripe_map(struct dm_target *ti, struct bio *bio,
		      union map_info *map_context)
{
	struct stripe_c *sc = ti->private;
	uint32_t stripe;
	unsigned target_request_nr;

	if (bio->bi_rw & BIO_FLUSH) {
		target_request_nr = map_context->target_request_nr;
		BUG_ON(target_request_nr >= sc->stripes);
		bio->bi_bdev = sc->stripe[target_request_nr].dev->bdev;
		return DM_MAPIO_REMAPPED;
	}
	if (unlikely(bio->bi_rw & BIO_DISCARD)) {
		target_request_nr = map_context->target_request_nr;
		BUG_ON(target_request_nr >= sc->stripes);
		return stripe_map_discard(sc, bio, target_request_nr);
	}

	stripe_map_sector(sc, bio->bi_sector, &stripe, &bio->bi_sector);

	bio->bi_sector += sc->stripe[stripe].physical_start;
	bio->bi_bdev = sc->stripe[stripe].dev->bdev;

	return DM_MAPIO_REMAPPED;
}