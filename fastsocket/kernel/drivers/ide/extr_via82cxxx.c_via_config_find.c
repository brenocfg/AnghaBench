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
struct via_isa_bridge {int flags; scalar_t__ rev_min; scalar_t__ rev_max; scalar_t__ id; } ;
struct pci_dev {scalar_t__ revision; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_VIA ; 
 int VIA_BAD_ID ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 struct via_isa_bridge* via_isa_bridges ; 

__attribute__((used)) static struct via_isa_bridge *via_config_find(struct pci_dev **isa)
{
	struct via_isa_bridge *via_config;

	for (via_config = via_isa_bridges; via_config->id; via_config++)
		if ((*isa = pci_get_device(PCI_VENDOR_ID_VIA +
			!!(via_config->flags & VIA_BAD_ID),
			via_config->id, NULL))) {

			if ((*isa)->revision >= via_config->rev_min &&
			    (*isa)->revision <= via_config->rev_max)
				break;
			pci_dev_put(*isa);
		}

	return via_config;
}