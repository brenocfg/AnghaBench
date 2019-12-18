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
struct pci_dev {TYPE_1__* resource; } ;
struct TYPE_2__ {unsigned long start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TRC (char*) ; 
 unsigned long PCI_BASE_ADDRESS_IO_MASK ; 
 unsigned long PCI_BASE_ADDRESS_MEM_MASK ; 
 unsigned long PCI_BASE_ADDRESS_SPACE_IO ; 

unsigned long divasa_get_pci_bar(unsigned char bus, unsigned char func,
				 int bar, void *pci_dev_handle)
{
	unsigned long ret = 0;
	struct pci_dev *dev = (struct pci_dev *) pci_dev_handle;

	if (bar < 6) {
		ret = dev->resource[bar].start;
	}

	DBG_TRC(("GOT BAR[%d]=%08x", bar, ret));

	{
		unsigned long type = (ret & 0x00000001);
		if (type & PCI_BASE_ADDRESS_SPACE_IO) {
			DBG_TRC(("  I/O"));
			ret &= PCI_BASE_ADDRESS_IO_MASK;
		} else {
			DBG_TRC(("  memory"));
			ret &= PCI_BASE_ADDRESS_MEM_MASK;
		}
		DBG_TRC(("  final=%08x", ret));
	}

	return (ret);
}