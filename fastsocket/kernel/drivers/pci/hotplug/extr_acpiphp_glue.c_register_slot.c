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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct acpiphp_slot {int function; int flags; int device; unsigned long long sun; struct acpiphp_slot* next; TYPE_1__ nb; int /*<<< orphan*/  funcs; int /*<<< orphan*/  sibling; struct acpiphp_slot* slot; int /*<<< orphan*/  crit_sect; struct acpiphp_bridge* bridge; int /*<<< orphan*/  handle; } ;
struct acpiphp_func {int function; int flags; int device; unsigned long long sun; struct acpiphp_func* next; TYPE_1__ nb; int /*<<< orphan*/  funcs; int /*<<< orphan*/  sibling; struct acpiphp_func* slot; int /*<<< orphan*/  crit_sect; struct acpiphp_bridge* bridge; int /*<<< orphan*/  handle; } ;
struct acpiphp_bridge {int nr_slots; struct acpiphp_slot* slots; struct pci_bus* pci_bus; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SYSTEM_NOTIFY ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int EBUSY ; 
 int FUNC_HAS_DCK ; 
 int FUNC_HAS_EJ0 ; 
 int FUNC_HAS_PS0 ; 
 int FUNC_HAS_PS3 ; 
 int FUNC_HAS_STA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCI_DEVFN (int,int) ; 
 int SLOT_ENABLED ; 
 int SLOT_POWEREDON ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpiphp_slot*) ; 
 int /*<<< orphan*/  acpi_pci_check_ejectable (struct pci_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpiphp_dock_ops ; 
 int acpiphp_register_hotplug_slot (struct acpiphp_slot*) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  handle_hotplug_event_func ; 
 scalar_t__ is_dock_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpiphp_slot*) ; 
 struct acpiphp_slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 struct pci_dev* pci_get_slot (struct pci_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_dock_fixups ; 
 scalar_t__ register_dock_notifier (TYPE_1__*) ; 
 scalar_t__ register_hotplug_dock_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpiphp_slot*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static acpi_status
register_slot(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	struct acpiphp_bridge *bridge = (struct acpiphp_bridge *)context;
	struct acpiphp_slot *slot;
	struct acpiphp_func *newfunc;
	acpi_handle tmp;
	acpi_status status = AE_OK;
	unsigned long long adr, sun;
	int device, function, retval;
	struct pci_bus *pbus = bridge->pci_bus;
	struct pci_dev *pdev;

	if (!acpi_pci_check_ejectable(pbus, handle) && !is_dock_device(handle))
		return AE_OK;

	acpi_evaluate_integer(handle, "_ADR", NULL, &adr);
	device = (adr >> 16) & 0xffff;
	function = adr & 0xffff;

	newfunc = kzalloc(sizeof(struct acpiphp_func), GFP_KERNEL);
	if (!newfunc)
		return AE_NO_MEMORY;

	INIT_LIST_HEAD(&newfunc->sibling);
	newfunc->handle = handle;
	newfunc->function = function;

	if (ACPI_SUCCESS(acpi_get_handle(handle, "_EJ0", &tmp)))
		newfunc->flags = FUNC_HAS_EJ0;

	if (ACPI_SUCCESS(acpi_get_handle(handle, "_STA", &tmp)))
		newfunc->flags |= FUNC_HAS_STA;

	if (ACPI_SUCCESS(acpi_get_handle(handle, "_PS0", &tmp)))
		newfunc->flags |= FUNC_HAS_PS0;

	if (ACPI_SUCCESS(acpi_get_handle(handle, "_PS3", &tmp)))
		newfunc->flags |= FUNC_HAS_PS3;

	if (ACPI_SUCCESS(acpi_get_handle(handle, "_DCK", &tmp)))
		newfunc->flags |= FUNC_HAS_DCK;

	status = acpi_evaluate_integer(handle, "_SUN", NULL, &sun);
	if (ACPI_FAILURE(status)) {
		/*
		 * use the count of the number of slots we've found
		 * for the number of the slot
		 */
		sun = bridge->nr_slots+1;
	}

	/* search for objects that share the same slot */
	for (slot = bridge->slots; slot; slot = slot->next)
		if (slot->device == device) {
			if (slot->sun != sun)
				warn("sibling found, but _SUN doesn't match!\n");
			break;
		}

	if (!slot) {
		slot = kzalloc(sizeof(struct acpiphp_slot), GFP_KERNEL);
		if (!slot) {
			kfree(newfunc);
			return AE_NO_MEMORY;
		}

		slot->bridge = bridge;
		slot->device = device;
		slot->sun = sun;
		INIT_LIST_HEAD(&slot->funcs);
		mutex_init(&slot->crit_sect);

		slot->next = bridge->slots;
		bridge->slots = slot;

		bridge->nr_slots++;

		dbg("found ACPI PCI Hotplug slot %llu at PCI %04x:%02x:%02x\n",
		    slot->sun, pci_domain_nr(pbus), pbus->number, device);
		retval = acpiphp_register_hotplug_slot(slot);
		if (retval) {
			if (retval == -EBUSY)
				warn("Slot %llu already registered by another "
					"hotplug driver\n", slot->sun);
			else
				warn("acpiphp_register_hotplug_slot failed "
					"(err code = 0x%x)\n", retval);
			goto err_exit;
		}
	}

	newfunc->slot = slot;
	list_add_tail(&newfunc->sibling, &slot->funcs);

	pdev = pci_get_slot(pbus, PCI_DEVFN(device, function));
	if (pdev) {
		slot->flags |= (SLOT_ENABLED | SLOT_POWEREDON);
		pci_dev_put(pdev);
	}

	if (is_dock_device(handle)) {
		/* we don't want to call this device's _EJ0
		 * because we want the dock notify handler
		 * to call it after it calls _DCK
		 */
		newfunc->flags &= ~FUNC_HAS_EJ0;
		if (register_hotplug_dock_device(handle,
			&acpiphp_dock_ops, newfunc))
			dbg("failed to register dock device\n");

		/* we need to be notified when dock events happen
		 * outside of the hotplug operation, since we may
		 * need to do fixups before we can hotplug.
		 */
		newfunc->nb.notifier_call = post_dock_fixups;
		if (register_dock_notifier(&newfunc->nb))
			dbg("failed to register a dock notifier");
	}

	/* install notify handler */
	if (!(newfunc->flags & FUNC_HAS_DCK)) {
		status = acpi_install_notify_handler(handle,
					     ACPI_SYSTEM_NOTIFY,
					     handle_hotplug_event_func,
					     newfunc);

		if (ACPI_FAILURE(status))
			err("failed to register interrupt notify handler\n");
	} else
		status = AE_OK;

	return status;

 err_exit:
	bridge->nr_slots--;
	bridge->slots = slot->next;
	kfree(slot);
	kfree(newfunc);

	return AE_OK;
}