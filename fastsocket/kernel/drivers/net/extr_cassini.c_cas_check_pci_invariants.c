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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; scalar_t__ revision; } ;
struct cas {int /*<<< orphan*/  cas_flags; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_FLAG_NO_HW_CSUM ; 
 int /*<<< orphan*/  CAS_FLAG_REG_PLUS ; 
 int /*<<< orphan*/  CAS_FLAG_SATURN ; 
 int /*<<< orphan*/  CAS_FLAG_TARGET_ABORT ; 
 scalar_t__ CAS_ID_REV2 ; 
 scalar_t__ CAS_ID_REVPLUS ; 
 scalar_t__ CAS_ID_REVPLUS02u ; 
 scalar_t__ PCI_DEVICE_ID_NS_SATURN ; 
 scalar_t__ PCI_DEVICE_ID_SUN_CASSINI ; 
 scalar_t__ PCI_VENDOR_ID_NS ; 
 scalar_t__ PCI_VENDOR_ID_SUN ; 

__attribute__((used)) static void cas_check_pci_invariants(struct cas *cp)
{
	struct pci_dev *pdev = cp->pdev;

	cp->cas_flags = 0;
	if ((pdev->vendor == PCI_VENDOR_ID_SUN) &&
	    (pdev->device == PCI_DEVICE_ID_SUN_CASSINI)) {
		if (pdev->revision >= CAS_ID_REVPLUS)
			cp->cas_flags |= CAS_FLAG_REG_PLUS;
		if (pdev->revision < CAS_ID_REVPLUS02u)
			cp->cas_flags |= CAS_FLAG_TARGET_ABORT;

		/* Original Cassini supports HW CSUM, but it's not
		 * enabled by default as it can trigger TX hangs.
		 */
		if (pdev->revision < CAS_ID_REV2)
			cp->cas_flags |= CAS_FLAG_NO_HW_CSUM;
	} else {
		/* Only sun has original cassini chips.  */
		cp->cas_flags |= CAS_FLAG_REG_PLUS;

		/* We use a flag because the same phy might be externally
		 * connected.
		 */
		if ((pdev->vendor == PCI_VENDOR_ID_NS) &&
		    (pdev->device == PCI_DEVICE_ID_NS_SATURN))
			cp->cas_flags |= CAS_FLAG_SATURN;
	}
}