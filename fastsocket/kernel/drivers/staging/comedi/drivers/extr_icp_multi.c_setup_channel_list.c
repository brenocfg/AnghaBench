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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int act_chanlist_len; int AdcCmdStatus; int /*<<< orphan*/ * act_chanlist; scalar_t__ io_addr; scalar_t__ act_chanlist_pos; } ;
struct TYPE_3__ {unsigned int* rangecode; } ;

/* Variables and functions */
 unsigned int ADC_DI ; 
 scalar_t__ AREF_DIFF ; 
 scalar_t__ CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 size_t CR_RANGE (unsigned int) ; 
 scalar_t__ ICP_MULTI_ADC_CSR ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  printk (char*,unsigned int,...) ; 
 TYPE_1__* this_board ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static void setup_channel_list(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       unsigned int *chanlist, unsigned int n_chan)
{
	unsigned int i, range, chanprog;
	unsigned int diff;

#ifdef ICP_MULTI_EXTDEBUG
	printk("icp multi EDBG:  setup_channel_list(...,%d)\n", n_chan);
#endif
	devpriv->act_chanlist_len = n_chan;
	devpriv->act_chanlist_pos = 0;

	for (i = 0; i < n_chan; i++) {
		/*  Get channel */
		chanprog = CR_CHAN(chanlist[i]);

		/*  Determine if it is a differential channel (Bit 15  = 1) */
		if (CR_AREF(chanlist[i]) == AREF_DIFF) {
			diff = 1;
			chanprog &= 0x0007;
		} else {
			diff = 0;
			chanprog &= 0x000f;
		}

		/*  Clear channel, range and input mode bits in A/D command/status register */
		devpriv->AdcCmdStatus &= 0xf00f;

		/*  Set channel number and differential mode status bit */
		if (diff) {
			/*  Set channel number, bits 9-11 & mode, bit 6 */
			devpriv->AdcCmdStatus |= (chanprog << 9);
			devpriv->AdcCmdStatus |= ADC_DI;
		} else
			/*  Set channel number, bits 8-11 */
			devpriv->AdcCmdStatus |= (chanprog << 8);

		/*  Get range for current channel */
		range = this_board->rangecode[CR_RANGE(chanlist[i])];
		/*  Set range. bits 4-5 */
		devpriv->AdcCmdStatus |= range;

		/* Output channel, range, mode to ICP Multi */
		writew(devpriv->AdcCmdStatus,
		       devpriv->io_addr + ICP_MULTI_ADC_CSR);

#ifdef ICP_MULTI_EXTDEBUG
		printk("GS: %2d. [%4x]=%4x %4x\n", i, chanprog, range,
		       devpriv->act_chanlist[i]);
#endif
	}

}