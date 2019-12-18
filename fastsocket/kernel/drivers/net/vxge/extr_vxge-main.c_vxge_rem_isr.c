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
struct TYPE_3__ {scalar_t__ intr_type; } ;
struct vxgedev {TYPE_2__* pdev; TYPE_1__ config; } ;
struct __vxge_hw_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ INTA ; 
 scalar_t__ MSI_X ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vxgedev*) ; 
 scalar_t__ pci_get_drvdata (TYPE_2__*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_rem_msix_isr (struct vxgedev*) ; 

__attribute__((used)) static void vxge_rem_isr(struct vxgedev *vdev)
{
	struct __vxge_hw_device  *hldev;
	hldev = (struct __vxge_hw_device  *) pci_get_drvdata(vdev->pdev);

#ifdef CONFIG_PCI_MSI
	if (vdev->config.intr_type == MSI_X) {
		vxge_rem_msix_isr(vdev);
	} else
#endif
	if (vdev->config.intr_type == INTA) {
			synchronize_irq(vdev->pdev->irq);
			free_irq(vdev->pdev->irq, vdev);
	}
}