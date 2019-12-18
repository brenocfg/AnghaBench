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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct acpiphp_ioapic {int /*<<< orphan*/  list; struct pci_dev* dev; int /*<<< orphan*/  gsi_base; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 unsigned long long ACPI_STA_ALL ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_CTRL_DEPTH ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_register_ioapic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* get_apic_pci_info (int /*<<< orphan*/ ) ; 
 scalar_t__ get_gsi_base (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioapic_list ; 
 int /*<<< orphan*/  ioapic_list_lock ; 
 int /*<<< orphan*/  kfree (struct acpiphp_ioapic*) ; 
 struct acpiphp_ioapic* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static acpi_status
ioapic_add(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	acpi_status status;
	unsigned long long sta;
	acpi_handle tmp;
	struct pci_dev *pdev;
	u32 gsi_base;
	u64 phys_addr;
	struct acpiphp_ioapic *ioapic;

	/* Evaluate _STA if present */
	status = acpi_evaluate_integer(handle, "_STA", NULL, &sta);
	if (ACPI_SUCCESS(status) && sta != ACPI_STA_ALL)
		return AE_CTRL_DEPTH;

	/* Scan only PCI bus scope */
	status = acpi_get_handle(handle, "_HID", &tmp);
	if (ACPI_SUCCESS(status))
		return AE_CTRL_DEPTH;

	if (get_gsi_base(handle, &gsi_base))
		return AE_OK;

	ioapic = kmalloc(sizeof(*ioapic), GFP_KERNEL);
	if (!ioapic)
		return AE_NO_MEMORY;

	pdev = get_apic_pci_info(handle);
	if (!pdev)
		goto exit_kfree;

	if (pci_enable_device(pdev))
		goto exit_pci_dev_put;

	pci_set_master(pdev);

	if (pci_request_region(pdev, 0, "I/O APIC(acpiphp)"))
		goto exit_pci_disable_device;

	phys_addr = pci_resource_start(pdev, 0);
	if (acpi_register_ioapic(handle, phys_addr, gsi_base))
		goto exit_pci_release_region;

	ioapic->gsi_base = gsi_base;
	ioapic->dev = pdev;
	spin_lock(&ioapic_list_lock);
	list_add_tail(&ioapic->list, &ioapic_list);
	spin_unlock(&ioapic_list_lock);

	return AE_OK;

 exit_pci_release_region:
	pci_release_region(pdev, 0);
 exit_pci_disable_device:
	pci_disable_device(pdev);
 exit_pci_dev_put:
	pci_dev_put(pdev);
 exit_kfree:
	kfree(ioapic);

	return AE_OK;
}