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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct vnic_dev {int dummy; } ;
struct enic {int /*<<< orphan*/ * rq; } ;
struct cq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNIC_RQ_RETURN_DESC ; 
 int /*<<< orphan*/  enic_rq_indicate_buf ; 
 struct enic* vnic_dev_priv (struct vnic_dev*) ; 
 int /*<<< orphan*/  vnic_rq_service (int /*<<< orphan*/ *,struct cq_desc*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int enic_rq_service(struct vnic_dev *vdev, struct cq_desc *cq_desc,
	u8 type, u16 q_number, u16 completed_index, void *opaque)
{
	struct enic *enic = vnic_dev_priv(vdev);

	vnic_rq_service(&enic->rq[q_number], cq_desc,
		completed_index, VNIC_RQ_RETURN_DESC,
		enic_rq_indicate_buf, opaque);

	return 0;
}