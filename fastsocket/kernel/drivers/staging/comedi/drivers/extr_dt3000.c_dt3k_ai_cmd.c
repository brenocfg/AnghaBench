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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int chanlist_len; int scan_end_arg; scalar_t__ convert_src; int flags; scalar_t__ scan_begin_src; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/  convert_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_4__ {scalar_t__ io_addr; } ;
struct TYPE_3__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int AI_FIFO_DEPTH ; 
 unsigned int AREF_DIFF ; 
 int /*<<< orphan*/  CMD_CONFIG ; 
 int /*<<< orphan*/  CMD_START ; 
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DPR_ADC_buffer ; 
 scalar_t__ DPR_Int_Mask ; 
 scalar_t__ DPR_Params (int) ; 
 scalar_t__ DPR_SubSys ; 
 int DT3000_ADFULL ; 
 int DT3000_ADHWERR ; 
 int DT3000_ADSWERR ; 
 unsigned int DT3000_AD_RETRIG_INTERNAL ; 
 int SUBS_AI ; 
 int TRIG_ROUND_MASK ; 
 scalar_t__ TRIG_TIMER ; 
 scalar_t__ debug_n_ints ; 
 TYPE_2__* devpriv ; 
 unsigned int dt3k_ns_to_timer (int,int /*<<< orphan*/ *,int) ; 
 int dt3k_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int dt3k_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	int i;
	unsigned int chan, range, aref;
	unsigned int divider;
	unsigned int tscandiv;
	int ret;
	unsigned int mode;

	printk("dt3k_ai_cmd:\n");
	for (i = 0; i < cmd->chanlist_len; i++) {
		chan = CR_CHAN(cmd->chanlist[i]);
		range = CR_RANGE(cmd->chanlist[i]);

		writew((range << 6) | chan,
		       devpriv->io_addr + DPR_ADC_buffer + i);
	}
	aref = CR_AREF(cmd->chanlist[0]);

	writew(cmd->scan_end_arg, devpriv->io_addr + DPR_Params(0));
	printk("param[0]=0x%04x\n", cmd->scan_end_arg);

	if (cmd->convert_src == TRIG_TIMER) {
		divider = dt3k_ns_to_timer(50, &cmd->convert_arg,
					   cmd->flags & TRIG_ROUND_MASK);
		writew((divider >> 16), devpriv->io_addr + DPR_Params(1));
		printk("param[1]=0x%04x\n", divider >> 16);
		writew((divider & 0xffff), devpriv->io_addr + DPR_Params(2));
		printk("param[2]=0x%04x\n", divider & 0xffff);
	} else {
		/* not supported */
	}

	if (cmd->scan_begin_src == TRIG_TIMER) {
		tscandiv = dt3k_ns_to_timer(100, &cmd->scan_begin_arg,
					    cmd->flags & TRIG_ROUND_MASK);
		writew((tscandiv >> 16), devpriv->io_addr + DPR_Params(3));
		printk("param[3]=0x%04x\n", tscandiv >> 16);
		writew((tscandiv & 0xffff), devpriv->io_addr + DPR_Params(4));
		printk("param[4]=0x%04x\n", tscandiv & 0xffff);
	} else {
		/* not supported */
	}

	mode = DT3000_AD_RETRIG_INTERNAL | 0 | 0;
	writew(mode, devpriv->io_addr + DPR_Params(5));
	printk("param[5]=0x%04x\n", mode);
	writew(aref == AREF_DIFF, devpriv->io_addr + DPR_Params(6));
	printk("param[6]=0x%04x\n", aref == AREF_DIFF);

	writew(AI_FIFO_DEPTH / 2, devpriv->io_addr + DPR_Params(7));
	printk("param[7]=0x%04x\n", AI_FIFO_DEPTH / 2);

	writew(SUBS_AI, devpriv->io_addr + DPR_SubSys);
	ret = dt3k_send_cmd(dev, CMD_CONFIG);

	writew(DT3000_ADFULL | DT3000_ADSWERR | DT3000_ADHWERR,
	       devpriv->io_addr + DPR_Int_Mask);

	debug_n_ints = 0;

	writew(SUBS_AI, devpriv->io_addr + DPR_SubSys);
	ret = dt3k_send_cmd(dev, CMD_START);

	return 0;
}