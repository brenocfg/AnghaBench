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
struct vnic_dev {int dummy; } ;
struct vnic_cq {unsigned int index; int /*<<< orphan*/  ring; int /*<<< orphan*/  ctrl; struct vnic_dev* vdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RES_TYPE_CQ ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int vnic_dev_alloc_desc_ring (struct vnic_dev*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vnic_dev_get_res (struct vnic_dev*,int /*<<< orphan*/ ,unsigned int) ; 

int vnic_cq_alloc(struct vnic_dev *vdev, struct vnic_cq *cq, unsigned int index,
	unsigned int desc_count, unsigned int desc_size)
{
	int err;

	cq->index = index;
	cq->vdev = vdev;

	cq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_CQ, index);
	if (!cq->ctrl) {
		pr_err("Failed to hook CQ[%d] resource\n", index);
		return -EINVAL;
	}

	err = vnic_dev_alloc_desc_ring(vdev, &cq->ring, desc_count, desc_size);
	if (err)
		return err;

	return 0;
}