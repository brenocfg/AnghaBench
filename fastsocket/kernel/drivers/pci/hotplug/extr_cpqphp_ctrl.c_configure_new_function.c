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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct resource_lists {struct pci_resource* p_mem_head; struct pci_resource* mem_head; struct pci_resource* io_head; struct pci_resource* bus_head; struct irq_mapping* irqs; } ;
struct pci_resource {int base; int length; struct pci_resource* next; } ;
struct pci_func {int bus; int device; int is_a_board; int configured; struct pci_resource* mem_head; struct pci_resource* p_mem_head; struct pci_resource* io_head; struct pci_resource* bus_head; scalar_t__ status; scalar_t__ function; } ;
struct pci_bus {int number; } ;
struct irq_mapping {int barber_pole; int* interrupt; int valid_INT; } ;
struct controller {struct pci_bus* pci_bus; } ;

/* Variables and functions */
 int DEVICE_TYPE_NOT_SUPPORTED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NOT_ENOUGH_RESOURCES ; 
 int PCI_BASE_CLASS_DISPLAY ; 
 int PCI_BASE_CLASS_STORAGE ; 
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 unsigned int PCI_DEVFN (int,scalar_t__) ; 
 int PCI_HEADER_TYPE ; 
 int PCI_HEADER_TYPE_BRIDGE ; 
 int PCI_HEADER_TYPE_NORMAL ; 
 int /*<<< orphan*/  PCI_INTERRUPT_LINE ; 
 int PCI_INTERRUPT_PIN ; 
 int /*<<< orphan*/  PCI_IO_BASE ; 
 int /*<<< orphan*/  PCI_IO_LIMIT ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  PCI_MEMORY_BASE ; 
 int /*<<< orphan*/  PCI_MEMORY_LIMIT ; 
 int /*<<< orphan*/  PCI_PREF_MEMORY_BASE ; 
 int /*<<< orphan*/  PCI_PREF_MEMORY_LIMIT ; 
 int /*<<< orphan*/  PCI_PRIMARY_BUS ; 
 int /*<<< orphan*/  PCI_ROM_ADDRESS ; 
 int /*<<< orphan*/  PCI_SECONDARY_BUS ; 
 int /*<<< orphan*/  PCI_SEC_LATENCY_TIMER ; 
 int /*<<< orphan*/  PCI_SUBORDINATE_BUS ; 
 int configure_new_device (struct controller*,struct pci_func*,int,struct resource_lists*) ; 
 int /*<<< orphan*/  cpqhp_destroy_resource_list (struct resource_lists*) ; 
 int cpqhp_disk_irq ; 
 scalar_t__ cpqhp_legacy_mode ; 
 int cpqhp_nic_irq ; 
 int cpqhp_set_irq (int,int,int,int) ; 
 struct pci_func* cpqhp_slot_create (int) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 struct pci_resource* do_bridge_resource_split (struct pci_resource**,int) ; 
 struct pci_resource* do_pre_bridge_resource_split (struct pci_resource**,struct pci_resource**,int) ; 
 struct pci_resource* get_io_resource (struct pci_resource**,int) ; 
 struct pci_resource* get_max_resource (struct pci_resource**,int) ; 
 struct pci_resource* get_resource (struct pci_resource**,int) ; 
 int /*<<< orphan*/  kfree (struct pci_resource*) ; 
 struct pci_resource* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct pci_resource*,struct pci_resource*,int) ; 
 int pci_bus_read_config_byte (struct pci_bus*,unsigned int,int,int*) ; 
 int pci_bus_read_config_dword (struct pci_bus*,unsigned int,int,int*) ; 
 int pci_bus_write_config_byte (struct pci_bus*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int pci_bus_write_config_dword (struct pci_bus*,unsigned int,int,int) ; 
 int pci_bus_write_config_word (struct pci_bus*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_resource (struct pci_resource**,struct pci_resource*) ; 

__attribute__((used)) static int configure_new_function(struct controller *ctrl, struct pci_func *func,
				   u8 behind_bridge,
				   struct resource_lists *resources)
{
	int cloop;
	u8 IRQ = 0;
	u8 temp_byte;
	u8 device;
	u8 class_code;
	u16 command;
	u16 temp_word;
	u32 temp_dword;
	u32 rc;
	u32 temp_register;
	u32 base;
	u32 ID;
	unsigned int devfn;
	struct pci_resource *mem_node;
	struct pci_resource *p_mem_node;
	struct pci_resource *io_node;
	struct pci_resource *bus_node;
	struct pci_resource *hold_mem_node;
	struct pci_resource *hold_p_mem_node;
	struct pci_resource *hold_IO_node;
	struct pci_resource *hold_bus_node;
	struct irq_mapping irqs;
	struct pci_func *new_slot;
	struct pci_bus *pci_bus;
	struct resource_lists temp_resources;

	pci_bus = ctrl->pci_bus;
	pci_bus->number = func->bus;
	devfn = PCI_DEVFN(func->device, func->function);

	/* Check for Bridge */
	rc = pci_bus_read_config_byte(pci_bus, devfn, PCI_HEADER_TYPE, &temp_byte);
	if (rc)
		return rc;

	if ((temp_byte & 0x7F) == PCI_HEADER_TYPE_BRIDGE) {
		/* set Primary bus */
		dbg("set Primary bus = %d\n", func->bus);
		rc = pci_bus_write_config_byte(pci_bus, devfn, PCI_PRIMARY_BUS, func->bus);
		if (rc)
			return rc;

		/* find range of busses to use */
		dbg("find ranges of buses to use\n");
		bus_node = get_max_resource(&(resources->bus_head), 1);

		/* If we don't have any busses to allocate, we can't continue */
		if (!bus_node)
			return -ENOMEM;

		/* set Secondary bus */
		temp_byte = bus_node->base;
		dbg("set Secondary bus = %d\n", bus_node->base);
		rc = pci_bus_write_config_byte(pci_bus, devfn, PCI_SECONDARY_BUS, temp_byte);
		if (rc)
			return rc;

		/* set subordinate bus */
		temp_byte = bus_node->base + bus_node->length - 1;
		dbg("set subordinate bus = %d\n", bus_node->base + bus_node->length - 1);
		rc = pci_bus_write_config_byte(pci_bus, devfn, PCI_SUBORDINATE_BUS, temp_byte);
		if (rc)
			return rc;

		/* set subordinate Latency Timer and base Latency Timer */
		temp_byte = 0x40;
		rc = pci_bus_write_config_byte(pci_bus, devfn, PCI_SEC_LATENCY_TIMER, temp_byte);
		if (rc)
			return rc;
		rc = pci_bus_write_config_byte(pci_bus, devfn, PCI_LATENCY_TIMER, temp_byte);
		if (rc)
			return rc;

		/* set Cache Line size */
		temp_byte = 0x08;
		rc = pci_bus_write_config_byte(pci_bus, devfn, PCI_CACHE_LINE_SIZE, temp_byte);
		if (rc)
			return rc;

		/* Setup the IO, memory, and prefetchable windows */
		io_node = get_max_resource(&(resources->io_head), 0x1000);
		if (!io_node)
			return -ENOMEM;
		mem_node = get_max_resource(&(resources->mem_head), 0x100000);
		if (!mem_node)
			return -ENOMEM;
		p_mem_node = get_max_resource(&(resources->p_mem_head), 0x100000);
		if (!p_mem_node)
			return -ENOMEM;
		dbg("Setup the IO, memory, and prefetchable windows\n");
		dbg("io_node\n");
		dbg("(base, len, next) (%x, %x, %p)\n", io_node->base,
					io_node->length, io_node->next);
		dbg("mem_node\n");
		dbg("(base, len, next) (%x, %x, %p)\n", mem_node->base,
					mem_node->length, mem_node->next);
		dbg("p_mem_node\n");
		dbg("(base, len, next) (%x, %x, %p)\n", p_mem_node->base,
					p_mem_node->length, p_mem_node->next);

		/* set up the IRQ info */
		if (!resources->irqs) {
			irqs.barber_pole = 0;
			irqs.interrupt[0] = 0;
			irqs.interrupt[1] = 0;
			irqs.interrupt[2] = 0;
			irqs.interrupt[3] = 0;
			irqs.valid_INT = 0;
		} else {
			irqs.barber_pole = resources->irqs->barber_pole;
			irqs.interrupt[0] = resources->irqs->interrupt[0];
			irqs.interrupt[1] = resources->irqs->interrupt[1];
			irqs.interrupt[2] = resources->irqs->interrupt[2];
			irqs.interrupt[3] = resources->irqs->interrupt[3];
			irqs.valid_INT = resources->irqs->valid_INT;
		}

		/* set up resource lists that are now aligned on top and bottom
		 * for anything behind the bridge. */
		temp_resources.bus_head = bus_node;
		temp_resources.io_head = io_node;
		temp_resources.mem_head = mem_node;
		temp_resources.p_mem_head = p_mem_node;
		temp_resources.irqs = &irqs;

		/* Make copies of the nodes we are going to pass down so that
		 * if there is a problem,we can just use these to free resources
		 */
		hold_bus_node = kmalloc(sizeof(*hold_bus_node), GFP_KERNEL);
		hold_IO_node = kmalloc(sizeof(*hold_IO_node), GFP_KERNEL);
		hold_mem_node = kmalloc(sizeof(*hold_mem_node), GFP_KERNEL);
		hold_p_mem_node = kmalloc(sizeof(*hold_p_mem_node), GFP_KERNEL);

		if (!hold_bus_node || !hold_IO_node || !hold_mem_node || !hold_p_mem_node) {
			kfree(hold_bus_node);
			kfree(hold_IO_node);
			kfree(hold_mem_node);
			kfree(hold_p_mem_node);

			return 1;
		}

		memcpy(hold_bus_node, bus_node, sizeof(struct pci_resource));

		bus_node->base += 1;
		bus_node->length -= 1;
		bus_node->next = NULL;

		/* If we have IO resources copy them and fill in the bridge's
		 * IO range registers */
		if (io_node) {
			memcpy(hold_IO_node, io_node, sizeof(struct pci_resource));
			io_node->next = NULL;

			/* set IO base and Limit registers */
			temp_byte = io_node->base >> 8;
			rc = pci_bus_write_config_byte(pci_bus, devfn, PCI_IO_BASE, temp_byte);

			temp_byte = (io_node->base + io_node->length - 1) >> 8;
			rc = pci_bus_write_config_byte(pci_bus, devfn, PCI_IO_LIMIT, temp_byte);
		} else {
			kfree(hold_IO_node);
			hold_IO_node = NULL;
		}

		/* If we have memory resources copy them and fill in the
		 * bridge's memory range registers.  Otherwise, fill in the
		 * range registers with values that disable them. */
		if (mem_node) {
			memcpy(hold_mem_node, mem_node, sizeof(struct pci_resource));
			mem_node->next = NULL;

			/* set Mem base and Limit registers */
			temp_word = mem_node->base >> 16;
			rc = pci_bus_write_config_word(pci_bus, devfn, PCI_MEMORY_BASE, temp_word);

			temp_word = (mem_node->base + mem_node->length - 1) >> 16;
			rc = pci_bus_write_config_word(pci_bus, devfn, PCI_MEMORY_LIMIT, temp_word);
		} else {
			temp_word = 0xFFFF;
			rc = pci_bus_write_config_word(pci_bus, devfn, PCI_MEMORY_BASE, temp_word);

			temp_word = 0x0000;
			rc = pci_bus_write_config_word(pci_bus, devfn, PCI_MEMORY_LIMIT, temp_word);

			kfree(hold_mem_node);
			hold_mem_node = NULL;
		}

		memcpy(hold_p_mem_node, p_mem_node, sizeof(struct pci_resource));
		p_mem_node->next = NULL;

		/* set Pre Mem base and Limit registers */
		temp_word = p_mem_node->base >> 16;
		rc = pci_bus_write_config_word (pci_bus, devfn, PCI_PREF_MEMORY_BASE, temp_word);

		temp_word = (p_mem_node->base + p_mem_node->length - 1) >> 16;
		rc = pci_bus_write_config_word (pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, temp_word);

		/* Adjust this to compensate for extra adjustment in first loop
		 */
		irqs.barber_pole--;

		rc = 0;

		/* Here we actually find the devices and configure them */
		for (device = 0; (device <= 0x1F) && !rc; device++) {
			irqs.barber_pole = (irqs.barber_pole + 1) & 0x03;

			ID = 0xFFFFFFFF;
			pci_bus->number = hold_bus_node->base;
			pci_bus_read_config_dword (pci_bus, PCI_DEVFN(device, 0), 0x00, &ID);
			pci_bus->number = func->bus;

			if (ID != 0xFFFFFFFF) {	  /*  device present */
				/* Setup slot structure. */
				new_slot = cpqhp_slot_create(hold_bus_node->base);

				if (new_slot == NULL) {
					rc = -ENOMEM;
					continue;
				}

				new_slot->bus = hold_bus_node->base;
				new_slot->device = device;
				new_slot->function = 0;
				new_slot->is_a_board = 1;
				new_slot->status = 0;

				rc = configure_new_device(ctrl, new_slot, 1, &temp_resources);
				dbg("configure_new_device rc=0x%x\n",rc);
			}	/* End of IF (device in slot?) */
		}		/* End of FOR loop */

		if (rc)
			goto free_and_out;
		/* save the interrupt routing information */
		if (resources->irqs) {
			resources->irqs->interrupt[0] = irqs.interrupt[0];
			resources->irqs->interrupt[1] = irqs.interrupt[1];
			resources->irqs->interrupt[2] = irqs.interrupt[2];
			resources->irqs->interrupt[3] = irqs.interrupt[3];
			resources->irqs->valid_INT = irqs.valid_INT;
		} else if (!behind_bridge) {
			/* We need to hook up the interrupts here */
			for (cloop = 0; cloop < 4; cloop++) {
				if (irqs.valid_INT & (0x01 << cloop)) {
					rc = cpqhp_set_irq(func->bus, func->device,
							   cloop + 1, irqs.interrupt[cloop]);
					if (rc)
						goto free_and_out;
				}
			}	/* end of for loop */
		}
		/* Return unused bus resources
		 * First use the temporary node to store information for
		 * the board */
		if (hold_bus_node && bus_node && temp_resources.bus_head) {
			hold_bus_node->length = bus_node->base - hold_bus_node->base;

			hold_bus_node->next = func->bus_head;
			func->bus_head = hold_bus_node;

			temp_byte = temp_resources.bus_head->base - 1;

			/* set subordinate bus */
			rc = pci_bus_write_config_byte (pci_bus, devfn, PCI_SUBORDINATE_BUS, temp_byte);

			if (temp_resources.bus_head->length == 0) {
				kfree(temp_resources.bus_head);
				temp_resources.bus_head = NULL;
			} else {
				return_resource(&(resources->bus_head), temp_resources.bus_head);
			}
		}

		/* If we have IO space available and there is some left,
		 * return the unused portion */
		if (hold_IO_node && temp_resources.io_head) {
			io_node = do_pre_bridge_resource_split(&(temp_resources.io_head),
							       &hold_IO_node, 0x1000);

			/* Check if we were able to split something off */
			if (io_node) {
				hold_IO_node->base = io_node->base + io_node->length;

				temp_byte = (hold_IO_node->base) >> 8;
				rc = pci_bus_write_config_word (pci_bus, devfn, PCI_IO_BASE, temp_byte);

				return_resource(&(resources->io_head), io_node);
			}

			io_node = do_bridge_resource_split(&(temp_resources.io_head), 0x1000);

			/* Check if we were able to split something off */
			if (io_node) {
				/* First use the temporary node to store
				 * information for the board */
				hold_IO_node->length = io_node->base - hold_IO_node->base;

				/* If we used any, add it to the board's list */
				if (hold_IO_node->length) {
					hold_IO_node->next = func->io_head;
					func->io_head = hold_IO_node;

					temp_byte = (io_node->base - 1) >> 8;
					rc = pci_bus_write_config_byte (pci_bus, devfn, PCI_IO_LIMIT, temp_byte);

					return_resource(&(resources->io_head), io_node);
				} else {
					/* it doesn't need any IO */
					temp_word = 0x0000;
					rc = pci_bus_write_config_word (pci_bus, devfn, PCI_IO_LIMIT, temp_word);

					return_resource(&(resources->io_head), io_node);
					kfree(hold_IO_node);
				}
			} else {
				/* it used most of the range */
				hold_IO_node->next = func->io_head;
				func->io_head = hold_IO_node;
			}
		} else if (hold_IO_node) {
			/* it used the whole range */
			hold_IO_node->next = func->io_head;
			func->io_head = hold_IO_node;
		}
		/* If we have memory space available and there is some left,
		 * return the unused portion */
		if (hold_mem_node && temp_resources.mem_head) {
			mem_node = do_pre_bridge_resource_split(&(temp_resources.  mem_head),
								&hold_mem_node, 0x100000);

			/* Check if we were able to split something off */
			if (mem_node) {
				hold_mem_node->base = mem_node->base + mem_node->length;

				temp_word = (hold_mem_node->base) >> 16;
				rc = pci_bus_write_config_word (pci_bus, devfn, PCI_MEMORY_BASE, temp_word);

				return_resource(&(resources->mem_head), mem_node);
			}

			mem_node = do_bridge_resource_split(&(temp_resources.mem_head), 0x100000);

			/* Check if we were able to split something off */
			if (mem_node) {
				/* First use the temporary node to store
				 * information for the board */
				hold_mem_node->length = mem_node->base - hold_mem_node->base;

				if (hold_mem_node->length) {
					hold_mem_node->next = func->mem_head;
					func->mem_head = hold_mem_node;

					/* configure end address */
					temp_word = (mem_node->base - 1) >> 16;
					rc = pci_bus_write_config_word (pci_bus, devfn, PCI_MEMORY_LIMIT, temp_word);

					/* Return unused resources to the pool */
					return_resource(&(resources->mem_head), mem_node);
				} else {
					/* it doesn't need any Mem */
					temp_word = 0x0000;
					rc = pci_bus_write_config_word (pci_bus, devfn, PCI_MEMORY_LIMIT, temp_word);

					return_resource(&(resources->mem_head), mem_node);
					kfree(hold_mem_node);
				}
			} else {
				/* it used most of the range */
				hold_mem_node->next = func->mem_head;
				func->mem_head = hold_mem_node;
			}
		} else if (hold_mem_node) {
			/* it used the whole range */
			hold_mem_node->next = func->mem_head;
			func->mem_head = hold_mem_node;
		}
		/* If we have prefetchable memory space available and there
		 * is some left at the end, return the unused portion */
		if (hold_p_mem_node && temp_resources.p_mem_head) {
			p_mem_node = do_pre_bridge_resource_split(&(temp_resources.p_mem_head),
								  &hold_p_mem_node, 0x100000);

			/* Check if we were able to split something off */
			if (p_mem_node) {
				hold_p_mem_node->base = p_mem_node->base + p_mem_node->length;

				temp_word = (hold_p_mem_node->base) >> 16;
				rc = pci_bus_write_config_word (pci_bus, devfn, PCI_PREF_MEMORY_BASE, temp_word);

				return_resource(&(resources->p_mem_head), p_mem_node);
			}

			p_mem_node = do_bridge_resource_split(&(temp_resources.p_mem_head), 0x100000);

			/* Check if we were able to split something off */
			if (p_mem_node) {
				/* First use the temporary node to store
				 * information for the board */
				hold_p_mem_node->length = p_mem_node->base - hold_p_mem_node->base;

				/* If we used any, add it to the board's list */
				if (hold_p_mem_node->length) {
					hold_p_mem_node->next = func->p_mem_head;
					func->p_mem_head = hold_p_mem_node;

					temp_word = (p_mem_node->base - 1) >> 16;
					rc = pci_bus_write_config_word (pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, temp_word);

					return_resource(&(resources->p_mem_head), p_mem_node);
				} else {
					/* it doesn't need any PMem */
					temp_word = 0x0000;
					rc = pci_bus_write_config_word (pci_bus, devfn, PCI_PREF_MEMORY_LIMIT, temp_word);

					return_resource(&(resources->p_mem_head), p_mem_node);
					kfree(hold_p_mem_node);
				}
			} else {
				/* it used the most of the range */
				hold_p_mem_node->next = func->p_mem_head;
				func->p_mem_head = hold_p_mem_node;
			}
		} else if (hold_p_mem_node) {
			/* it used the whole range */
			hold_p_mem_node->next = func->p_mem_head;
			func->p_mem_head = hold_p_mem_node;
		}
		/* We should be configuring an IRQ and the bridge's base address
		 * registers if it needs them.  Although we have never seen such
		 * a device */

		/* enable card */
		command = 0x0157;	/* = PCI_COMMAND_IO |
					 *   PCI_COMMAND_MEMORY |
					 *   PCI_COMMAND_MASTER |
					 *   PCI_COMMAND_INVALIDATE |
					 *   PCI_COMMAND_PARITY |
					 *   PCI_COMMAND_SERR */
		rc = pci_bus_write_config_word (pci_bus, devfn, PCI_COMMAND, command);

		/* set Bridge Control Register */
		command = 0x07;		/* = PCI_BRIDGE_CTL_PARITY |
					 *   PCI_BRIDGE_CTL_SERR |
					 *   PCI_BRIDGE_CTL_NO_ISA */
		rc = pci_bus_write_config_word (pci_bus, devfn, PCI_BRIDGE_CONTROL, command);
	} else if ((temp_byte & 0x7F) == PCI_HEADER_TYPE_NORMAL) {
		/* Standard device */
		rc = pci_bus_read_config_byte (pci_bus, devfn, 0x0B, &class_code);

		if (class_code == PCI_BASE_CLASS_DISPLAY) {
			/* Display (video) adapter (not supported) */
			return DEVICE_TYPE_NOT_SUPPORTED;
		}
		/* Figure out IO and memory needs */
		for (cloop = 0x10; cloop <= 0x24; cloop += 4) {
			temp_register = 0xFFFFFFFF;

			dbg("CND: bus=%d, devfn=%d, offset=%d\n", pci_bus->number, devfn, cloop);
			rc = pci_bus_write_config_dword (pci_bus, devfn, cloop, temp_register);

			rc = pci_bus_read_config_dword (pci_bus, devfn, cloop, &temp_register);
			dbg("CND: base = 0x%x\n", temp_register);

			if (temp_register) {	  /* If this register is implemented */
				if ((temp_register & 0x03L) == 0x01) {
					/* Map IO */

					/* set base = amount of IO space */
					base = temp_register & 0xFFFFFFFC;
					base = ~base + 1;

					dbg("CND:      length = 0x%x\n", base);
					io_node = get_io_resource(&(resources->io_head), base);
					dbg("Got io_node start = %8.8x, length = %8.8x next (%p)\n",
					    io_node->base, io_node->length, io_node->next);
					dbg("func (%p) io_head (%p)\n", func, func->io_head);

					/* allocate the resource to the board */
					if (io_node) {
						base = io_node->base;

						io_node->next = func->io_head;
						func->io_head = io_node;
					} else
						return -ENOMEM;
				} else if ((temp_register & 0x0BL) == 0x08) {
					/* Map prefetchable memory */
					base = temp_register & 0xFFFFFFF0;
					base = ~base + 1;

					dbg("CND:      length = 0x%x\n", base);
					p_mem_node = get_resource(&(resources->p_mem_head), base);

					/* allocate the resource to the board */
					if (p_mem_node) {
						base = p_mem_node->base;

						p_mem_node->next = func->p_mem_head;
						func->p_mem_head = p_mem_node;
					} else
						return -ENOMEM;
				} else if ((temp_register & 0x0BL) == 0x00) {
					/* Map memory */
					base = temp_register & 0xFFFFFFF0;
					base = ~base + 1;

					dbg("CND:      length = 0x%x\n", base);
					mem_node = get_resource(&(resources->mem_head), base);

					/* allocate the resource to the board */
					if (mem_node) {
						base = mem_node->base;

						mem_node->next = func->mem_head;
						func->mem_head = mem_node;
					} else
						return -ENOMEM;
				} else if ((temp_register & 0x0BL) == 0x04) {
					/* Map memory */
					base = temp_register & 0xFFFFFFF0;
					base = ~base + 1;

					dbg("CND:      length = 0x%x\n", base);
					mem_node = get_resource(&(resources->mem_head), base);

					/* allocate the resource to the board */
					if (mem_node) {
						base = mem_node->base;

						mem_node->next = func->mem_head;
						func->mem_head = mem_node;
					} else
						return -ENOMEM;
				} else if ((temp_register & 0x0BL) == 0x06) {
					/* Those bits are reserved, we can't handle this */
					return 1;
				} else {
					/* Requesting space below 1M */
					return NOT_ENOUGH_RESOURCES;
				}

				rc = pci_bus_write_config_dword(pci_bus, devfn, cloop, base);

				/* Check for 64-bit base */
				if ((temp_register & 0x07L) == 0x04) {
					cloop += 4;

					/* Upper 32 bits of address always zero
					 * on today's systems */
					/* FIXME this is probably not true on
					 * Alpha and ia64??? */
					base = 0;
					rc = pci_bus_write_config_dword(pci_bus, devfn, cloop, base);
				}
			}
		}		/* End of base register loop */
		if (cpqhp_legacy_mode) {
			/* Figure out which interrupt pin this function uses */
			rc = pci_bus_read_config_byte (pci_bus, devfn,
				PCI_INTERRUPT_PIN, &temp_byte);

			/* If this function needs an interrupt and we are behind
			 * a bridge and the pin is tied to something that's
			 * alread mapped, set this one the same */
			if (temp_byte && resources->irqs &&
			    (resources->irqs->valid_INT &
			     (0x01 << ((temp_byte + resources->irqs->barber_pole - 1) & 0x03)))) {
				/* We have to share with something already set up */
				IRQ = resources->irqs->interrupt[(temp_byte +
					resources->irqs->barber_pole - 1) & 0x03];
			} else {
				/* Program IRQ based on card type */
				rc = pci_bus_read_config_byte (pci_bus, devfn, 0x0B, &class_code);

				if (class_code == PCI_BASE_CLASS_STORAGE)
					IRQ = cpqhp_disk_irq;
				else
					IRQ = cpqhp_nic_irq;
			}

			/* IRQ Line */
			rc = pci_bus_write_config_byte (pci_bus, devfn, PCI_INTERRUPT_LINE, IRQ);
		}

		if (!behind_bridge) {
			rc = cpqhp_set_irq(func->bus, func->device, temp_byte, IRQ);
			if (rc)
				return 1;
		} else {
			/* TBD - this code may also belong in the other clause
			 * of this If statement */
			resources->irqs->interrupt[(temp_byte + resources->irqs->barber_pole - 1) & 0x03] = IRQ;
			resources->irqs->valid_INT |= 0x01 << (temp_byte + resources->irqs->barber_pole - 1) & 0x03;
		}

		/* Latency Timer */
		temp_byte = 0x40;
		rc = pci_bus_write_config_byte(pci_bus, devfn,
					PCI_LATENCY_TIMER, temp_byte);

		/* Cache Line size */
		temp_byte = 0x08;
		rc = pci_bus_write_config_byte(pci_bus, devfn,
					PCI_CACHE_LINE_SIZE, temp_byte);

		/* disable ROM base Address */
		temp_dword = 0x00L;
		rc = pci_bus_write_config_word(pci_bus, devfn,
					PCI_ROM_ADDRESS, temp_dword);

		/* enable card */
		temp_word = 0x0157;	/* = PCI_COMMAND_IO |
					 *   PCI_COMMAND_MEMORY |
					 *   PCI_COMMAND_MASTER |
					 *   PCI_COMMAND_INVALIDATE |
					 *   PCI_COMMAND_PARITY |
					 *   PCI_COMMAND_SERR */
		rc = pci_bus_write_config_word (pci_bus, devfn,
					PCI_COMMAND, temp_word);
	} else {		/* End of Not-A-Bridge else */
		/* It's some strange type of PCI adapter (Cardbus?) */
		return DEVICE_TYPE_NOT_SUPPORTED;
	}

	func->configured = 1;

	return 0;
free_and_out:
	cpqhp_destroy_resource_list (&temp_resources);

	return_resource(&(resources-> bus_head), hold_bus_node);
	return_resource(&(resources-> io_head), hold_IO_node);
	return_resource(&(resources-> mem_head), hold_mem_node);
	return_resource(&(resources-> p_mem_head), hold_p_mem_node);
	return rc;
}