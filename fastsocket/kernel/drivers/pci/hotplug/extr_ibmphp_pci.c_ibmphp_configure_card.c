#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct pci_func {int busno; int device; int function; int bus; int /*<<< orphan*/ ** mem; int /*<<< orphan*/ ** pfmem; int /*<<< orphan*/ ** io; struct pci_func* next; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * devices; } ;
struct TYPE_5__ {int number; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCI_CLASS_BRIDGE_PCI ; 
 int PCI_CLASS_DISPLAY_VGA ; 
 int PCI_CLASS_NOT_DEFINED_VGA ; 
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 unsigned int PCI_DEVFN (int,int) ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
#define  PCI_HEADER_TYPE_BRIDGE 131 
#define  PCI_HEADER_TYPE_MULTIBRIDGE 130 
#define  PCI_HEADER_TYPE_MULTIDEVICE 129 
#define  PCI_HEADER_TYPE_NORMAL 128 
 int /*<<< orphan*/  PCI_SECONDARY_BUS ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 scalar_t__ PCI_VENDOR_ID_NOTVALID ; 
 int /*<<< orphan*/  assign_alt_irq (struct pci_func*,int) ; 
 int configure_bridge (struct pci_func**,int) ; 
 int configure_device (struct pci_func*) ; 
 int /*<<< orphan*/  debug (char*,int,...) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 TYPE_1__* ibmphp_pci_bus ; 
 int /*<<< orphan*/  ibmphp_remove_resource (int /*<<< orphan*/ *) ; 
 struct pci_func* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bus_read_config_byte (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_bus_read_config_dword (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_bus_read_config_word (TYPE_1__*,unsigned int,int /*<<< orphan*/ ,scalar_t__*) ; 

int ibmphp_configure_card (struct pci_func *func, u8 slotno)
{
	u16 vendor_id;
	u32 class;
	u8 class_code;
	u8 hdr_type, device, sec_number;
	u8 function;
	struct pci_func *newfunc;	/* for multi devices */
	struct pci_func *cur_func, *prev_func;
	int rc, i, j;
	int cleanup_count;
	u8 flag;
	u8 valid_device = 0x00; /* to see if we are able to read from card any device info at all */

	debug ("inside configure_card, func->busno = %x\n", func->busno);

	device = func->device;
	cur_func = func;

	/* We only get bus and device from IRQ routing table.  So at this point,
	 * func->busno is correct, and func->device contains only device (at the 5 
	 * highest bits)
	 */

	/* For every function on the card */
	for (function = 0x00; function < 0x08; function++) {
		unsigned int devfn = PCI_DEVFN(device, function);
		ibmphp_pci_bus->number = cur_func->busno;

		cur_func->function = function;

		debug ("inside the loop, cur_func->busno = %x, cur_func->device = %x, cur_func->funcion = %x\n",
			cur_func->busno, cur_func->device, cur_func->function);

		pci_bus_read_config_word (ibmphp_pci_bus, devfn, PCI_VENDOR_ID, &vendor_id);

		debug ("vendor_id is %x\n", vendor_id);
		if (vendor_id != PCI_VENDOR_ID_NOTVALID) {
			/* found correct device!!! */
			debug ("found valid device, vendor_id = %x\n", vendor_id);

			++valid_device;

			/* header: x x x x x x x x
			 *         | |___________|=> 1=PPB bridge, 0=normal device, 2=CardBus Bridge
			 *         |_=> 0 = single function device, 1 = multi-function device
			 */

			pci_bus_read_config_byte (ibmphp_pci_bus, devfn, PCI_HEADER_TYPE, &hdr_type);
			pci_bus_read_config_dword (ibmphp_pci_bus, devfn, PCI_CLASS_REVISION, &class);

			class_code = class >> 24;
			debug ("hrd_type = %x, class = %x, class_code %x\n", hdr_type, class, class_code);
			class >>= 8;	/* to take revision out, class = class.subclass.prog i/f */
			if (class == PCI_CLASS_NOT_DEFINED_VGA) {
				err ("The device %x is VGA compatible and as is not supported for hot plugging. "
				     "Please choose another device.\n", cur_func->device);
				return -ENODEV;
			} else if (class == PCI_CLASS_DISPLAY_VGA) {
				err ("The device %x is not supported for hot plugging. "
				     "Please choose another device.\n", cur_func->device);
				return -ENODEV;
			}
			switch (hdr_type) {
				case PCI_HEADER_TYPE_NORMAL:
					debug ("single device case.... vendor id = %x, hdr_type = %x, class = %x\n", vendor_id, hdr_type, class);
					assign_alt_irq (cur_func, class_code);
					if ((rc = configure_device (cur_func)) < 0) {
						/* We need to do this in case some other BARs were properly inserted */
						err ("was not able to configure devfunc %x on bus %x.\n",
						     cur_func->device, cur_func->busno);
						cleanup_count = 6;
						goto error;
					}	
					cur_func->next = NULL;
					function = 0x8;
					break;
				case PCI_HEADER_TYPE_MULTIDEVICE:
					assign_alt_irq (cur_func, class_code);
					if ((rc = configure_device (cur_func)) < 0) {
						/* We need to do this in case some other BARs were properly inserted */
						err ("was not able to configure devfunc %x on bus %x...bailing out\n",
						     cur_func->device, cur_func->busno);
						cleanup_count = 6;
						goto error;
					}
					newfunc = kzalloc(sizeof(*newfunc), GFP_KERNEL);
					if (!newfunc) {
						err ("out of system memory\n");
						return -ENOMEM;
					}
					newfunc->busno = cur_func->busno;
					newfunc->device = device;
					cur_func->next = newfunc;
					cur_func = newfunc;
					for (j = 0; j < 4; j++)
						newfunc->irq[j] = cur_func->irq[j];
					break;
				case PCI_HEADER_TYPE_MULTIBRIDGE:
					class >>= 8;
					if (class != PCI_CLASS_BRIDGE_PCI) {
						err ("This %x is not PCI-to-PCI bridge, and as is not supported for hot-plugging. "
						     "Please insert another card.\n", cur_func->device);
						return -ENODEV;
					}
					assign_alt_irq (cur_func, class_code);
					rc = configure_bridge (&cur_func, slotno);
					if (rc == -ENODEV) {
						err ("You chose to insert Single Bridge, or nested bridges, this is not supported...\n");
						err ("Bus %x, devfunc %x\n", cur_func->busno, cur_func->device);
						return rc;
					}
					if (rc) {
						/* We need to do this in case some other BARs were properly inserted */
						err ("was not able to hot-add PPB properly.\n");
						func->bus = 1; /* To indicate to the unconfigure function that this is a PPB */
						cleanup_count = 2;
						goto error;
					}

					pci_bus_read_config_byte (ibmphp_pci_bus, devfn, PCI_SECONDARY_BUS, &sec_number);
					flag = 0;
					for (i = 0; i < 32; i++) {
						if (func->devices[i]) {
							newfunc = kzalloc(sizeof(*newfunc), GFP_KERNEL);
							if (!newfunc) {
								err ("out of system memory\n");
								return -ENOMEM;
							}
							newfunc->busno = sec_number;
							newfunc->device = (u8) i;
							for (j = 0; j < 4; j++)
								newfunc->irq[j] = cur_func->irq[j];

							if (flag) {
								for (prev_func = cur_func; prev_func->next; prev_func = prev_func->next) ;
								prev_func->next = newfunc;
							} else
								cur_func->next = newfunc;

							rc = ibmphp_configure_card (newfunc, slotno);
							/* This could only happen if kmalloc failed */
							if (rc) {
								/* We need to do this in case bridge itself got configured properly, but devices behind it failed */
								func->bus = 1; /* To indicate to the unconfigure function that this is a PPB */
								cleanup_count = 2;
								goto error;
							}
							flag = 1;
						}
					}

					newfunc = kzalloc(sizeof(*newfunc), GFP_KERNEL);
					if (!newfunc) {
						err ("out of system memory\n");
						return -ENOMEM;
					}
					newfunc->busno = cur_func->busno;
					newfunc->device = device;
					for (j = 0; j < 4; j++)
						newfunc->irq[j] = cur_func->irq[j];
					for (prev_func = cur_func; prev_func->next; prev_func = prev_func->next) ;
					prev_func->next = newfunc;
					cur_func = newfunc;
					break;
				case PCI_HEADER_TYPE_BRIDGE:
					class >>= 8;
					debug ("class now is %x\n", class);
					if (class != PCI_CLASS_BRIDGE_PCI) {
						err ("This %x is not PCI-to-PCI bridge, and as is not supported for hot-plugging. "
						     "Please insert another card.\n", cur_func->device);
						return -ENODEV;
					}

					assign_alt_irq (cur_func, class_code);

					debug ("cur_func->busno b4 configure_bridge is %x\n", cur_func->busno);
					rc = configure_bridge (&cur_func, slotno);
					if (rc == -ENODEV) {
						err ("You chose to insert Single Bridge, or nested bridges, this is not supported...\n");
						err ("Bus %x, devfunc %x\n", cur_func->busno, cur_func->device);
						return rc;
					}
					if (rc) {
						/* We need to do this in case some other BARs were properly inserted */
						func->bus = 1; /* To indicate to the unconfigure function that this is a PPB */
						err ("was not able to hot-add PPB properly.\n");
						cleanup_count = 2;
						goto error;
					}
					debug ("cur_func->busno = %x, device = %x, function = %x\n",
						cur_func->busno, device, function);
					pci_bus_read_config_byte (ibmphp_pci_bus, devfn, PCI_SECONDARY_BUS, &sec_number);
					debug ("after configuring bridge..., sec_number = %x\n", sec_number);
					flag = 0;
					for (i = 0; i < 32; i++) {
						if (func->devices[i]) {
							debug ("inside for loop, device is %x\n", i);
							newfunc = kzalloc(sizeof(*newfunc), GFP_KERNEL);
							if (!newfunc) {
								err (" out of system memory\n");
								return -ENOMEM;
							}
							newfunc->busno = sec_number;
							newfunc->device = (u8) i;
							for (j = 0; j < 4; j++)
								newfunc->irq[j] = cur_func->irq[j];

							if (flag) {
								for (prev_func = cur_func; prev_func->next; prev_func = prev_func->next) ;
								prev_func->next = newfunc;
							} else
								cur_func->next = newfunc;

							rc = ibmphp_configure_card (newfunc, slotno);

							/* Again, this case should not happen... For complete paranoia, will need to call remove_bus */
							if (rc) {
								/* We need to do this in case some other BARs were properly inserted */
								func->bus = 1; /* To indicate to the unconfigure function that this is a PPB */
								cleanup_count = 2;
								goto error;
							}
							flag = 1;
						}
					}

					function = 0x8;
					break;
				default:
					err ("MAJOR PROBLEM!!!!, header type not supported? %x\n", hdr_type);
					return -ENXIO;
					break;
			}	/* end of switch */
		}	/* end of valid device */
	}	/* end of for */

	if (!valid_device) {
		err ("Cannot find any valid devices on the card.  Or unable to read from card.\n");
		return -ENODEV;
	}

	return 0;

error:
	for (i = 0; i < cleanup_count; i++) {
		if (cur_func->io[i]) {
			ibmphp_remove_resource (cur_func->io[i]);
			cur_func->io[i] = NULL;
		} else if (cur_func->pfmem[i]) {
			ibmphp_remove_resource (cur_func->pfmem[i]);
			cur_func->pfmem[i] = NULL;
		} else if (cur_func->mem[i]) {
			ibmphp_remove_resource (cur_func->mem[i]);
			cur_func->mem[i] = NULL;
		}
	}
	return rc;
}