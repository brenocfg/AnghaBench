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
struct dm_target {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_sector; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_target_offset (struct dm_target*,int /*<<< orphan*/ ) ; 
 int thin_bio_map (struct dm_target*,struct bio*,union map_info*) ; 

__attribute__((used)) static int thin_map(struct dm_target *ti, struct bio *bio,
		    union map_info *map_context)
{
	bio->bi_sector = dm_target_offset(ti, bio->bi_sector);

	return thin_bio_map(ti, bio, map_context);
}