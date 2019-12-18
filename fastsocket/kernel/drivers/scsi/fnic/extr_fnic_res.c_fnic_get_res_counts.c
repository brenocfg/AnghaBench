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
struct fnic {int /*<<< orphan*/  vdev; void* intr_count; void* cq_count; void* rq_count; void* raw_wq_count; void* wq_count; void* wq_copy_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_TYPE_CQ ; 
 int /*<<< orphan*/  RES_TYPE_INTR_CTRL ; 
 int /*<<< orphan*/  RES_TYPE_RQ ; 
 int /*<<< orphan*/  RES_TYPE_WQ ; 
 void* vnic_dev_get_res_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fnic_get_res_counts(struct fnic *fnic)
{
	fnic->wq_count = vnic_dev_get_res_count(fnic->vdev, RES_TYPE_WQ);
	fnic->raw_wq_count = fnic->wq_count - 1;
	fnic->wq_copy_count = fnic->wq_count - fnic->raw_wq_count;
	fnic->rq_count = vnic_dev_get_res_count(fnic->vdev, RES_TYPE_RQ);
	fnic->cq_count = vnic_dev_get_res_count(fnic->vdev, RES_TYPE_CQ);
	fnic->intr_count = vnic_dev_get_res_count(fnic->vdev,
		RES_TYPE_INTR_CTRL);
}