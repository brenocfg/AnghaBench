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
struct mddev {int /*<<< orphan*/  bio_set; } ;
struct bio {int /*<<< orphan*/  bi_destructor; int /*<<< orphan*/  bi_max_vecs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  __bio_clone (struct bio*,struct bio*) ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio* bio_clone (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_integrity (struct bio*) ; 
 int bio_integrity_clone (struct bio*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  mddev_bio_destructor ; 

struct bio *bio_clone_mddev(struct bio *bio, gfp_t gfp_mask,
			    struct mddev *mddev)
{
	struct bio *b;
	struct mddev **mddevp;

	if (!mddev || !mddev->bio_set)
		return bio_clone(bio, gfp_mask);

	b = bio_alloc_bioset(gfp_mask, bio->bi_max_vecs,
			     mddev->bio_set);
	if (!b)
		return NULL;
	mddevp = (void*)b;
	mddevp[-1] = mddev;
	b->bi_destructor = mddev_bio_destructor;
	__bio_clone(b, bio);
	if (bio_integrity(bio)) {
		int ret;

		ret = bio_integrity_clone(b, bio, gfp_mask, mddev->bio_set);

		if (ret < 0) {
			bio_put(b);
			return NULL;
		}
	}

	return b;
}