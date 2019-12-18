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

/* Variables and functions */
#define  HCI_PCCARD 134 
#define  HCI_PCI 133 
#define  HCI_RS232 132 
#define  HCI_SDIO 131 
#define  HCI_UART 130 
#define  HCI_USB 129 
#define  HCI_VIRTUAL 128 

__attribute__((used)) static inline char *host_typetostr(int type)
{
	switch (type) {
	case HCI_VIRTUAL:
		return "VIRTUAL";
	case HCI_USB:
		return "USB";
	case HCI_PCCARD:
		return "PCCARD";
	case HCI_UART:
		return "UART";
	case HCI_RS232:
		return "RS232";
	case HCI_PCI:
		return "PCI";
	case HCI_SDIO:
		return "SDIO";
	default:
		return "UNKNOWN";
	}
}