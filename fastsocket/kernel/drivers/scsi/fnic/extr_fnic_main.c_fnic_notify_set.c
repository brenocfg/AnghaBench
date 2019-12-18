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
struct fnic {int /*<<< orphan*/  vdev; TYPE_1__* lport; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FNIC_INTX_NOTIFY ; 
 int FNIC_MSIX_ERR_NOTIFY ; 
 int /*<<< orphan*/  KERN_ERR ; 
#define  VNIC_DEV_INTR_MODE_INTX 130 
#define  VNIC_DEV_INTR_MODE_MSI 129 
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 
 int vnic_dev_notify_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fnic_notify_set(struct fnic *fnic)
{
	int err;

	switch (vnic_dev_get_intr_mode(fnic->vdev)) {
	case VNIC_DEV_INTR_MODE_INTX:
		err = vnic_dev_notify_set(fnic->vdev, FNIC_INTX_NOTIFY);
		break;
	case VNIC_DEV_INTR_MODE_MSI:
		err = vnic_dev_notify_set(fnic->vdev, -1);
		break;
	case VNIC_DEV_INTR_MODE_MSIX:
		err = vnic_dev_notify_set(fnic->vdev, FNIC_MSIX_ERR_NOTIFY);
		break;
	default:
		shost_printk(KERN_ERR, fnic->lport->host,
			     "Interrupt mode should be set up"
			     " before devcmd notify set %d\n",
			     vnic_dev_get_intr_mode(fnic->vdev));
		err = -1;
		break;
	}

	return err;
}