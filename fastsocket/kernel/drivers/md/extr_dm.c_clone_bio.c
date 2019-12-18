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
struct bio_set {int dummy; } ;
struct bio {unsigned short bi_idx; unsigned short bi_vcnt; scalar_t__ bi_size; int bi_flags; int /*<<< orphan*/  bi_sector; int /*<<< orphan*/  bi_destructor; int /*<<< orphan*/  bi_max_vecs; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int BIO_SEG_VALID ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  __bio_clone (struct bio*,struct bio*) ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio_set*) ; 
 scalar_t__ bio_integrity (struct bio*) ; 
 int /*<<< orphan*/  bio_integrity_clone (struct bio*,struct bio*,int /*<<< orphan*/ ,struct bio_set*) ; 
 int /*<<< orphan*/  bio_integrity_trim (struct bio*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bio_sector_offset (struct bio*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bio_destructor ; 
 scalar_t__ to_bytes (unsigned int) ; 

__attribute__((used)) static struct bio *clone_bio(struct bio *bio, sector_t sector,
			     unsigned short idx, unsigned short bv_count,
			     unsigned int len, struct bio_set *bs)
{
	struct bio *clone;

	clone = bio_alloc_bioset(GFP_NOIO, bio->bi_max_vecs, bs);
	__bio_clone(clone, bio);
	clone->bi_destructor = dm_bio_destructor;
	clone->bi_sector = sector;
	clone->bi_idx = idx;
	clone->bi_vcnt = idx + bv_count;
	clone->bi_size = to_bytes(len);
	clone->bi_flags &= ~(1 << BIO_SEG_VALID);

	if (bio_integrity(bio)) {
		bio_integrity_clone(clone, bio, GFP_NOIO, bs);

		if (idx != bio->bi_idx || clone->bi_size < bio->bi_size)
			bio_integrity_trim(clone,
					   bio_sector_offset(bio, idx, 0), len);
	}

	return clone;
}