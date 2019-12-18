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
struct TYPE_2__ {scalar_t__ dac; int /*<<< orphan*/  dac_cal1_bits; } ;

/* Variables and functions */
 scalar_t__ DACALIBRATION1 ; 
 int /*<<< orphan*/  SERIAL_IN_BIT ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cb_pcidda_serial_out(struct comedi_device *dev, unsigned int value,
				 unsigned int num_bits)
{
	int i;

	for (i = 1; i <= num_bits; i++) {
		/*  send bits most significant bit first */
		if (value & (1 << (num_bits - i)))
			devpriv->dac_cal1_bits |= SERIAL_IN_BIT;
		else
			devpriv->dac_cal1_bits &= ~SERIAL_IN_BIT;
		outw_p(devpriv->dac_cal1_bits, devpriv->dac + DACALIBRATION1);
	}
}