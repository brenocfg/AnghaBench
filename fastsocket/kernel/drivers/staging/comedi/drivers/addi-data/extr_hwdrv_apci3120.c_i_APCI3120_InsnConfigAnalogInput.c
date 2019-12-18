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
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {unsigned int ui_EocEosConversionTime; unsigned int b_InterruptMode; unsigned int ui_AiNbrofChannels; unsigned int* ui_AiChannelList; void* b_EocEosInterrupt; } ;
struct TYPE_3__ {scalar_t__ i_NbrAiChannel; } ;

/* Variables and functions */
 void* APCI3120_DISABLE ; 
 void* APCI3120_ENABLE ; 
 unsigned int APCI3120_EOC_MODE ; 
 unsigned int APCI3120_EOS_MODE ; 
 scalar_t__ CR_CHAN (unsigned int) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* this_board ; 

int i_APCI3120_InsnConfigAnalogInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int i;

	if ((data[0] != APCI3120_EOC_MODE) && (data[0] != APCI3120_EOS_MODE))
		return -1;

	/*  Check for Conversion time to be added ?? */
	devpriv->ui_EocEosConversionTime = data[2];

	if (data[0] == APCI3120_EOS_MODE) {

		/* Test the number of the channel */
		for (i = 0; i < data[3]; i++) {

			if (CR_CHAN(data[4 + i]) >= this_board->i_NbrAiChannel) {
				printk("bad channel list\n");
				return -2;
			}
		}

		devpriv->b_InterruptMode = APCI3120_EOS_MODE;

		if (data[1]) {
			devpriv->b_EocEosInterrupt = APCI3120_ENABLE;
		} else
			devpriv->b_EocEosInterrupt = APCI3120_DISABLE;
		/*  Copy channel list and Range List to devpriv */

		devpriv->ui_AiNbrofChannels = data[3];
		for (i = 0; i < devpriv->ui_AiNbrofChannels; i++) {
			devpriv->ui_AiChannelList[i] = data[4 + i];
		}

	} else			/*  EOC */
	{
		devpriv->b_InterruptMode = APCI3120_EOC_MODE;
		if (data[1]) {
			devpriv->b_EocEosInterrupt = APCI3120_ENABLE;
		} else {
			devpriv->b_EocEosInterrupt = APCI3120_DISABLE;
		}
	}

	return insn->n;
}