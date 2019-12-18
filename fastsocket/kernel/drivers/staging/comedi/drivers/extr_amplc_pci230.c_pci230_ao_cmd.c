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
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {scalar_t__ scan_begin_src; scalar_t__ stop_src; unsigned int chanlist_len; int flags; int /*<<< orphan*/  scan_begin_arg; int /*<<< orphan*/ * chanlist; scalar_t__ stop_arg; } ;
struct TYPE_4__ {int ao_continuous; int hwver; unsigned short daccon; scalar_t__ iobase1; scalar_t__ ao_bipolar; scalar_t__ ao_scan_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  GAT_CONFIG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GAT_GND ; 
 int /*<<< orphan*/  I8254_MODE3 ; 
 int /*<<< orphan*/  OWNER_AOCMD ; 
 scalar_t__ PCI230P2_DACEN ; 
 unsigned short PCI230P2_DAC_FIFO_EN ; 
 unsigned short PCI230P2_DAC_FIFO_RESET ; 
 unsigned short PCI230P2_DAC_FIFO_UNDERRUN_CLEAR ; 
 unsigned short PCI230P2_DAC_INT_FIFO_NHALF ; 
 unsigned short PCI230P2_DAC_TRIG_NONE ; 
 scalar_t__ PCI230_DACCON ; 
 unsigned short PCI230_DAC_OR_BIP ; 
 unsigned short PCI230_DAC_OR_UNI ; 
 scalar_t__ PCI230_ZGAT_SCE ; 
 int /*<<< orphan*/  RES_Z2CT1 ; 
 scalar_t__ TRIG_COUNT ; 
 int TRIG_ROUND_MASK ; 
 scalar_t__ TRIG_TIMER ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  get_one_resource (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 scalar_t__* pci230_ao_bipolar ; 
 int /*<<< orphan*/  pci230_ao_inttrig_start ; 
 int /*<<< orphan*/  pci230_ct_setup_ns_mode (struct comedi_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pci230_ao_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	unsigned short daccon;
	unsigned int range;

	/* Get the command. */
	struct comedi_cmd *cmd = &s->async->cmd;

	if (cmd->scan_begin_src == TRIG_TIMER) {
		/* Claim Z2-CT1. */
		if (!get_one_resource(dev, RES_Z2CT1, OWNER_AOCMD)) {
			return -EBUSY;
		}
	}

	/* Get number of scans required. */
	if (cmd->stop_src == TRIG_COUNT) {
		devpriv->ao_scan_count = cmd->stop_arg;
		devpriv->ao_continuous = 0;
	} else {
		/* TRIG_NONE, user calls cancel. */
		devpriv->ao_scan_count = 0;
		devpriv->ao_continuous = 1;
	}

	/* Set range - see analogue output range table; 0 => unipolar 10V,
	 * 1 => bipolar +/-10V range scale */
	range = CR_RANGE(cmd->chanlist[0]);
	devpriv->ao_bipolar = pci230_ao_bipolar[range];
	daccon = devpriv->ao_bipolar ? PCI230_DAC_OR_BIP : PCI230_DAC_OR_UNI;
	/* Use DAC FIFO for hardware version 2 onwards. */
	if (devpriv->hwver >= 2) {
		unsigned short dacen;
		unsigned int i;

		dacen = 0;
		for (i = 0; i < cmd->chanlist_len; i++) {
			dacen |= 1 << CR_CHAN(cmd->chanlist[i]);
		}
		/* Set channel scan list. */
		outw(dacen, dev->iobase + PCI230P2_DACEN);
		/*
		 * Enable DAC FIFO.
		 * Set DAC scan source to 'none'.
		 * Set DAC FIFO interrupt trigger level to 'not half full'.
		 * Reset DAC FIFO and clear underrun.
		 *
		 * N.B. DAC FIFO interrupts are currently disabled.
		 */
		daccon |= PCI230P2_DAC_FIFO_EN | PCI230P2_DAC_FIFO_RESET
		    | PCI230P2_DAC_FIFO_UNDERRUN_CLEAR
		    | PCI230P2_DAC_TRIG_NONE | PCI230P2_DAC_INT_FIFO_NHALF;
	}

	/* Set DACCON. */
	outw(daccon, dev->iobase + PCI230_DACCON);
	/* Preserve most of DACCON apart from write-only, transient bits. */
	devpriv->daccon = daccon
	    & ~(PCI230P2_DAC_FIFO_RESET | PCI230P2_DAC_FIFO_UNDERRUN_CLEAR);

	if (cmd->scan_begin_src == TRIG_TIMER) {
		/* Set the counter timer 1 to the specified scan frequency. */
		/* cmd->scan_begin_arg is sampling period in ns */
		/* gate it off for now. */
		outb(GAT_CONFIG(1, GAT_GND),
		     devpriv->iobase1 + PCI230_ZGAT_SCE);
		pci230_ct_setup_ns_mode(dev, 1, I8254_MODE3,
					cmd->scan_begin_arg,
					cmd->flags & TRIG_ROUND_MASK);
	}

	/* N.B. cmd->start_src == TRIG_INT */
	s->async->inttrig = pci230_ao_inttrig_start;

	return 0;
}