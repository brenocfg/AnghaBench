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
struct pci_dev {int device; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_SERVERWORKS_CSB5IDE 131 
#define  PCI_DEVICE_ID_SERVERWORKS_CSB6IDE 130 
#define  PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2 129 
#define  PCI_DEVICE_ID_SERVERWORKS_HT1000IDE 128 

__attribute__((used)) static u8 svwks_csb_check (struct pci_dev *dev)
{
	switch (dev->device) {
		case PCI_DEVICE_ID_SERVERWORKS_CSB5IDE:
		case PCI_DEVICE_ID_SERVERWORKS_CSB6IDE:
		case PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2:
		case PCI_DEVICE_ID_SERVERWORKS_HT1000IDE:
			return 1;
		default:
			break;
	}
	return 0;
}