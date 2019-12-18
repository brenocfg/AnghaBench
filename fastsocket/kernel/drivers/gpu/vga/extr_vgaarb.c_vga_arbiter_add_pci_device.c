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
typedef  int u16 ;
struct vga_device {int decodes; int owns; int locks; int /*<<< orphan*/  list; struct pci_dev* pdev; } ;
struct pci_dev {int class; struct pci_bus* bus; } ;
struct pci_bus {struct pci_bus* parent; struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int PCI_BRIDGE_CTL_VGA ; 
 int PCI_CLASS_DISPLAY_VGA ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MEMORY ; 
 int VGA_RSRC_LEGACY_IO ; 
 int VGA_RSRC_LEGACY_MASK ; 
 int VGA_RSRC_LEGACY_MEM ; 
 int VGA_RSRC_NORMAL_IO ; 
 int VGA_RSRC_NORMAL_MEM ; 
 int /*<<< orphan*/  kfree (struct vga_device*) ; 
 struct vga_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct vga_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vga_arbiter_check_bridge_sharing (struct vga_device*) ; 
 int /*<<< orphan*/  vga_count ; 
 int /*<<< orphan*/  vga_decode_count ; 
 int /*<<< orphan*/ * vga_default ; 
 int /*<<< orphan*/  vga_iostate_to_str (int) ; 
 int /*<<< orphan*/  vga_list ; 
 int /*<<< orphan*/  vga_lock ; 
 int /*<<< orphan*/ * vgadev_find (struct pci_dev*) ; 

__attribute__((used)) static bool vga_arbiter_add_pci_device(struct pci_dev *pdev)
{
	struct vga_device *vgadev;
	unsigned long flags;
	struct pci_bus *bus;
	struct pci_dev *bridge;
	u16 cmd;

	/* Only deal with VGA class devices */
	if ((pdev->class >> 8) != PCI_CLASS_DISPLAY_VGA)
		return false;

	/* Allocate structure */
	vgadev = kmalloc(sizeof(struct vga_device), GFP_KERNEL);
	if (vgadev == NULL) {
		pr_err("vgaarb: failed to allocate pci device\n");
		/* What to do on allocation failure ? For now, let's
		 * just do nothing, I'm not sure there is anything saner
		 * to be done
		 */
		return false;
	}

	memset(vgadev, 0, sizeof(*vgadev));

	/* Take lock & check for duplicates */
	spin_lock_irqsave(&vga_lock, flags);
	if (vgadev_find(pdev) != NULL) {
		BUG_ON(1);
		goto fail;
	}
	vgadev->pdev = pdev;

	/* By default, assume we decode everything */
	vgadev->decodes = VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM |
			  VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;

	/* by default mark it as decoding */
	vga_decode_count++;
	/* Mark that we "own" resources based on our enables, we will
	 * clear that below if the bridge isn't forwarding
	 */
	pci_read_config_word(pdev, PCI_COMMAND, &cmd);
	if (cmd & PCI_COMMAND_IO)
		vgadev->owns |= VGA_RSRC_LEGACY_IO;
	if (cmd & PCI_COMMAND_MEMORY)
		vgadev->owns |= VGA_RSRC_LEGACY_MEM;

	/* Check if VGA cycles can get down to us */
	bus = pdev->bus;
	while (bus) {
		bridge = bus->self;
		if (bridge) {
			u16 l;
			pci_read_config_word(bridge, PCI_BRIDGE_CONTROL,
					     &l);
			if (!(l & PCI_BRIDGE_CTL_VGA)) {
				vgadev->owns = 0;
				break;
			}
		}
		bus = bus->parent;
	}

	/* Deal with VGA default device. Use first enabled one
	 * by default if arch doesn't have it's own hook
	 */
#ifndef __ARCH_HAS_VGA_DEFAULT_DEVICE
	if (vga_default == NULL &&
	    ((vgadev->owns & VGA_RSRC_LEGACY_MASK) == VGA_RSRC_LEGACY_MASK))
		vga_default = pci_dev_get(pdev);
#endif

	vga_arbiter_check_bridge_sharing(vgadev);

	/* Add to the list */
	list_add(&vgadev->list, &vga_list);
	vga_count++;
	pr_info("vgaarb: device added: PCI:%s,decodes=%s,owns=%s,locks=%s\n",
		pci_name(pdev),
		vga_iostate_to_str(vgadev->decodes),
		vga_iostate_to_str(vgadev->owns),
		vga_iostate_to_str(vgadev->locks));

	spin_unlock_irqrestore(&vga_lock, flags);
	return true;
fail:
	spin_unlock_irqrestore(&vga_lock, flags);
	kfree(vgadev);
	return false;
}