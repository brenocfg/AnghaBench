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
struct nvme_bio_pair {int err; struct nvme_bio_pair* bv2; struct nvme_bio_pair* bv1; int /*<<< orphan*/  parent; int /*<<< orphan*/  cnt; } ;
struct bio {struct nvme_bio_pair* bi_private; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct nvme_bio_pair*) ; 

__attribute__((used)) static void nvme_bio_pair_endio(struct bio *bio, int err)
{
	struct nvme_bio_pair *bp = bio->bi_private;

	if (err)
		bp->err = err;

	if (atomic_dec_and_test(&bp->cnt)) {
		bio_endio(bp->parent, bp->err);
		kfree(bp->bv1);
		kfree(bp->bv2);
		kfree(bp);
	}
}