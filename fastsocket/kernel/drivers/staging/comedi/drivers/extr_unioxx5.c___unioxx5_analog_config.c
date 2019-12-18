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
struct unioxx5_subd_priv {int* usp_prev_cn_val; scalar_t__ usp_iobase; } ;

/* Variables and functions */
 int __unioxx5_define_chan_offset (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void __unioxx5_analog_config(struct unioxx5_subd_priv *usp, int channel)
{
	int chan_a, chan_b, conf, channel_offset;

	channel_offset = __unioxx5_define_chan_offset(channel);
	conf = usp->usp_prev_cn_val[channel_offset - 1];
	chan_a = chan_b = 1;

	/* setting channel A and channel B mask */
	if (channel % 2 == 0) {
		chan_a <<= channel & 0x07;
		chan_b <<= (channel + 1) & 0x07;
	} else {
		chan_a <<= (channel - 1) & 0x07;
		chan_b <<= channel & 0x07;
	}

	conf |= chan_a;		/* even channel ot output */
	conf &= ~chan_b;	/* odd channel to input */

	outb(1, usp->usp_iobase + 0);
	outb(conf, usp->usp_iobase + channel_offset);
	outb(0, usp->usp_iobase + 0);

	usp->usp_prev_cn_val[channel_offset - 1] = conf;
}