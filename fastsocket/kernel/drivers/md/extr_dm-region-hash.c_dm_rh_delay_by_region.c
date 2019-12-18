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
struct dm_region_hash {int /*<<< orphan*/  hash_lock; } ;
struct dm_region {int /*<<< orphan*/  delayed_bios; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */
 struct dm_region* __rh_find (struct dm_region_hash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

void dm_rh_delay_by_region(struct dm_region_hash *rh,
			   struct bio *bio, region_t region)
{
	struct dm_region *reg;

	/* FIXME: locking. */
	read_lock(&rh->hash_lock);
	reg = __rh_find(rh, region);
	bio_list_add(&reg->delayed_bios, bio);
	read_unlock(&rh->hash_lock);
}