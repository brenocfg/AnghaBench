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
struct daqboard2000_hw {int refDacs; int dacControl; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {struct daqboard2000_hw* daq; } ;

/* Variables and functions */
 int DAQBOARD2000_NegRefDacSelect ; 
 int DAQBOARD2000_PosRefDacSelect ; 
 int DAQBOARD2000_RefBusy ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void daqboard2000_activateReferenceDacs(struct comedi_device *dev)
{
	struct daqboard2000_hw *fpga = devpriv->daq;
	int timeout;

	/*  Set the + reference dac value in the FPGA */
	fpga->refDacs = 0x80 | DAQBOARD2000_PosRefDacSelect;
	for (timeout = 0; timeout < 20; timeout++) {
		if ((fpga->dacControl & DAQBOARD2000_RefBusy) == 0) {
			break;
		}
		udelay(2);
	}
/*  printk("DAQBOARD2000_PosRefDacSelect %d\n", timeout);*/

	/*  Set the - reference dac value in the FPGA */
	fpga->refDacs = 0x80 | DAQBOARD2000_NegRefDacSelect;
	for (timeout = 0; timeout < 20; timeout++) {
		if ((fpga->dacControl & DAQBOARD2000_RefBusy) == 0) {
			break;
		}
		udelay(2);
	}
/*  printk("DAQBOARD2000_NegRefDacSelect %d\n", timeout);*/
}