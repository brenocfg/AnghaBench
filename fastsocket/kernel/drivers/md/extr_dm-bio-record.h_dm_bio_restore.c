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
struct dm_bio_details {TYPE_2__* bi_io_vec; int /*<<< orphan*/  bi_flags; int /*<<< orphan*/  bi_idx; int /*<<< orphan*/  bi_size; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_sector; } ;
struct bio {unsigned int bi_vcnt; TYPE_1__* bi_io_vec; int /*<<< orphan*/  bi_flags; int /*<<< orphan*/  bi_idx; int /*<<< orphan*/  bi_size; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_sector; } ;
struct TYPE_4__ {int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_len; } ;

/* Variables and functions */

__attribute__((used)) static inline void dm_bio_restore(struct dm_bio_details *bd, struct bio *bio)
{
	unsigned i;

	bio->bi_sector = bd->bi_sector;
	bio->bi_bdev = bd->bi_bdev;
	bio->bi_size = bd->bi_size;
	bio->bi_idx = bd->bi_idx;
	bio->bi_flags = bd->bi_flags;

	for (i = 0; i < bio->bi_vcnt; i++) {
		bio->bi_io_vec[i].bv_len = bd->bi_io_vec[i].bv_len;
		bio->bi_io_vec[i].bv_offset = bd->bi_io_vec[i].bv_offset;
	}
}