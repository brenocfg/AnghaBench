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
struct comedi_device {int /*<<< orphan*/  minor; } ;
struct TYPE_4__ {unsigned int i8254_osc_base; } ;
struct TYPE_3__ {unsigned int ai_ns_min; unsigned int ai_pacer_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,unsigned int,unsigned int,...) ; 
 unsigned int TRIG_ROUND_NEAREST ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer (unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static void pci9118_calc_divisors(char mode, struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  unsigned int *tim1, unsigned int *tim2,
				  unsigned int flags, int chans,
				  unsigned int *div1, unsigned int *div2,
				  char usessh, unsigned int chnsshfront)
{
	DPRINTK
	    ("adl_pci9118 EDBG: BGN: pci9118_calc_divisors(%d,%d,.,%u,%u,%u,%d,.,.,,%u,%u)\n",
	     mode, dev->minor, *tim1, *tim2, flags, chans, usessh, chnsshfront);
	switch (mode) {
	case 1:
	case 4:
		if (*tim2 < this_board->ai_ns_min)
			*tim2 = this_board->ai_ns_min;
		i8253_cascade_ns_to_timer(devpriv->i8254_osc_base, div1, div2,
					  tim2, flags & TRIG_ROUND_NEAREST);
		DPRINTK("OSC base=%u div1=%u div2=%u timer1=%u\n",
			devpriv->i8254_osc_base, *div1, *div2, *tim1);
		break;
	case 2:
		if (*tim2 < this_board->ai_ns_min)
			*tim2 = this_board->ai_ns_min;
		DPRINTK("1 div1=%u div2=%u timer1=%u timer2=%u\n", *div1, *div2,
			*tim1, *tim2);
		*div1 = *tim2 / devpriv->i8254_osc_base;	/*  convert timer (burst) */
		DPRINTK("2 div1=%u div2=%u timer1=%u timer2=%u\n", *div1, *div2,
			*tim1, *tim2);
		if (*div1 < this_board->ai_pacer_min)
			*div1 = this_board->ai_pacer_min;
		DPRINTK("3 div1=%u div2=%u timer1=%u timer2=%u\n", *div1, *div2,
			*tim1, *tim2);
		*div2 = *tim1 / devpriv->i8254_osc_base;	/*  scan timer */
		DPRINTK("4 div1=%u div2=%u timer1=%u timer2=%u\n", *div1, *div2,
			*tim1, *tim2);
		*div2 = *div2 / *div1;	/*  major timer is c1*c2 */
		DPRINTK("5 div1=%u div2=%u timer1=%u timer2=%u\n", *div1, *div2,
			*tim1, *tim2);
		if (*div2 < chans)
			*div2 = chans;
		DPRINTK("6 div1=%u div2=%u timer1=%u timer2=%u\n", *div1, *div2,
			*tim1, *tim2);

		*tim2 = *div1 * devpriv->i8254_osc_base;	/*  real convert timer */

		if (usessh & (chnsshfront == 0))	/*  use BSSH signal */
			if (*div2 < (chans + 2))
				*div2 = chans + 2;

		DPRINTK("7 div1=%u div2=%u timer1=%u timer2=%u\n", *div1, *div2,
			*tim1, *tim2);
		*tim1 = *div1 * *div2 * devpriv->i8254_osc_base;
		DPRINTK("OSC base=%u div1=%u div2=%u timer1=%u timer2=%u\n",
			devpriv->i8254_osc_base, *div1, *div2, *tim1, *tim2);
		break;
	}
	DPRINTK("adl_pci9118 EDBG: END: pci9118_calc_divisors(%u,%u)\n",
		*div1, *div2);
}