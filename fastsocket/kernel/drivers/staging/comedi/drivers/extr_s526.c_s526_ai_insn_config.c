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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned int s526_ai_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_REG (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ISR_ADC_DONE ; 
 int /*<<< orphan*/  REG_IER ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s526_ai_insn_config(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	int result = -EINVAL;

	if (insn->n < 1)
		return result;

	result = insn->n;

	/* data[0] : channels was set in relevant bits.
	   data[1] : delay
	 */
	/* COMMENT: abbotti 2008-07-24: I don't know why you'd want to
	 * enable channels here.  The channel should be enabled in the
	 * INSN_READ handler. */

	/*  Enable ADC interrupt */
	outw(ISR_ADC_DONE, ADDR_REG(REG_IER));
/* printk("s526: ADC current value: 0x%04x\n", inw(ADDR_REG(REG_ADC))); */
	devpriv->s526_ai_config = (data[0] & 0x3FF) << 5;
	if (data[1] > 0)
		devpriv->s526_ai_config |= 0x8000;	/* set the delay */

	devpriv->s526_ai_config |= 0x0001;	/*  ADC start bit. */

	return result;
}