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
struct comedi_device {scalar_t__ subdevices; scalar_t__ iobase; int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int ai12_startstop; unsigned int AdControlReg; int /*<<< orphan*/  (* int_ai_func ) (struct comedi_device*,scalar_t__,unsigned int,unsigned int,unsigned int) ;scalar_t__ ai_neverending; int /*<<< orphan*/  ai_divisor2; int /*<<< orphan*/  ai_divisor1; scalar_t__ ai_do; scalar_t__ iobase_a; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 unsigned int ANY_S593X_INT ; 
 unsigned int AdStatus_DTH ; 
 int /*<<< orphan*/  EXTTRG_AI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int Int_DTrg ; 
 scalar_t__ PCI9118_ADCNTRL ; 
 scalar_t__ PCI9118_ADSTAT ; 
 scalar_t__ PCI9118_INTSRC ; 
 int START_AI_EXT ; 
 int STOP_AI_EXT ; 
 TYPE_1__* devpriv ; 
 int inl (scalar_t__) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  pci9118_exttrg_del (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_pacer (struct comedi_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,scalar_t__,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static irqreturn_t interrupt_pci9118(int irq, void *d)
{
	struct comedi_device *dev = d;
	unsigned int int_daq = 0, int_amcc, int_adstat;

	if (!dev->attached)
		return IRQ_NONE;	/*  not fully initialized */

	int_daq = inl(dev->iobase + PCI9118_INTSRC) & 0xf;	/*  get IRQ reasons from card */
	int_amcc = inl(devpriv->iobase_a + AMCC_OP_REG_INTCSR);	/*  get INT register from AMCC chip */

/* DPRINTK("INT daq=0x%01x amcc=0x%08x MWAR=0x%08x MWTC=0x%08x ADSTAT=0x%02x ai_do=%d\n", int_daq, int_amcc, inl(devpriv->iobase_a+AMCC_OP_REG_MWAR), inl(devpriv->iobase_a+AMCC_OP_REG_MWTC), inw(dev->iobase+PCI9118_ADSTAT)&0x1ff,devpriv->ai_do); */

	if ((!int_daq) && (!(int_amcc & ANY_S593X_INT)))
		return IRQ_NONE;	/*  interrupt from other source */

	outl(int_amcc | 0x00ff0000, devpriv->iobase_a + AMCC_OP_REG_INTCSR);	/*  shutdown IRQ reasons in AMCC */

	int_adstat = inw(dev->iobase + PCI9118_ADSTAT) & 0x1ff;	/*  get STATUS register */

	if (devpriv->ai_do) {
		if (devpriv->ai12_startstop)
			if ((int_adstat & AdStatus_DTH) && (int_daq & Int_DTrg)) {	/*  start stop of measure */
				if (devpriv->ai12_startstop & START_AI_EXT) {
					devpriv->ai12_startstop &=
					    ~START_AI_EXT;
					if (!(devpriv->ai12_startstop &
					      STOP_AI_EXT))
						pci9118_exttrg_del(dev, EXTTRG_AI);	/*  deactivate EXT trigger */
					start_pacer(dev, devpriv->ai_do, devpriv->ai_divisor1, devpriv->ai_divisor2);	/*  start pacer */
					outl(devpriv->AdControlReg,
					     dev->iobase + PCI9118_ADCNTRL);
				} else {
					if (devpriv->ai12_startstop &
					    STOP_AI_EXT) {
						devpriv->ai12_startstop &=
						    ~STOP_AI_EXT;
						pci9118_exttrg_del(dev, EXTTRG_AI);	/*  deactivate EXT trigger */
						devpriv->ai_neverending = 0;	/* well, on next interrupt from DMA/EOC measure will stop */
					}
				}
			}

		(devpriv->int_ai_func) (dev, dev->subdevices + 0, int_adstat,
					int_amcc, int_daq);

	}
	return IRQ_HANDLED;
}