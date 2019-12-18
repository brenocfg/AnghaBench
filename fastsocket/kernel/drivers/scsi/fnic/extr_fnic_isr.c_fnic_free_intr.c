#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fnic {TYPE_3__* msix; TYPE_2__* msix_entry; TYPE_1__* pdev; int /*<<< orphan*/  vdev; } ;
struct TYPE_6__ {struct fnic* devid; int /*<<< orphan*/  requested; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
#define  VNIC_DEV_INTR_MODE_INTX 130 
#define  VNIC_DEV_INTR_MODE_MSI 129 
#define  VNIC_DEV_INTR_MODE_MSIX 128 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fnic*) ; 
 int vnic_dev_get_intr_mode (int /*<<< orphan*/ ) ; 

void fnic_free_intr(struct fnic *fnic)
{
	int i;

	switch (vnic_dev_get_intr_mode(fnic->vdev)) {
	case VNIC_DEV_INTR_MODE_INTX:
	case VNIC_DEV_INTR_MODE_MSI:
		free_irq(fnic->pdev->irq, fnic);
		break;

	case VNIC_DEV_INTR_MODE_MSIX:
		for (i = 0; i < ARRAY_SIZE(fnic->msix); i++)
			if (fnic->msix[i].requested)
				free_irq(fnic->msix_entry[i].vector,
					 fnic->msix[i].devid);
		break;

	default:
		break;
	}
}