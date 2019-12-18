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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  size_t u_int ;
struct ahc_pci_identity {int full_id; int id_mask; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  ahc_dev_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_DEVVENDOR ; 
 int /*<<< orphan*/  PCIR_SUBDEV_0 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_0 ; 
 scalar_t__ SUBID_9005_MFUNCENB (int /*<<< orphan*/ ) ; 
 scalar_t__ ahc_9005_subdevinfo_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ahc_compose_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ahc_get_pci_function (int /*<<< orphan*/ ) ; 
 size_t ahc_num_pci_devs ; 
 struct ahc_pci_identity* ahc_pci_ident_table ; 
 int /*<<< orphan*/  ahc_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

const struct ahc_pci_identity *
ahc_find_pci_device(ahc_dev_softc_t pci)
{
	uint64_t  full_id;
	uint16_t  device;
	uint16_t  vendor;
	uint16_t  subdevice;
	uint16_t  subvendor;
	const struct ahc_pci_identity *entry;
	u_int	  i;

	vendor = ahc_pci_read_config(pci, PCIR_DEVVENDOR, /*bytes*/2);
	device = ahc_pci_read_config(pci, PCIR_DEVICE, /*bytes*/2);
	subvendor = ahc_pci_read_config(pci, PCIR_SUBVEND_0, /*bytes*/2);
	subdevice = ahc_pci_read_config(pci, PCIR_SUBDEV_0, /*bytes*/2);
	full_id = ahc_compose_id(device, vendor, subdevice, subvendor);

	/*
	 * If the second function is not hooked up, ignore it.
	 * Unfortunately, not all MB vendors implement the
	 * subdevice ID as per the Adaptec spec, so do our best
	 * to sanity check it prior to accepting the subdevice
	 * ID as valid.
	 */
	if (ahc_get_pci_function(pci) > 0
	 && ahc_9005_subdevinfo_valid(vendor, device, subvendor, subdevice)
	 && SUBID_9005_MFUNCENB(subdevice) == 0)
		return (NULL);

	for (i = 0; i < ahc_num_pci_devs; i++) {
		entry = &ahc_pci_ident_table[i];
		if (entry->full_id == (full_id & entry->id_mask)) {
			/* Honor exclusion entries. */
			if (entry->name == NULL)
				return (NULL);
			return (entry);
		}
	}
	return (NULL);
}