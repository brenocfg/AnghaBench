#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnic_wq_copy {int /*<<< orphan*/  ring; TYPE_1__* ctrl; scalar_t__ to_clean_index; scalar_t__ to_use_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_status; int /*<<< orphan*/  posted_index; int /*<<< orphan*/  fetch_index; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_dev_clear_desc_ring (int /*<<< orphan*/ *) ; 
 scalar_t__ vnic_wq_copy_desc_in_use (struct vnic_wq_copy*) ; 
 int /*<<< orphan*/  vnic_wq_copy_service (struct vnic_wq_copy*,int,void (*) (struct vnic_wq_copy*,struct fcpio_host_req*)) ; 

void vnic_wq_copy_clean(struct vnic_wq_copy *wq,
	void (*q_clean)(struct vnic_wq_copy *wq,
	struct fcpio_host_req *wq_desc))
{
	BUG_ON(ioread32(&wq->ctrl->enable));

	if (vnic_wq_copy_desc_in_use(wq))
		vnic_wq_copy_service(wq, -1, q_clean);

	wq->to_use_index = wq->to_clean_index = 0;

	iowrite32(0, &wq->ctrl->fetch_index);
	iowrite32(0, &wq->ctrl->posted_index);
	iowrite32(0, &wq->ctrl->error_status);

	vnic_dev_clear_desc_ring(&wq->ring);
}