#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_bus {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {int device; int /*<<< orphan*/  bus; int /*<<< orphan*/  segment; } ;
struct acpi_prt_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  index; scalar_t__ pin; TYPE_1__ id; int /*<<< orphan*/  link; } ;
struct acpi_pci_routing_table {int address; scalar_t__* source; int /*<<< orphan*/  source_index; scalar_t__ pin; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_prt_list ; 
 int /*<<< orphan*/  acpi_prt_lock ; 
 int /*<<< orphan*/  do_prt_fixups (struct acpi_prt_entry*,struct acpi_pci_routing_table*) ; 
 struct acpi_prt_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 int /*<<< orphan*/  pin_name (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_pci_irq_add_entry(acpi_handle handle, struct pci_bus *bus,
				  struct acpi_pci_routing_table *prt)
{
	struct acpi_prt_entry *entry;

	entry = kzalloc(sizeof(struct acpi_prt_entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	/*
	 * Note that the _PRT uses 0=INTA, 1=INTB, etc, while PCI uses
	 * 1=INTA, 2=INTB.  We use the PCI encoding throughout, so convert
	 * it here.
	 */
	entry->id.segment = pci_domain_nr(bus);
	entry->id.bus = bus->number;
	entry->id.device = (prt->address >> 16) & 0xFFFF;
	entry->pin = prt->pin + 1;

	do_prt_fixups(entry, prt);

	entry->index = prt->source_index;

	/*
	 * Type 1: Dynamic
	 * ---------------
	 * The 'source' field specifies the PCI interrupt link device used to
	 * configure the IRQ assigned to this slot|dev|pin.  The 'source_index'
	 * indicates which resource descriptor in the resource template (of
	 * the link device) this interrupt is allocated from.
	 * 
	 * NOTE: Don't query the Link Device for IRQ information at this time
	 *       because Link Device enumeration may not have occurred yet
	 *       (e.g. exists somewhere 'below' this _PRT entry in the ACPI
	 *       namespace).
	 */
	if (prt->source[0])
		acpi_get_handle(handle, prt->source, &entry->link);

	/*
	 * Type 2: Static
	 * --------------
	 * The 'source' field is NULL, and the 'source_index' field specifies
	 * the IRQ value, which is hardwired to specific interrupt inputs on
	 * the interrupt controller.
	 */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INFO,
			      "      %04x:%02x:%02x[%c] -> %s[%d]\n",
			      entry->id.segment, entry->id.bus,
			      entry->id.device, pin_name(entry->pin),
			      prt->source, entry->index));

	spin_lock(&acpi_prt_lock);
	list_add_tail(&entry->list, &acpi_prt_list);
	spin_unlock(&acpi_prt_lock);

	return 0;
}