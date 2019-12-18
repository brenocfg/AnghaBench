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
struct enic {int /*<<< orphan*/  devcmd_lock; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
#define  VNIC_DEV_INTR_MODE_INTX 129 
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int enic_legacy_notify_intr () ; 
 int enic_msix_notify_intr (struct enic*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int vnic_dev_notify_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int enic_dev_notify_set(struct enic *enic)
{
	int err;

	spin_lock(&enic->devcmd_lock);
	switch (vnic_dev_get_intr_mode(enic->vdev)) {
	case VNIC_DEV_INTR_MODE_INTX:
		err = vnic_dev_notify_set(enic->vdev,
			enic_legacy_notify_intr());
		break;
	case VNIC_DEV_INTR_MODE_MSIX:
		err = vnic_dev_notify_set(enic->vdev,
			enic_msix_notify_intr(enic));
		break;
	default:
		err = vnic_dev_notify_set(enic->vdev, -1 /* no intr */);
		break;
	}
	spin_unlock(&enic->devcmd_lock);

	return err;
}