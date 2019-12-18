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
struct virtio_pci_device {int msix_used_vectors; TYPE_2__* msix_entries; TYPE_2__* msix_names; scalar_t__ msix_vectors; scalar_t__ msix_enabled; TYPE_1__* pci_dev; scalar_t__ ioaddr; scalar_t__ intx_enabled; } ;
struct virtio_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_MSI_CONFIG_VECTOR ; 
 int /*<<< orphan*/  VIRTIO_MSI_NO_VECTOR ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct virtio_pci_device*) ; 
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_1__*) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 

__attribute__((used)) static void vp_free_vectors(struct virtio_device *vdev)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	int i;

	if (vp_dev->intx_enabled) {
		free_irq(vp_dev->pci_dev->irq, vp_dev);
		vp_dev->intx_enabled = 0;
	}

	for (i = 0; i < vp_dev->msix_used_vectors; ++i)
		free_irq(vp_dev->msix_entries[i].vector, vp_dev);

	if (vp_dev->msix_enabled) {
		/* Disable the vector used for configuration */
		iowrite16(VIRTIO_MSI_NO_VECTOR,
			  vp_dev->ioaddr + VIRTIO_MSI_CONFIG_VECTOR);
		/* Flush the write out to device */
		ioread16(vp_dev->ioaddr + VIRTIO_MSI_CONFIG_VECTOR);

		pci_disable_msix(vp_dev->pci_dev);
		vp_dev->msix_enabled = 0;
		vp_dev->msix_vectors = 0;
	}

	vp_dev->msix_used_vectors = 0;
	kfree(vp_dev->msix_names);
	vp_dev->msix_names = NULL;
	kfree(vp_dev->msix_entries);
	vp_dev->msix_entries = NULL;
}