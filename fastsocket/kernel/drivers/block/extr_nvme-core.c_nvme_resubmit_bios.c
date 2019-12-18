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
struct nvme_queue {int /*<<< orphan*/  sq_cong; int /*<<< orphan*/  sq_cong_wait; int /*<<< orphan*/  sq_full; } ;
struct nvme_ns {int dummy; } ;
struct bio {TYPE_2__* bi_bdev; } ;
struct TYPE_4__ {TYPE_1__* bd_disk; } ;
struct TYPE_3__ {struct nvme_ns* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_add_head (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ bio_list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_list_peek (int /*<<< orphan*/ *) ; 
 struct bio* bio_list_pop (int /*<<< orphan*/ *) ; 
 scalar_t__ nvme_submit_bio_queue (struct nvme_queue*,struct nvme_ns*,struct bio*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_resubmit_bios(struct nvme_queue *nvmeq)
{
	while (bio_list_peek(&nvmeq->sq_cong)) {
		struct bio *bio = bio_list_pop(&nvmeq->sq_cong);
		struct nvme_ns *ns = bio->bi_bdev->bd_disk->private_data;

		if (bio_list_empty(&nvmeq->sq_cong))
			remove_wait_queue(&nvmeq->sq_full,
							&nvmeq->sq_cong_wait);
		if (nvme_submit_bio_queue(nvmeq, ns, bio)) {
			if (bio_list_empty(&nvmeq->sq_cong))
				add_wait_queue(&nvmeq->sq_full,
							&nvmeq->sq_cong_wait);
			bio_list_add_head(&nvmeq->sq_cong, bio);
			break;
		}
	}
}