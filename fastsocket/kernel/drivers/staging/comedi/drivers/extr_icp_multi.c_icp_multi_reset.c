#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int DacCmdStatus; scalar_t__ io_addr; } ;
struct TYPE_3__ {int n_aochan; } ;

/* Variables and functions */
 unsigned int DAC_ST ; 
 scalar_t__ ICP_MULTI_AO ; 
 scalar_t__ ICP_MULTI_DAC_CSR ; 
 scalar_t__ ICP_MULTI_DO ; 
 scalar_t__ ICP_MULTI_INT_EN ; 
 scalar_t__ ICP_MULTI_INT_STAT ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* this_board ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int icp_multi_reset(struct comedi_device *dev)
{
	unsigned int i;

#ifdef ICP_MULTI_EXTDEBUG
	printk("icp_multi EDBG: BGN: icp_multi_reset(...)\n");
#endif
	/*  Clear INT enables and requests */
	writew(0, devpriv->io_addr + ICP_MULTI_INT_EN);
	writew(0x00ff, devpriv->io_addr + ICP_MULTI_INT_STAT);

	if (this_board->n_aochan)
		/*  Set DACs to 0..5V range and 0V output */
		for (i = 0; i < this_board->n_aochan; i++) {
			devpriv->DacCmdStatus &= 0xfcce;

			/*  Set channel number */
			devpriv->DacCmdStatus |= (i << 8);

			/*  Output 0V */
			writew(0, devpriv->io_addr + ICP_MULTI_AO);

			/*  Set start conversion bit */
			devpriv->DacCmdStatus |= DAC_ST;

			/*  Output to command / status register */
			writew(devpriv->DacCmdStatus,
			       devpriv->io_addr + ICP_MULTI_DAC_CSR);

			/*  Delay to allow DAC time to recover */
			udelay(1);
		}
	/*  Digital outputs to 0 */
	writew(0, devpriv->io_addr + ICP_MULTI_DO);

#ifdef ICP_MULTI_EXTDEBUG
	printk("icp multi EDBG: END: icp_multi_reset(...)\n");
#endif
	return 0;
}