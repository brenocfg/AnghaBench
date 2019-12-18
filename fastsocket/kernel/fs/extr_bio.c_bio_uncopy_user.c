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
struct bio_map_data {int /*<<< orphan*/  is_our_pages; int /*<<< orphan*/  nr_sgvecs; int /*<<< orphan*/  sgvecs; int /*<<< orphan*/  iovecs; } ;
struct bio {struct bio_map_data* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NULL_MAPPED ; 
 scalar_t__ READ ; 
 int __bio_copy_iov (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_free_map_data (struct bio_map_data*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 

int bio_uncopy_user(struct bio *bio)
{
	struct bio_map_data *bmd = bio->bi_private;
	int ret = 0;

	if (!bio_flagged(bio, BIO_NULL_MAPPED))
		ret = __bio_copy_iov(bio, bmd->iovecs, bmd->sgvecs,
				     bmd->nr_sgvecs, bio_data_dir(bio) == READ,
				     0, bmd->is_our_pages);
	bio_free_map_data(bmd);
	bio_put(bio);
	return ret;
}