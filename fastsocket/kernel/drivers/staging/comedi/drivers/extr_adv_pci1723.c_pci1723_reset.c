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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int* ao_data; int* da_range; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 scalar_t__ PCI1723_CHANGE_CHA_OUTPUT_TYPE_STROBE ; 
 scalar_t__ PCI1723_DA (int) ; 
 scalar_t__ PCI1723_RANGE_CALIBRATION_MODE ; 
 scalar_t__ PCI1723_SYN_SET ; 
 scalar_t__ PCI1723_SYN_STROBE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int pci1723_reset(struct comedi_device *dev)
{
	int i;
	DPRINTK("adv_pci1723 EDBG: BGN: pci1723_reset(...)\n");

	outw(0x01, dev->iobase + PCI1723_SYN_SET);	/*  set synchronous output mode */

	for (i = 0; i < 8; i++) {
		/*  set all outputs to 0V */
		devpriv->ao_data[i] = 0x8000;
		outw(devpriv->ao_data[i], dev->iobase + PCI1723_DA(i));
		/*  set all ranges to +/- 10V */
		devpriv->da_range[i] = 0;
		outw(((devpriv->da_range[i] << 4) | i),
		     PCI1723_RANGE_CALIBRATION_MODE);
	}

	outw(0, dev->iobase + PCI1723_CHANGE_CHA_OUTPUT_TYPE_STROBE);	/*  update ranges */
	outw(0, dev->iobase + PCI1723_SYN_STROBE);	/*  update outputs */

	/*  set asynchronous output mode */
	outw(0, dev->iobase + PCI1723_SYN_SET);

	DPRINTK("adv_pci1723 EDBG: END: pci1723_reset(...)\n");
	return 0;
}