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
struct dm_region_hash {scalar_t__ target_begin; } ;
struct bio {scalar_t__ bi_sector; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */
 int /*<<< orphan*/  dm_rh_sector_to_region (struct dm_region_hash*,scalar_t__) ; 

region_t dm_rh_bio_to_region(struct dm_region_hash *rh, struct bio *bio)
{
	return dm_rh_sector_to_region(rh, bio->bi_sector - rh->target_begin);
}