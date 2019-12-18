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
struct dm_region_hash {int dummy; } ;
struct bio_list {struct bio* head; } ;
struct bio {int bi_rw; struct bio* bi_next; } ;

/* Variables and functions */
 int BIO_DISCARD ; 
 int BIO_FLUSH ; 
 int /*<<< orphan*/  dm_rh_bio_to_region (struct dm_region_hash*,struct bio*) ; 
 int /*<<< orphan*/  dm_rh_inc (struct dm_region_hash*,int /*<<< orphan*/ ) ; 

void dm_rh_inc_pending(struct dm_region_hash *rh, struct bio_list *bios)
{
	struct bio *bio;

	for (bio = bios->head; bio; bio = bio->bi_next) {
		if (bio->bi_rw & (BIO_FLUSH | BIO_DISCARD))
			continue;
		dm_rh_inc(rh, dm_rh_bio_to_region(rh, bio));
	}
}