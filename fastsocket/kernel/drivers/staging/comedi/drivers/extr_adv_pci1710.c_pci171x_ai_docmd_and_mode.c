#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_6__ {int ai_do; int neverending_ai; int CntrlReg; int ai_flags; int ai_eos; int ai_scans; int ai_et_CntrlReg; int ai_et; unsigned int ai_et_div1; unsigned int ai_et_div2; int /*<<< orphan*/  ai_timer1; int /*<<< orphan*/  i8254_osc_base; scalar_t__ ai_buf_ptr; scalar_t__ ai_act_scan; int /*<<< orphan*/  ai_n_chan; int /*<<< orphan*/  ai_chanlist; } ;
struct TYPE_5__ {int /*<<< orphan*/  ai_ns_min; } ;
struct TYPE_4__ {scalar_t__ cur_chan; } ;

/* Variables and functions */
 int Control_CNT0 ; 
 int Control_EXT ; 
 int Control_GATE ; 
 int Control_IRQEN ; 
 int Control_ONEFH ; 
 int Control_PACER ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 scalar_t__ PCI171x_CLRFIFO ; 
 scalar_t__ PCI171x_CLRINT ; 
 scalar_t__ PCI171x_CONTROL ; 
 int TRIG_ROUND_MASK ; 
 int TRIG_WAKE_EOS ; 
 unsigned int check_channel_list (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer (int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  setup_channel_list (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  start_pacer (struct comedi_device*,int,unsigned int,unsigned int) ; 
 TYPE_2__* this_board ; 

__attribute__((used)) static int pci171x_ai_docmd_and_mode(int mode, struct comedi_device *dev,
				     struct comedi_subdevice *s)
{
	unsigned int divisor1, divisor2;
	unsigned int seglen;

	DPRINTK("adv_pci1710 EDBG: BGN: pci171x_ai_docmd_and_mode(%d,...)\n",
		mode);
	start_pacer(dev, -1, 0, 0);	/*  stop pacer */

	seglen = check_channel_list(dev, s, devpriv->ai_chanlist,
				    devpriv->ai_n_chan);
	if (seglen < 1)
		return -EINVAL;
	setup_channel_list(dev, s, devpriv->ai_chanlist,
			   devpriv->ai_n_chan, seglen);

	outb(0, dev->iobase + PCI171x_CLRFIFO);
	outb(0, dev->iobase + PCI171x_CLRINT);

	devpriv->ai_do = mode;

	devpriv->ai_act_scan = 0;
	s->async->cur_chan = 0;
	devpriv->ai_buf_ptr = 0;
	devpriv->neverending_ai = 0;

	devpriv->CntrlReg &= Control_CNT0;
	if ((devpriv->ai_flags & TRIG_WAKE_EOS)) {	/*  don't we want wake up every scan?            devpriv->ai_eos=1; */
		devpriv->ai_eos = 1;
	} else {
		devpriv->CntrlReg |= Control_ONEFH;
		devpriv->ai_eos = 0;
	}

	if ((devpriv->ai_scans == 0) || (devpriv->ai_scans == -1)) {
		devpriv->neverending_ai = 1;
	} /* well, user want neverending */
	else {
		devpriv->neverending_ai = 0;
	}
	switch (mode) {
	case 1:
	case 2:
		if (devpriv->ai_timer1 < this_board->ai_ns_min)
			devpriv->ai_timer1 = this_board->ai_ns_min;
		devpriv->CntrlReg |= Control_PACER | Control_IRQEN;
		if (mode == 2) {
			devpriv->ai_et_CntrlReg = devpriv->CntrlReg;
			devpriv->CntrlReg &=
			    ~(Control_PACER | Control_ONEFH | Control_GATE);
			devpriv->CntrlReg |= Control_EXT;
			devpriv->ai_et = 1;
		} else {
			devpriv->ai_et = 0;
		}
		i8253_cascade_ns_to_timer(devpriv->i8254_osc_base, &divisor1,
					  &divisor2, &devpriv->ai_timer1,
					  devpriv->ai_flags & TRIG_ROUND_MASK);
		DPRINTK
		    ("adv_pci1710 EDBG: OSC base=%u div1=%u div2=%u timer=%u\n",
		     devpriv->i8254_osc_base, divisor1, divisor2,
		     devpriv->ai_timer1);
		outw(devpriv->CntrlReg, dev->iobase + PCI171x_CONTROL);
		if (mode != 2) {
			/*  start pacer */
			start_pacer(dev, mode, divisor1, divisor2);
		} else {
			devpriv->ai_et_div1 = divisor1;
			devpriv->ai_et_div2 = divisor2;
		}
		break;
	case 3:
		devpriv->CntrlReg |= Control_EXT | Control_IRQEN;
		outw(devpriv->CntrlReg, dev->iobase + PCI171x_CONTROL);
		break;
	}

	DPRINTK("adv_pci1710 EDBG: END: pci171x_ai_docmd_and_mode(...)\n");
	return 0;
}