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
struct cx23885_dev {int board; int /*<<< orphan*/  sd_ir; } ;

/* Variables and functions */
#define  CX23885_BOARD_HAUPPAUGE_HVR1250 131 
#define  CX23885_BOARD_HAUPPAUGE_HVR1290 130 
#define  CX23885_BOARD_HAUPPAUGE_HVR1850 129 
#define  CX23885_BOARD_TEVII_S470 128 
 int /*<<< orphan*/  PCI_MSK_AV_CORE ; 
 int /*<<< orphan*/  PCI_MSK_IR ; 
 int /*<<< orphan*/  cx23885_irq_add_enable (struct cx23885_dev*,int /*<<< orphan*/ ) ; 

void cx23885_ir_pci_int_enable(struct cx23885_dev *dev)
{
	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
		if (dev->sd_ir)
			cx23885_irq_add_enable(dev, PCI_MSK_IR);
		break;
	case CX23885_BOARD_TEVII_S470:
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
		if (dev->sd_ir)
			cx23885_irq_add_enable(dev, PCI_MSK_AV_CORE);
		break;
	}
}