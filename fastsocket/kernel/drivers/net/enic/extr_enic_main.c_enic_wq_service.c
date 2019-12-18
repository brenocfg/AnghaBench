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
struct enic {int /*<<< orphan*/ * wq_lock; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * wq; } ;
struct cq_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENIC_DESC_MAX_SPLITS ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  enic_wq_free_buf ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct enic* vnic_dev_priv (struct vnic_dev*) ; 
 scalar_t__ vnic_wq_desc_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_wq_service (int /*<<< orphan*/ *,struct cq_desc*,size_t,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int enic_wq_service(struct vnic_dev *vdev, struct cq_desc *cq_desc,
	u8 type, u16 q_number, u16 completed_index, void *opaque)
{
	struct enic *enic = vnic_dev_priv(vdev);

	spin_lock(&enic->wq_lock[q_number]);

	vnic_wq_service(&enic->wq[q_number], cq_desc,
		completed_index, enic_wq_free_buf,
		opaque);

	if (netif_queue_stopped(enic->netdev) &&
	    vnic_wq_desc_avail(&enic->wq[q_number]) >=
	    (MAX_SKB_FRAGS + ENIC_DESC_MAX_SPLITS))
		netif_wake_queue(enic->netdev);

	spin_unlock(&enic->wq_lock[q_number]);

	return 0;
}