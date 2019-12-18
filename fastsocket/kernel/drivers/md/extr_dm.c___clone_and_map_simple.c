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
struct dm_target_io {int dummy; } ;
struct dm_target {int dummy; } ;
struct clone_info {int /*<<< orphan*/  sector_count; TYPE_1__* md; scalar_t__ idx; int /*<<< orphan*/  sector; struct bio* bio; } ;
struct bio {scalar_t__ bi_vcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __map_bio (struct dm_target*,struct bio*,struct dm_target_io*) ; 
 struct dm_target_io* alloc_tio (struct clone_info*,struct dm_target*) ; 
 struct bio* clone_bio (struct bio*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __clone_and_map_simple(struct clone_info *ci, struct dm_target *ti)
{
	struct bio *clone, *bio = ci->bio;
	struct dm_target_io *tio;

	tio = alloc_tio(ci, ti);
	clone = clone_bio(bio, ci->sector, ci->idx,
			  bio->bi_vcnt - ci->idx, ci->sector_count,
			  ci->md->bs);
	__map_bio(ti, clone, tio);
	ci->sector_count = 0;
}