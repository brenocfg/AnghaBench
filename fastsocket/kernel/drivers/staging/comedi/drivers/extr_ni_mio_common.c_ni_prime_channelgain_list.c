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
struct TYPE_2__ {int (* stc_readw ) (struct comedi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_FIFO_Clear ; 
 int AI_CONVERT_Pulse ; 
 int /*<<< orphan*/  AI_Command_1_Register ; 
 int AI_FIFO_Empty_St ; 
 int /*<<< orphan*/  AI_Status_1_Register ; 
 int NI_TIMEOUT ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void ni_prime_channelgain_list(struct comedi_device *dev)
{
	int i;
	devpriv->stc_writew(dev, AI_CONVERT_Pulse, AI_Command_1_Register);
	for (i = 0; i < NI_TIMEOUT; ++i) {
		if (!(devpriv->stc_readw(dev,
					 AI_Status_1_Register) &
		      AI_FIFO_Empty_St)) {
			devpriv->stc_writew(dev, 1, ADC_FIFO_Clear);
			return;
		}
		udelay(1);
	}
	printk("ni_mio_common: timeout loading channel/gain list\n");
}