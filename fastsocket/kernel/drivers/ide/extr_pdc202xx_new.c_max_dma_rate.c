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
#define  PCI_DEVICE_ID_PROMISE_20268 134 
#define  PCI_DEVICE_ID_PROMISE_20269 133 
#define  PCI_DEVICE_ID_PROMISE_20270 132 
#define  PCI_DEVICE_ID_PROMISE_20271 131 
#define  PCI_DEVICE_ID_PROMISE_20275 130 
#define  PCI_DEVICE_ID_PROMISE_20276 129 
#define  PCI_DEVICE_ID_PROMISE_20277 128 

__attribute__((used)) static u8 max_dma_rate(struct pci_dev *pdev)
{
	u8 mode;

	switch(pdev->device) {
		case PCI_DEVICE_ID_PROMISE_20277:
		case PCI_DEVICE_ID_PROMISE_20276:
		case PCI_DEVICE_ID_PROMISE_20275:
		case PCI_DEVICE_ID_PROMISE_20271:
		case PCI_DEVICE_ID_PROMISE_20269:
			mode = 4;
			break;
		case PCI_DEVICE_ID_PROMISE_20270:
		case PCI_DEVICE_ID_PROMISE_20268:
			mode = 3;
			break;
		default:
			return 0;
	}

	return mode;
}