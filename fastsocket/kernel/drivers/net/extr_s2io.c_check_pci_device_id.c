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
typedef  int u16 ;

/* Variables and functions */
 int PCI_ANY_ID ; 
#define  PCI_DEVICE_ID_HERC_UNI 131 
#define  PCI_DEVICE_ID_HERC_WIN 130 
#define  PCI_DEVICE_ID_S2IO_UNI 129 
#define  PCI_DEVICE_ID_S2IO_WIN 128 
 int XFRAME_II_DEVICE ; 
 int XFRAME_I_DEVICE ; 

__attribute__((used)) static u16 check_pci_device_id(u16 id)
{
	switch (id) {
	case PCI_DEVICE_ID_HERC_WIN:
	case PCI_DEVICE_ID_HERC_UNI:
		return XFRAME_II_DEVICE;
	case PCI_DEVICE_ID_S2IO_UNI:
	case PCI_DEVICE_ID_S2IO_WIN:
		return XFRAME_I_DEVICE;
	default:
		return PCI_ANY_ID;
	}
}