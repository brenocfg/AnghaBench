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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_ADC_Command_67xx ; 
 int /*<<< orphan*/  CAL_ADC_Status_67xx ; 
 int CSS_ADC_BUSY ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int ni_ao_win_inw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_ao_win_outw (struct comedi_device*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cs5529_command(struct comedi_device *dev, unsigned short value)
{
	static const int timeout = 100;
	int i;

	ni_ao_win_outw(dev, value, CAL_ADC_Command_67xx);
	/* give time for command to start being serially clocked into cs5529.
	 * this insures that the CSS_ADC_BUSY bit will get properly
	 * set before we exit this function.
	 */
	for (i = 0; i < timeout; i++) {
		if ((ni_ao_win_inw(dev, CAL_ADC_Status_67xx) & CSS_ADC_BUSY))
			break;
		udelay(1);
	}
/* printk("looped %i times writing command to cs5529\n", i); */
	if (i == timeout) {
		comedi_error(dev, "possible problem - never saw adc go busy?");
	}
}