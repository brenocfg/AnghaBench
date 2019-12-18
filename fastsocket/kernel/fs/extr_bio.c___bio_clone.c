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
struct bio_vec {int dummy; } ;
struct bio {int bi_max_vecs; int bi_flags; int /*<<< orphan*/  bi_idx; int /*<<< orphan*/  bi_size; int /*<<< orphan*/  bi_vcnt; int /*<<< orphan*/  bi_rw; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_io_vec; } ;

/* Variables and functions */
 int BIO_CLONED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void __bio_clone(struct bio *bio, struct bio *bio_src)
{
	memcpy(bio->bi_io_vec, bio_src->bi_io_vec,
		bio_src->bi_max_vecs * sizeof(struct bio_vec));

	/*
	 * most users will be overriding ->bi_bdev with a new target,
	 * so we don't set nor calculate new physical/hw segment counts here
	 */
	bio->bi_sector = bio_src->bi_sector;
	bio->bi_bdev = bio_src->bi_bdev;
	bio->bi_flags |= 1 << BIO_CLONED;
	bio->bi_rw = bio_src->bi_rw;
	bio->bi_vcnt = bio_src->bi_vcnt;
	bio->bi_size = bio_src->bi_size;
	bio->bi_idx = bio_src->bi_idx;
}