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
struct comedi_cmd {unsigned int chanlist_len; scalar_t__ scan_begin_src; unsigned int scan_begin_arg; int flags; int stop_src; int start_src; int /*<<< orphan*/  stop_arg; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_4__ {unsigned int ao_enab; unsigned int* ao_scan_order; int daccon; int* hwrange; unsigned int cached_div1; unsigned int cached_div2; int ao_stop_continuous; int /*<<< orphan*/  ao_spinlock; scalar_t__ iobase1; int /*<<< orphan*/  intsce; int /*<<< orphan*/  ao_stop_count; } ;
struct TYPE_3__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_10MHZ ; 
 int /*<<< orphan*/  CLK_CONFIG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_OUTNM1 ; 
 int COMBINE (int,int,int) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GAT_CONFIG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GAT_VCC ; 
 scalar_t__ PCI224_DACCEN ; 
 scalar_t__ PCI224_DACCON ; 
 int PCI224_DACCON_FIFOINTR_MASK ; 
 int PCI224_DACCON_FIFOINTR_NHALF ; 
 int PCI224_DACCON_FIFORESET ; 
 int PCI224_DACCON_POLAR_MASK ; 
 int PCI224_DACCON_TRIG_MASK ; 
 int PCI224_DACCON_TRIG_NONE ; 
 int PCI224_DACCON_VREF_MASK ; 
 int /*<<< orphan*/  PCI224_INTR_EXT ; 
 scalar_t__ PCI224_INT_SCE ; 
 scalar_t__ PCI224_Z2_CT0 ; 
 scalar_t__ PCI224_ZCLK_SCE ; 
 scalar_t__ PCI224_ZGAT_SCE ; 
 int TIMEBASE_10MHZ ; 
#define  TRIG_COUNT 133 
#define  TRIG_EXT 132 
#define  TRIG_INT 131 
#define  TRIG_ROUND_DOWN 130 
 int TRIG_ROUND_MASK ; 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 
 scalar_t__ TRIG_TIMER ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  i8254_load (scalar_t__,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pci224_ao_inttrig_start ; 
 int /*<<< orphan*/  pci224_cascade_ns_to_timer (int,unsigned int*,unsigned int*,unsigned int*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pci224_ao_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	int range;
	unsigned int i, j;
	unsigned int ch;
	unsigned int rank;
	unsigned long flags;

	/* Cannot handle null/empty chanlist. */
	if (cmd->chanlist == NULL || cmd->chanlist_len == 0) {
		return -EINVAL;
	}

	/* Determine which channels are enabled and their load order.  */
	devpriv->ao_enab = 0;

	for (i = 0; i < cmd->chanlist_len; i++) {
		ch = CR_CHAN(cmd->chanlist[i]);
		devpriv->ao_enab |= 1U << ch;
		rank = 0;
		for (j = 0; j < cmd->chanlist_len; j++) {
			if (CR_CHAN(cmd->chanlist[j]) < ch) {
				rank++;
			}
		}
		devpriv->ao_scan_order[rank] = i;
	}

	/* Set enabled channels. */
	outw(devpriv->ao_enab, dev->iobase + PCI224_DACCEN);

	/* Determine range and polarity.  All channels the same.  */
	range = CR_RANGE(cmd->chanlist[0]);

	/*
	 * Set DAC range and polarity.
	 * Set DAC scan trigger source to 'none'.
	 * Set DAC FIFO interrupt trigger level to 'not half full'.
	 * Reset DAC FIFO.
	 *
	 * N.B. DAC FIFO interrupts are currently disabled.
	 */
	devpriv->daccon = COMBINE(devpriv->daccon,
				  (devpriv->
				   hwrange[range] | PCI224_DACCON_TRIG_NONE |
				   PCI224_DACCON_FIFOINTR_NHALF),
				  (PCI224_DACCON_POLAR_MASK |
				   PCI224_DACCON_VREF_MASK |
				   PCI224_DACCON_TRIG_MASK |
				   PCI224_DACCON_FIFOINTR_MASK));
	outw(devpriv->daccon | PCI224_DACCON_FIFORESET,
	     dev->iobase + PCI224_DACCON);

	if (cmd->scan_begin_src == TRIG_TIMER) {
		unsigned int div1, div2, round;
		unsigned int ns = cmd->scan_begin_arg;
		int round_mode = cmd->flags & TRIG_ROUND_MASK;

		/* Check whether to use a single timer. */
		switch (round_mode) {
		case TRIG_ROUND_NEAREST:
		default:
			round = TIMEBASE_10MHZ / 2;
			break;
		case TRIG_ROUND_DOWN:
			round = 0;
			break;
		case TRIG_ROUND_UP:
			round = TIMEBASE_10MHZ - 1;
			break;
		}
		/* Be careful to avoid overflow! */
		div2 = cmd->scan_begin_arg / TIMEBASE_10MHZ;
		div2 += (round + cmd->scan_begin_arg % TIMEBASE_10MHZ) /
		    TIMEBASE_10MHZ;
		if (div2 <= 0x10000) {
			/* A single timer will suffice. */
			if (div2 < 2)
				div2 = 2;
			div2 &= 0xffff;
			div1 = 1;	/* Flag that single timer to be used. */
		} else {
			/* Use two timers. */
			div1 = devpriv->cached_div1;
			div2 = devpriv->cached_div2;
			pci224_cascade_ns_to_timer(TIMEBASE_10MHZ, &div1, &div2,
						   &ns, round_mode);
		}

		/*
		 * The output of timer Z2-0 will be used as the scan trigger
		 * source.
		 */
		/* Make sure Z2-0 is gated on.  */
		outb(GAT_CONFIG(0, GAT_VCC),
		     devpriv->iobase1 + PCI224_ZGAT_SCE);
		if (div1 == 1) {
			/* Not cascading.  Z2-0 needs 10 MHz clock. */
			outb(CLK_CONFIG(0, CLK_10MHZ),
			     devpriv->iobase1 + PCI224_ZCLK_SCE);
		} else {
			/* Cascading with Z2-2. */
			/* Make sure Z2-2 is gated on.  */
			outb(GAT_CONFIG(2, GAT_VCC),
			     devpriv->iobase1 + PCI224_ZGAT_SCE);
			/* Z2-2 needs 10 MHz clock. */
			outb(CLK_CONFIG(2, CLK_10MHZ),
			     devpriv->iobase1 + PCI224_ZCLK_SCE);
			/* Load Z2-2 mode (2) and counter (div1). */
			i8254_load(devpriv->iobase1 + PCI224_Z2_CT0, 0,
				   2, div1, 2);
			/* Z2-0 is clocked from Z2-2's output. */
			outb(CLK_CONFIG(0, CLK_OUTNM1),
			     devpriv->iobase1 + PCI224_ZCLK_SCE);
		}
		/* Load Z2-0 mode (2) and counter (div2). */
		i8254_load(devpriv->iobase1 + PCI224_Z2_CT0, 0, 0, div2, 2);
	}

	/*
	 * Sort out end of acquisition.
	 */
	switch (cmd->stop_src) {
	case TRIG_COUNT:
		/* Fixed number of scans.  */
		devpriv->ao_stop_continuous = 0;
		devpriv->ao_stop_count = cmd->stop_arg;
		break;
	default:
		/* Continuous scans. */
		devpriv->ao_stop_continuous = 1;
		devpriv->ao_stop_count = 0;
		break;
	}

	/*
	 * Sort out start of acquisition.
	 */
	switch (cmd->start_src) {
	case TRIG_INT:
		spin_lock_irqsave(&devpriv->ao_spinlock, flags);
		s->async->inttrig = &pci224_ao_inttrig_start;
		spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
		break;
	case TRIG_EXT:
		/* Enable external interrupt trigger to start acquisition. */
		spin_lock_irqsave(&devpriv->ao_spinlock, flags);
		devpriv->intsce |= PCI224_INTR_EXT;
		outb(devpriv->intsce, devpriv->iobase1 + PCI224_INT_SCE);
		spin_unlock_irqrestore(&devpriv->ao_spinlock, flags);
		break;
	}

	return 0;
}