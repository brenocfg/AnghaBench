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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned char range_correction; unsigned char old_chan_reg; unsigned char old_gain_reg; int /*<<< orphan*/  max_812_ai_mode0_rangewait; scalar_t__ use_diff; scalar_t__ use_MPC; } ;

/* Variables and functions */
 unsigned char CR_CHAN (unsigned int) ; 
 unsigned char CR_RANGE (unsigned int) ; 
 scalar_t__ PCL812_GAIN ; 
 scalar_t__ PCL812_MUX ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_range_channel(struct comedi_device *dev,
				struct comedi_subdevice *s,
				unsigned int rangechan, char wait)
{
	unsigned char chan_reg = CR_CHAN(rangechan);	/*  normal board */
	unsigned char gain_reg = CR_RANGE(rangechan) + devpriv->range_correction;	/*  gain index */

	if ((chan_reg == devpriv->old_chan_reg)
	    && (gain_reg == devpriv->old_gain_reg))
		return;		/*  we can return, no change */

	devpriv->old_chan_reg = chan_reg;
	devpriv->old_gain_reg = gain_reg;

	if (devpriv->use_MPC) {
		if (devpriv->use_diff) {
			chan_reg = chan_reg | 0x30;	/*  DIFF inputs */
		} else {
			if (chan_reg & 0x80) {
				chan_reg = chan_reg | 0x20;	/*  SE inputs 8-15 */
			} else {
				chan_reg = chan_reg | 0x10;	/*  SE inputs 0-7 */
			}
		}
	}

	outb(chan_reg, dev->iobase + PCL812_MUX);	/* select channel */
	outb(gain_reg, dev->iobase + PCL812_GAIN);	/* select gain */

	if (wait) {
		udelay(devpriv->max_812_ai_mode0_rangewait);	/*  XXX this depends on selected range and can be very long for some high gain ranges! */
	}
}