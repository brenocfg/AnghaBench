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
struct TYPE_4__ {int AdFunctionReg; int AdControlReg; scalar_t__ iobase_a; int /*<<< orphan*/  IntControlReg; scalar_t__ dma_actbuf; scalar_t__ ai_neverending; scalar_t__ ai_buf_ptr; scalar_t__ ai_act_dmapos; scalar_t__ ai_act_scan; scalar_t__ usedma; scalar_t__ ai_do; } ;
struct TYPE_3__ {int /*<<< orphan*/ * inttrig; scalar_t__ cur_chan; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 scalar_t__ AMCC_OP_REG_MCSR ; 
 int AdFunction_PDTrg ; 
 int AdFunction_PETrg ; 
 int EN_A2P_TRANSFERS ; 
 int /*<<< orphan*/  EXTTRG_AI ; 
 scalar_t__ PCI9118_ADCNTRL ; 
 scalar_t__ PCI9118_ADFUNC ; 
 scalar_t__ PCI9118_BURST ; 
 scalar_t__ PCI9118_DELFIFO ; 
 scalar_t__ PCI9118_SCANMOD ; 
 TYPE_2__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  pci9118_exttrg_del (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_pacer (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci9118_ai_cancel(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	if (devpriv->usedma)
		outl(inl(devpriv->iobase_a + AMCC_OP_REG_MCSR) & (~EN_A2P_TRANSFERS), devpriv->iobase_a + AMCC_OP_REG_MCSR);	/*  stop DMA */
	pci9118_exttrg_del(dev, EXTTRG_AI);
	start_pacer(dev, 0, 0, 0);	/*  stop 8254 counters */
	devpriv->AdFunctionReg = AdFunction_PDTrg | AdFunction_PETrg;
	outl(devpriv->AdFunctionReg, dev->iobase + PCI9118_ADFUNC);	/*  positive triggers, no S&H, no burst, burst stop, no post trigger, no about trigger, trigger stop */
	devpriv->AdControlReg = 0x00;
	outl(devpriv->AdControlReg, dev->iobase + PCI9118_ADCNTRL);	/*  bipolar, S.E., use 8254, stop 8354, internal trigger, soft trigger, disable INT and DMA */
	outl(0, dev->iobase + PCI9118_BURST);
	outl(1, dev->iobase + PCI9118_SCANMOD);
	outl(2, dev->iobase + PCI9118_SCANMOD);	/*  reset scan queue */
	outl(0, dev->iobase + PCI9118_DELFIFO);	/*  flush FIFO */

	devpriv->ai_do = 0;
	devpriv->usedma = 0;

	devpriv->ai_act_scan = 0;
	devpriv->ai_act_dmapos = 0;
	s->async->cur_chan = 0;
	s->async->inttrig = NULL;
	devpriv->ai_buf_ptr = 0;
	devpriv->ai_neverending = 0;
	devpriv->dma_actbuf = 0;

	if (!devpriv->IntControlReg)
		outl(inl(devpriv->iobase_a + AMCC_OP_REG_INTCSR) | 0x1f00, devpriv->iobase_a + AMCC_OP_REG_INTCSR);	/*  allow INT in AMCC */

	return 0;
}