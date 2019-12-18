#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t secondary_status; char* control; } ;
struct TYPE_7__ {size_t lower; char* upper; } ;
struct TYPE_6__ {int slot; size_t vendor_id; char* device_id; int /*<<< orphan*/ * class_code; int /*<<< orphan*/  secondary_bus; int /*<<< orphan*/  function; int /*<<< orphan*/  device; int /*<<< orphan*/  bus; int /*<<< orphan*/  segment; } ;
struct TYPE_5__ {size_t major; char* minor; } ;
struct cper_sec_pcie {int validation_bits; size_t port_type; size_t command; char* status; TYPE_4__ bridge; TYPE_3__ serial_number; TYPE_2__ device_id; TYPE_1__ version; } ;
struct acpi_hest_generic_data {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int CPER_PCIE_SLOT_SHIFT ; 
 int CPER_PCIE_VALID_BRIDGE_CONTROL_STATUS ; 
 int CPER_PCIE_VALID_COMMAND_STATUS ; 
 int CPER_PCIE_VALID_DEVICE_ID ; 
 int CPER_PCIE_VALID_PORT_TYPE ; 
 int CPER_PCIE_VALID_SERIAL_NUMBER ; 
 int CPER_PCIE_VALID_VERSION ; 
 char** cper_pcie_port_type_strs ; 
 int /*<<< orphan*/  printk (char*,char const*,size_t,...) ; 

__attribute__((used)) static void cper_print_pcie(const char *pfx, const struct cper_sec_pcie *pcie,
			    const struct acpi_hest_generic_data *gdata)
{
	if (pcie->validation_bits & CPER_PCIE_VALID_PORT_TYPE)
		printk("%s""port_type: %d, %s\n", pfx, pcie->port_type,
		       pcie->port_type < ARRAY_SIZE(cper_pcie_port_type_strs) ?
		       cper_pcie_port_type_strs[pcie->port_type] : "unknown");
	if (pcie->validation_bits & CPER_PCIE_VALID_VERSION)
		printk("%s""version: %d.%d\n", pfx,
		       pcie->version.major, pcie->version.minor);
	if (pcie->validation_bits & CPER_PCIE_VALID_COMMAND_STATUS)
		printk("%s""command: 0x%04x, status: 0x%04x\n", pfx,
		       pcie->command, pcie->status);
	if (pcie->validation_bits & CPER_PCIE_VALID_DEVICE_ID) {
		const __u8 *p;
		printk("%s""device_id: %04x:%02x:%02x.%x\n", pfx,
		       pcie->device_id.segment, pcie->device_id.bus,
		       pcie->device_id.device, pcie->device_id.function);
		printk("%s""slot: %d\n", pfx,
		       pcie->device_id.slot >> CPER_PCIE_SLOT_SHIFT);
		printk("%s""secondary_bus: 0x%02x\n", pfx,
		       pcie->device_id.secondary_bus);
		printk("%s""vendor_id: 0x%04x, device_id: 0x%04x\n", pfx,
		       pcie->device_id.vendor_id, pcie->device_id.device_id);
		p = pcie->device_id.class_code;
		printk("%s""class_code: %02x%02x%02x\n", pfx, p[0], p[1], p[2]);
	}
	if (pcie->validation_bits & CPER_PCIE_VALID_SERIAL_NUMBER)
		printk("%s""serial number: 0x%04x, 0x%04x\n", pfx,
		       pcie->serial_number.lower, pcie->serial_number.upper);
	if (pcie->validation_bits & CPER_PCIE_VALID_BRIDGE_CONTROL_STATUS)
		printk(
	"%s""bridge: secondary_status: 0x%04x, control: 0x%04x\n",
	pfx, pcie->bridge.secondary_status, pcie->bridge.control);
}