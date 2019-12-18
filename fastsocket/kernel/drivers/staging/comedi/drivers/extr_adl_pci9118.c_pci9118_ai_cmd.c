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
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  minor; } ;
struct comedi_cmd {int flags; int chanlist_len; int scan_end_arg; scalar_t__ start_src; scalar_t__ stop_src; scalar_t__ convert_src; scalar_t__ scan_begin_src; unsigned int convert_arg; scalar_t__ scan_begin_arg; scalar_t__ stop_arg; int /*<<< orphan*/  start_arg; int /*<<< orphan*/  chanlist; } ;
struct TYPE_6__ {int ai_flags; int ai_n_chan; int ai_n_scanlen; int ai_timer2; int ai_add_front; int ai_add_back; int ai_maskerr; int ai_neverending; int usessh; int usedma; unsigned int softsshdelay; int ai_n_realscanlen; int ai_do; int AdControlReg; int AdFunctionReg; scalar_t__ ai_buf_ptr; scalar_t__ ai_act_dmapos; scalar_t__ ai_act_scan; scalar_t__ ai_timer1; int /*<<< orphan*/  ai_divisor2; int /*<<< orphan*/  ai_divisor1; scalar_t__ useeoshandle; int /*<<< orphan*/  ai_chanlist; scalar_t__ master; int /*<<< orphan*/  ai12_startstop; scalar_t__ ai_scans; int /*<<< orphan*/  ai_inttrig_start; int /*<<< orphan*/  ai_data_len; int /*<<< orphan*/  ai_data; } ;
struct TYPE_5__ {unsigned int ai_ns_min; } ;
struct TYPE_4__ {scalar_t__ cur_chan; int /*<<< orphan*/  inttrig; int /*<<< orphan*/  prealloc_bufsz; int /*<<< orphan*/  prealloc_buf; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int AdFunction_PDTrg ; 
 int AdFunction_PETrg ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ PCI9118_ADCNTRL ; 
 scalar_t__ PCI9118_ADFUNC ; 
 scalar_t__ PCI9118_ADSTAT ; 
 scalar_t__ PCI9118_DELFIFO ; 
 scalar_t__ PCI9118_INTSRC ; 
 int /*<<< orphan*/  START_AI_EXT ; 
 int /*<<< orphan*/  START_AI_INT ; 
 int /*<<< orphan*/  STOP_AI_EXT ; 
 int /*<<< orphan*/  STOP_AI_INT ; 
 scalar_t__ TRIG_COUNT ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_INT ; 
 scalar_t__ TRIG_NONE ; 
 scalar_t__ TRIG_NOW ; 
 scalar_t__ TRIG_TIMER ; 
 int TRIG_WAKE_EOS ; 
 int /*<<< orphan*/  check_channel_list (struct comedi_device*,struct comedi_subdevice*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int pci9118_ai_docmd_dma (struct comedi_device*,struct comedi_subdevice*) ; 
 int pci9118_ai_docmd_sampl (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci9118_ai_inttrig ; 
 int /*<<< orphan*/  pci9118_calc_divisors (int,struct comedi_device*,struct comedi_subdevice*,scalar_t__*,int*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  setup_channel_list (struct comedi_device*,struct comedi_subdevice*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  start_pacer (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* this_board ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pci9118_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int addchans = 0;
	int ret = 0;

	DPRINTK("adl_pci9118 EDBG: BGN: pci9118_ai_cmd(%d,)\n", dev->minor);
	devpriv->ai12_startstop = 0;
	devpriv->ai_flags = cmd->flags;
	devpriv->ai_n_chan = cmd->chanlist_len;
	devpriv->ai_n_scanlen = cmd->scan_end_arg;
	devpriv->ai_chanlist = cmd->chanlist;
	devpriv->ai_data = s->async->prealloc_buf;
	devpriv->ai_data_len = s->async->prealloc_bufsz;
	devpriv->ai_timer1 = 0;
	devpriv->ai_timer2 = 0;
	devpriv->ai_add_front = 0;
	devpriv->ai_add_back = 0;
	devpriv->ai_maskerr = 0x10e;

	/*  prepare for start/stop conditions */
	if (cmd->start_src == TRIG_EXT)
		devpriv->ai12_startstop |= START_AI_EXT;
	if (cmd->stop_src == TRIG_EXT) {
		devpriv->ai_neverending = 1;
		devpriv->ai12_startstop |= STOP_AI_EXT;
	}
	if (cmd->start_src == TRIG_INT) {
		devpriv->ai12_startstop |= START_AI_INT;
		devpriv->ai_inttrig_start = cmd->start_arg;
		s->async->inttrig = pci9118_ai_inttrig;
	}
#if 0
	if (cmd->stop_src == TRIG_INT) {
		devpriv->ai_neverending = 1;
		devpriv->ai12_startstop |= STOP_AI_INT;
	}
#endif
	if (cmd->stop_src == TRIG_NONE)
		devpriv->ai_neverending = 1;
	if (cmd->stop_src == TRIG_COUNT) {
		devpriv->ai_scans = cmd->stop_arg;
		devpriv->ai_neverending = 0;
	} else {
		devpriv->ai_scans = 0;
	}

	/*  use sample&hold signal? */
	if (cmd->convert_src == TRIG_NOW) {
		devpriv->usessh = 1;
	} /*  yes */
	else {
		devpriv->usessh = 0;
	}			/*  no */

	DPRINTK("1 neverending=%d scans=%u usessh=%d ai_startstop=0x%2x\n",
		devpriv->ai_neverending, devpriv->ai_scans, devpriv->usessh,
		devpriv->ai12_startstop);

	/*  use additional sample at end of every scan to satisty DMA 32 bit transfer? */
	devpriv->ai_add_front = 0;
	devpriv->ai_add_back = 0;
	devpriv->useeoshandle = 0;
	if (devpriv->master) {
		devpriv->usedma = 1;
		if ((cmd->flags & TRIG_WAKE_EOS) &&
		    (devpriv->ai_n_scanlen == 1)) {
			if (cmd->convert_src == TRIG_NOW) {
				devpriv->ai_add_back = 1;
			}
			if (cmd->convert_src == TRIG_TIMER) {
				devpriv->usedma = 0;	/*  use INT transfer if scanlist have only one channel */
			}
		}
		if ((cmd->flags & TRIG_WAKE_EOS) &&
		    (devpriv->ai_n_scanlen & 1) &&
		    (devpriv->ai_n_scanlen > 1)) {
			if (cmd->scan_begin_src == TRIG_FOLLOW) {
				/* vpriv->useeoshandle=1; // change DMA transfer block to fit EOS on every second call */
				devpriv->usedma = 0;	/*  XXX maybe can be corrected to use 16 bit DMA */
			} else {	/*  well, we must insert one sample to end of EOS to meet 32 bit transfer */
				devpriv->ai_add_back = 1;
			}
		}
	} else {		/*  interrupt transfer don't need any correction */
		devpriv->usedma = 0;
	}

	/*  we need software S&H signal? It add  two samples before every scan as minimum */
	if (devpriv->usessh && devpriv->softsshdelay) {
		devpriv->ai_add_front = 2;
		if ((devpriv->usedma == 1) && (devpriv->ai_add_back == 1)) {	/*  move it to front */
			devpriv->ai_add_front++;
			devpriv->ai_add_back = 0;
		}
		if (cmd->convert_arg < this_board->ai_ns_min)
			cmd->convert_arg = this_board->ai_ns_min;
		addchans = devpriv->softsshdelay / cmd->convert_arg;
		if (devpriv->softsshdelay % cmd->convert_arg)
			addchans++;
		if (addchans > (devpriv->ai_add_front - 1)) {	/*  uff, still short :-( */
			devpriv->ai_add_front = addchans + 1;
			if (devpriv->usedma == 1)
				if ((devpriv->ai_add_front +
				     devpriv->ai_n_chan +
				     devpriv->ai_add_back) & 1)
					devpriv->ai_add_front++;	/*  round up to 32 bit */
		}
	}
	/*  well, we now know what must be all added */
	devpriv->ai_n_realscanlen =	/*  what we must take from card in real to have ai_n_scanlen on output? */
	    (devpriv->ai_add_front + devpriv->ai_n_chan +
	     devpriv->ai_add_back) * (devpriv->ai_n_scanlen /
				      devpriv->ai_n_chan);

	DPRINTK("2 usedma=%d realscan=%d af=%u n_chan=%d ab=%d n_scanlen=%d\n",
		devpriv->usedma,
		devpriv->ai_n_realscanlen, devpriv->ai_add_front,
		devpriv->ai_n_chan, devpriv->ai_add_back,
		devpriv->ai_n_scanlen);

	/*  check and setup channel list */
	if (!check_channel_list(dev, s, devpriv->ai_n_chan,
				devpriv->ai_chanlist, devpriv->ai_add_front,
				devpriv->ai_add_back))
		return -EINVAL;
	if (!setup_channel_list(dev, s, devpriv->ai_n_chan,
				devpriv->ai_chanlist, 0, devpriv->ai_add_front,
				devpriv->ai_add_back, devpriv->usedma,
				devpriv->useeoshandle))
		return -EINVAL;

	/*  compute timers settings */
	/*  simplest way, fr=4Mhz/(tim1*tim2), channel manipulation without timers effect */
	if (((cmd->scan_begin_src == TRIG_FOLLOW) || (cmd->scan_begin_src == TRIG_EXT) || (cmd->scan_begin_src == TRIG_INT)) && (cmd->convert_src == TRIG_TIMER)) {	/*  both timer is used for one time */
		if (cmd->scan_begin_src == TRIG_EXT) {
			devpriv->ai_do = 4;
		} else {
			devpriv->ai_do = 1;
		}
		pci9118_calc_divisors(devpriv->ai_do, dev, s,
				      &cmd->scan_begin_arg, &cmd->convert_arg,
				      devpriv->ai_flags,
				      devpriv->ai_n_realscanlen,
				      &devpriv->ai_divisor1,
				      &devpriv->ai_divisor2, devpriv->usessh,
				      devpriv->ai_add_front);
		devpriv->ai_timer2 = cmd->convert_arg;
	}

	if ((cmd->scan_begin_src == TRIG_TIMER) && ((cmd->convert_src == TRIG_TIMER) || (cmd->convert_src == TRIG_NOW))) {	/*  double timed action */
		if (!devpriv->usedma) {
			comedi_error(dev,
				     "cmd->scan_begin_src=TRIG_TIMER works only with bus mastering!");
			return -EIO;
		}

		devpriv->ai_do = 2;
		pci9118_calc_divisors(devpriv->ai_do, dev, s,
				      &cmd->scan_begin_arg, &cmd->convert_arg,
				      devpriv->ai_flags,
				      devpriv->ai_n_realscanlen,
				      &devpriv->ai_divisor1,
				      &devpriv->ai_divisor2, devpriv->usessh,
				      devpriv->ai_add_front);
		devpriv->ai_timer1 = cmd->scan_begin_arg;
		devpriv->ai_timer2 = cmd->convert_arg;
	}

	if ((cmd->scan_begin_src == TRIG_FOLLOW)
	    && (cmd->convert_src == TRIG_EXT)) {
		devpriv->ai_do = 3;
	}

	start_pacer(dev, -1, 0, 0);	/*  stop pacer */

	devpriv->AdControlReg = 0;	/*  bipolar, S.E., use 8254, stop 8354, internal trigger, soft trigger, disable DMA */
	outl(devpriv->AdControlReg, dev->iobase + PCI9118_ADCNTRL);
	devpriv->AdFunctionReg = AdFunction_PDTrg | AdFunction_PETrg;	/*  positive triggers, no S&H, no burst, burst stop, no post trigger, no about trigger, trigger stop */
	outl(devpriv->AdFunctionReg, dev->iobase + PCI9118_ADFUNC);
	udelay(1);
	outl(0, dev->iobase + PCI9118_DELFIFO);	/*  flush FIFO */
	inl(dev->iobase + PCI9118_ADSTAT);	/*  flush A/D and INT status register */
	inl(dev->iobase + PCI9118_INTSRC);

	devpriv->ai_act_scan = 0;
	devpriv->ai_act_dmapos = 0;
	s->async->cur_chan = 0;
	devpriv->ai_buf_ptr = 0;

	if (devpriv->usedma)
		ret = pci9118_ai_docmd_dma(dev, s);
	else
		ret = pci9118_ai_docmd_sampl(dev, s);

	DPRINTK("adl_pci9118 EDBG: END: pci9118_ai_cmd()\n");
	return ret;
}