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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {int convert_src; int convert_arg; int scan_begin_src; } ;
struct comedi_async {int /*<<< orphan*/  inttrig; int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;
struct TYPE_2__ {scalar_t__ ai_scan_count; unsigned char int_en; unsigned char ier; unsigned short adccon; scalar_t__ iobase1; int /*<<< orphan*/  isr_spinlock; int /*<<< orphan*/  ai_continuous; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CMD_STARTED ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int CR_EDGE ; 
 int CR_INVERT ; 
 unsigned char GAT_CONFIG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GAT_EXT ; 
 int /*<<< orphan*/  GAT_NOUTNM2 ; 
 int /*<<< orphan*/  GAT_VCC ; 
 int /*<<< orphan*/  OWNER_AICMD ; 
 scalar_t__ PCI230_ADCCON ; 
 unsigned short PCI230_ADC_TRIG_EXTN ; 
 unsigned short PCI230_ADC_TRIG_EXTP ; 
 unsigned short PCI230_ADC_TRIG_MASK ; 
 unsigned short PCI230_ADC_TRIG_NONE ; 
 unsigned short PCI230_ADC_TRIG_Z2CT2 ; 
 unsigned char PCI230_INT_ADC ; 
 scalar_t__ PCI230_INT_SCE ; 
 scalar_t__ PCI230_ZGAT_SCE ; 
 int /*<<< orphan*/  RES_Z2CT2 ; 
#define  TRIG_EXT 130 
 int TRIG_FOLLOW ; 
#define  TRIG_INT 129 
#define  TRIG_TIMER 128 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ai_inttrig_convert ; 
 int /*<<< orphan*/  pci230_ai_inttrig_scan_begin ; 
 int /*<<< orphan*/  pci230_ai_stop (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci230_ai_update_fifo_trigger_level (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  put_one_resource (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pci230_ai_start(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	unsigned long irqflags;
	unsigned short conv;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;

	set_bit(AI_CMD_STARTED, &devpriv->state);
	if (!devpriv->ai_continuous && (devpriv->ai_scan_count == 0)) {
		/* An empty acquisition! */
		async->events |= COMEDI_CB_EOA;
		pci230_ai_stop(dev, s);
		comedi_event(dev, s);
	} else {
		/* Enable ADC FIFO trigger level interrupt. */
		spin_lock_irqsave(&devpriv->isr_spinlock, irqflags);
		devpriv->int_en |= PCI230_INT_ADC;
		devpriv->ier |= PCI230_INT_ADC;
		outb(devpriv->ier, devpriv->iobase1 + PCI230_INT_SCE);
		spin_unlock_irqrestore(&devpriv->isr_spinlock, irqflags);

		/* Update conversion trigger source which is currently set
		 * to CT2 output, which is currently stuck high. */
		switch (cmd->convert_src) {
		default:
			conv = PCI230_ADC_TRIG_NONE;
			break;
		case TRIG_TIMER:
			/* Using CT2 output. */
			conv = PCI230_ADC_TRIG_Z2CT2;
			break;
		case TRIG_EXT:
			if ((cmd->convert_arg & CR_EDGE) != 0) {
				if ((cmd->convert_arg & CR_INVERT) == 0) {
					/* Trigger on +ve edge. */
					conv = PCI230_ADC_TRIG_EXTP;
				} else {
					/* Trigger on -ve edge. */
					conv = PCI230_ADC_TRIG_EXTN;
				}
			} else {
				/* Backwards compatibility. */
				if (cmd->convert_arg != 0) {
					/* Trigger on +ve edge. */
					conv = PCI230_ADC_TRIG_EXTP;
				} else {
					/* Trigger on -ve edge. */
					conv = PCI230_ADC_TRIG_EXTN;
				}
			}
			break;
		case TRIG_INT:
			/* Use CT2 output for software trigger due to problems
			 * in differential mode on PCI230/260. */
			conv = PCI230_ADC_TRIG_Z2CT2;
			break;
		}
		devpriv->adccon = (devpriv->adccon & ~PCI230_ADC_TRIG_MASK)
		    | conv;
		outw(devpriv->adccon, dev->iobase + PCI230_ADCCON);
		if (cmd->convert_src == TRIG_INT) {
			async->inttrig = pci230_ai_inttrig_convert;
		}
		/* Update FIFO interrupt trigger level, which is currently
		 * set to "full".  */
		pci230_ai_update_fifo_trigger_level(dev, s);
		if (cmd->convert_src == TRIG_TIMER) {
			/* Update timer gates. */
			unsigned char zgat;

			if (cmd->scan_begin_src != TRIG_FOLLOW) {
				/* Conversion timer CT2 needs to be gated by
				 * inverted output of monostable CT2. */
				zgat = GAT_CONFIG(2, GAT_NOUTNM2);
			} else {
				/* Conversion timer CT2 needs to be gated on
				 * continuously. */
				zgat = GAT_CONFIG(2, GAT_VCC);
			}
			outb(zgat, devpriv->iobase1 + PCI230_ZGAT_SCE);
			if (cmd->scan_begin_src != TRIG_FOLLOW) {
				/* Set monostable CT0 trigger source. */
				switch (cmd->scan_begin_src) {
				default:
					zgat = GAT_CONFIG(0, GAT_VCC);
					break;
				case TRIG_EXT:
					/*
					 * For CT0 on PCI230, the external
					 * trigger (gate) signal comes from
					 * PPC0, which is channel 16 of the DIO
					 * subdevice.  The application needs to
					 * configure this as an input in order
					 * to use it as an external scan
					 * trigger.
					 */
					zgat = GAT_CONFIG(0, GAT_EXT);
					break;
				case TRIG_TIMER:
					/*
					 * Monostable CT0 triggered by rising
					 * edge on inverted output of CT1
					 * (falling edge on CT1).
					 */
					zgat = GAT_CONFIG(0, GAT_NOUTNM2);
					break;
				case TRIG_INT:
					/*
					 * Monostable CT0 is triggered by
					 * inttrig function waggling the CT0
					 * gate source.
					 */
					zgat = GAT_CONFIG(0, GAT_VCC);
					break;
				}
				outb(zgat, devpriv->iobase1 + PCI230_ZGAT_SCE);
				switch (cmd->scan_begin_src) {
				case TRIG_TIMER:
					/* Scan period timer CT1 needs to be
					 * gated on to start counting. */
					zgat = GAT_CONFIG(1, GAT_VCC);
					outb(zgat, devpriv->iobase1
					     + PCI230_ZGAT_SCE);
					break;
				case TRIG_INT:
					async->inttrig =
					    pci230_ai_inttrig_scan_begin;
					break;
				}
			}
		} else if (cmd->convert_src != TRIG_INT) {
			/* No longer need Z2-CT2. */
			put_one_resource(dev, RES_Z2CT2, OWNER_AICMD);
		}
	}
}