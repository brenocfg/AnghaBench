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
struct virtio_pci_device {scalar_t__ ioaddr; } ;
struct virtio_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_PCI_STATUS ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 
 struct virtio_pci_device* to_vp_device (struct virtio_device*) ; 

__attribute__((used)) static u8 vp_get_status(struct virtio_device *vdev)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);
	return ioread8(vp_dev->ioaddr + VIRTIO_PCI_STATUS);
}