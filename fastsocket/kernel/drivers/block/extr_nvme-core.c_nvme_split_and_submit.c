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
struct nvme_queue {int /*<<< orphan*/  sq_cong; int /*<<< orphan*/  sq_cong_wait; int /*<<< orphan*/  sq_full; } ;
struct nvme_bio_pair {int /*<<< orphan*/  b2; int /*<<< orphan*/  b1; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bio_list_empty (int /*<<< orphan*/ *) ; 
 struct nvme_bio_pair* nvme_bio_split (struct bio*,int,int,int) ; 

__attribute__((used)) static int nvme_split_and_submit(struct bio *bio, struct nvme_queue *nvmeq,
						int idx, int len, int offset)
{
	struct nvme_bio_pair *bp = nvme_bio_split(bio, idx, len, offset);
	if (!bp)
		return -ENOMEM;

	if (bio_list_empty(&nvmeq->sq_cong))
		add_wait_queue(&nvmeq->sq_full, &nvmeq->sq_cong_wait);
	bio_list_add(&nvmeq->sq_cong, &bp->b1);
	bio_list_add(&nvmeq->sq_cong, &bp->b2);

	return 0;
}