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
struct vnic_wq_copy {int /*<<< orphan*/ * ctrl; int /*<<< orphan*/  ring; struct vnic_dev* vdev; } ;
struct vnic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vnic_dev_free_desc_ring (struct vnic_dev*,int /*<<< orphan*/ *) ; 

void vnic_wq_copy_free(struct vnic_wq_copy *wq)
{
	struct vnic_dev *vdev;

	vdev = wq->vdev;
	vnic_dev_free_desc_ring(vdev, &wq->ring);
	wq->ctrl = NULL;
}