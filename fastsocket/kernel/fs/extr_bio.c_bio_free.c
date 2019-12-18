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
struct bio_set {int /*<<< orphan*/  bio_pool; scalar_t__ front_pad; } ;
struct bio {int /*<<< orphan*/  bi_io_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_POOL_IDX (struct bio*) ; 
 scalar_t__ bio_has_allocated_vec (struct bio*) ; 
 scalar_t__ bio_integrity (struct bio*) ; 
 int /*<<< orphan*/  bio_integrity_free (struct bio*,struct bio_set*) ; 
 int /*<<< orphan*/  bvec_free_bs (struct bio_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (void*,int /*<<< orphan*/ ) ; 

void bio_free(struct bio *bio, struct bio_set *bs)
{
	void *p;

	if (bio_has_allocated_vec(bio))
		bvec_free_bs(bs, bio->bi_io_vec, BIO_POOL_IDX(bio));

	if (bio_integrity(bio))
		bio_integrity_free(bio, bs);

	/*
	 * If we have front padding, adjust the bio pointer before freeing
	 */
	p = bio;
	if (bs->front_pad)
		p -= bs->front_pad;

	mempool_free(p, bs->bio_pool);
}