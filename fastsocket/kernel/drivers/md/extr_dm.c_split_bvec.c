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
struct bio_vec {unsigned int bv_offset; int /*<<< orphan*/  bv_len; } ;
struct bio_set {int dummy; } ;
struct bio {int bi_vcnt; int bi_flags; int /*<<< orphan*/  bi_size; struct bio_vec* bi_io_vec; int /*<<< orphan*/  bi_rw; int /*<<< orphan*/  bi_bdev; int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_destructor; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int BIO_CLONED ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int,struct bio_set*) ; 
 scalar_t__ bio_integrity (struct bio*) ; 
 int /*<<< orphan*/  bio_integrity_clone (struct bio*,struct bio*,int /*<<< orphan*/ ,struct bio_set*) ; 
 int /*<<< orphan*/  bio_integrity_trim (struct bio*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bio_sector_offset (struct bio*,unsigned short,unsigned int) ; 
 int /*<<< orphan*/  dm_bio_destructor ; 
 int /*<<< orphan*/  to_bytes (unsigned int) ; 

__attribute__((used)) static struct bio *split_bvec(struct bio *bio, sector_t sector,
			      unsigned short idx, unsigned int offset,
			      unsigned int len, struct bio_set *bs)
{
	struct bio *clone;
	struct bio_vec *bv = bio->bi_io_vec + idx;

	clone = bio_alloc_bioset(GFP_NOIO, 1, bs);
	clone->bi_destructor = dm_bio_destructor;
	*clone->bi_io_vec = *bv;

	clone->bi_sector = sector;
	clone->bi_bdev = bio->bi_bdev;
	clone->bi_rw = bio->bi_rw;
	clone->bi_vcnt = 1;
	clone->bi_size = to_bytes(len);
	clone->bi_io_vec->bv_offset = offset;
	clone->bi_io_vec->bv_len = clone->bi_size;
	clone->bi_flags |= 1 << BIO_CLONED;

	if (bio_integrity(bio)) {
		bio_integrity_clone(clone, bio, GFP_NOIO, bs);
		bio_integrity_trim(clone,
				   bio_sector_offset(bio, idx, offset), len);
	}

	return clone;
}