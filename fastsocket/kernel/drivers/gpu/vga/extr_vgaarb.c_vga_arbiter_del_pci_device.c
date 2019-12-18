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
struct vga_device {int decodes; int /*<<< orphan*/  list; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int VGA_RSRC_LEGACY_IO ; 
 int VGA_RSRC_LEGACY_MEM ; 
 int /*<<< orphan*/  kfree (struct vga_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vga_arb_device_card_gone (struct pci_dev*) ; 
 int /*<<< orphan*/  vga_count ; 
 int /*<<< orphan*/  vga_decode_count ; 
 struct pci_dev* vga_default ; 
 int /*<<< orphan*/  vga_lock ; 
 int /*<<< orphan*/  vga_wait_queue ; 
 struct vga_device* vgadev_find (struct pci_dev*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vga_arbiter_del_pci_device(struct pci_dev *pdev)
{
	struct vga_device *vgadev;
	unsigned long flags;
	bool ret = true;

	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	if (vgadev == NULL) {
		ret = false;
		goto bail;
	}

#ifndef __ARCH_HAS_VGA_DEFAULT_DEVICE
	if (vga_default == pdev) {
		pci_dev_put(vga_default);
		vga_default = NULL;
	}
#endif

	if (vgadev->decodes & (VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM))
		vga_decode_count--;

	/* Remove entry from list */
	list_del(&vgadev->list);
	vga_count--;
	/* Notify userland driver that the device is gone so it discards
	 * it's copies of the pci_dev pointer
	 */
	vga_arb_device_card_gone(pdev);

	/* Wake up all possible waiters */
	wake_up_all(&vga_wait_queue);
bail:
	spin_unlock_irqrestore(&vga_lock, flags);
	kfree(vgadev);
	return ret;
}