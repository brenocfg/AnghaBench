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
struct pci_bus {int /*<<< orphan*/  number; } ;
struct device_node {int dummy; } ;
struct HvCallPci_LoadReturn {scalar_t__ rc; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvCall3Ret16 (int /*<<< orphan*/ ,struct HvCallPci_LoadReturn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 struct device_node* find_device_node (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * hv_cfg_read_func ; 
 int /*<<< orphan*/  iseries_ds_addr (struct device_node*) ; 

__attribute__((used)) static int iSeries_pci_read_config(struct pci_bus *bus, unsigned int devfn,
		int offset, int size, u32 *val)
{
	struct device_node *node = find_device_node(bus->number, devfn);
	u64 fn;
	struct HvCallPci_LoadReturn ret;

	if (node == NULL)
		return PCIBIOS_DEVICE_NOT_FOUND;
	if (offset > 255) {
		*val = ~0;
		return PCIBIOS_BAD_REGISTER_NUMBER;
	}

	fn = hv_cfg_read_func[(size - 1) & 3];
	HvCall3Ret16(fn, &ret, iseries_ds_addr(node), offset, 0);

	if (ret.rc != 0) {
		*val = ~0;
		return PCIBIOS_DEVICE_NOT_FOUND;	/* or something */
	}

	*val = ret.value;
	return 0;
}