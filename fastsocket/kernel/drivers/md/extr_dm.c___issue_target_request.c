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
struct TYPE_5__ {unsigned int target_request_nr; } ;
struct dm_target_io {TYPE_2__ info; } ;
struct dm_target {int dummy; } ;
struct clone_info {int /*<<< orphan*/  sector; TYPE_3__* bio; TYPE_1__* md; } ;
struct bio {int /*<<< orphan*/  bi_size; int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_destructor; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_6__ {int /*<<< orphan*/  bi_max_vecs; } ;
struct TYPE_4__ {int /*<<< orphan*/  bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  __bio_clone (struct bio*,TYPE_3__*) ; 
 int /*<<< orphan*/  __map_bio (struct dm_target*,struct bio*,struct dm_target_io*) ; 
 struct dm_target_io* alloc_tio (struct clone_info*,struct dm_target*) ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bio_destructor ; 
 int /*<<< orphan*/  to_bytes (scalar_t__) ; 

__attribute__((used)) static void __issue_target_request(struct clone_info *ci, struct dm_target *ti,
				   unsigned request_nr, sector_t len)
{
	struct dm_target_io *tio = alloc_tio(ci, ti);
	struct bio *clone;

	tio->info.target_request_nr = request_nr;

	/*
	 * Discard requests require the bio's inline iovecs be initialized.
	 * ci->bio->bi_max_vecs is BIO_INLINE_VECS anyway, for both flush
	 * and discard, so no need for concern about wasted bvec allocations.
	 */
	clone = bio_alloc_bioset(GFP_NOIO, ci->bio->bi_max_vecs, ci->md->bs);
	__bio_clone(clone, ci->bio);
	clone->bi_destructor = dm_bio_destructor;
	if (len) {
		clone->bi_sector = ci->sector;
		clone->bi_size = to_bytes(len);
	}

	__map_bio(ti, clone, tio);
}