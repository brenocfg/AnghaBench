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
struct comedi_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ io_addr; } ;

/* Variables and functions */
#define  ADC_READY 135 
#define  CIE0 134 
#define  CIE1 133 
#define  CIE2 132 
#define  CIE3 131 
#define  DAC_READY 130 
#define  DIN_STATUS 129 
#define  DOUT_ERROR 128 
 scalar_t__ ICP_MULTI_INT_STAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int Status_IRQ ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static irqreturn_t interrupt_service_icp_multi(int irq, void *d)
{
	struct comedi_device *dev = d;
	int int_no;

#ifdef ICP_MULTI_EXTDEBUG
	printk("icp multi EDBG: BGN: interrupt_service_icp_multi(%d,...)\n",
	       irq);
#endif

	/*  Is this interrupt from our board? */
	int_no = readw(devpriv->io_addr + ICP_MULTI_INT_STAT) & Status_IRQ;
	if (!int_no)
		/*  No, exit */
		return IRQ_NONE;

#ifdef ICP_MULTI_EXTDEBUG
	printk("icp multi EDBG: interrupt_service_icp_multi() ST: %4x\n",
	       readw(devpriv->io_addr + ICP_MULTI_INT_STAT));
#endif

	/*  Determine which interrupt is active & handle it */
	switch (int_no) {
	case ADC_READY:
		break;
	case DAC_READY:
		break;
	case DOUT_ERROR:
		break;
	case DIN_STATUS:
		break;
	case CIE0:
		break;
	case CIE1:
		break;
	case CIE2:
		break;
	case CIE3:
		break;
	default:
		break;

	}

#ifdef ICP_MULTI_EXTDEBUG
	printk("icp multi EDBG: END: interrupt_service_icp_multi(...)\n");
#endif
	return IRQ_HANDLED;
}