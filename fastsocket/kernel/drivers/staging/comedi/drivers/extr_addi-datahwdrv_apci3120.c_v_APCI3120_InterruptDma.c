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
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct TYPE_4__ {unsigned int* ui_DmaBufferUsesize; size_t ui_DmaActualBuffer; unsigned long* ul_DmaBufferHw; int ui_AiFlags; scalar_t__ ui_AiActualScan; scalar_t__ ui_AiNbrofScans; scalar_t__ i_IobaseAmcc; scalar_t__ i_IobaseAddon; scalar_t__ b_DmaDoubleBuffer; void* b_AiCyclicAcquisition; int /*<<< orphan*/  b_AiContinuous; int /*<<< orphan*/ * ul_DmaBufferVirtual; } ;
struct TYPE_3__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 unsigned int AGCSTS_RESET_A2P_FIFO ; 
 unsigned int AGCSTS_TC_ENABLE ; 
 scalar_t__ AMCC_OP_REG_AGCSTS ; 
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 scalar_t__ AMCC_OP_REG_MCSR ; 
 scalar_t__ AMCC_OP_REG_MWTC ; 
 unsigned int APCI3120_A2P_FIFO_MANAGEMENT ; 
 int APCI3120_ADD_ON_AGCSTS_HIGH ; 
 int APCI3120_ADD_ON_AGCSTS_LOW ; 
 int APCI3120_ADD_ON_MWAR_HIGH ; 
 int APCI3120_ADD_ON_MWAR_LOW ; 
 int APCI3120_ADD_ON_MWTC_HIGH ; 
 int APCI3120_ADD_ON_MWTC_LOW ; 
 void* APCI3120_DISABLE ; 
 int APCI3120_ENABLE_TRANSFER_ADD_ON_HIGH ; 
 int APCI3120_ENABLE_TRANSFER_ADD_ON_LOW ; 
 unsigned int APCI3120_ENABLE_WRITE_TC_INT ; 
 unsigned int APCI3120_FIFO_ADVANCE_ON_BYTE_2 ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  COMEDI_CB_EOS ; 
 int TRIG_WAKE_EOS ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  i_APCI3120_StopCyclicAcquisition (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  v_APCI3120_InterruptDmaMoveBlock16bit (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 

void v_APCI3120_InterruptDma(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->subdevices + 0;
	unsigned int next_dma_buf, samplesinbuf;
	unsigned long low_word, high_word, var;

	unsigned int ui_Tmp;
	samplesinbuf =
		devpriv->ui_DmaBufferUsesize[devpriv->ui_DmaActualBuffer] -
		inl(devpriv->i_IobaseAmcc + AMCC_OP_REG_MWTC);

	if (samplesinbuf <
		devpriv->ui_DmaBufferUsesize[devpriv->ui_DmaActualBuffer]) {
		comedi_error(dev, "Interrupted DMA transfer!");
	}
	if (samplesinbuf & 1) {
		comedi_error(dev, "Odd count of bytes in DMA ring!");
		i_APCI3120_StopCyclicAcquisition(dev, s);
		devpriv->b_AiCyclicAcquisition = APCI3120_DISABLE;

		return;
	}
	samplesinbuf = samplesinbuf >> 1;	/*  number of received samples */
	if (devpriv->b_DmaDoubleBuffer) {
		/*  switch DMA buffers if is used double buffering */
		next_dma_buf = 1 - devpriv->ui_DmaActualBuffer;

		ui_Tmp = AGCSTS_TC_ENABLE | AGCSTS_RESET_A2P_FIFO;
		outl(ui_Tmp, devpriv->i_IobaseAddon + AMCC_OP_REG_AGCSTS);

		/*  changed  since 16 bit interface for add on */
		outw(APCI3120_ADD_ON_AGCSTS_LOW, devpriv->i_IobaseAddon + 0);
		outw(APCI3120_ENABLE_TRANSFER_ADD_ON_LOW,
			devpriv->i_IobaseAddon + 2);
		outw(APCI3120_ADD_ON_AGCSTS_HIGH, devpriv->i_IobaseAddon + 0);
		outw(APCI3120_ENABLE_TRANSFER_ADD_ON_HIGH, devpriv->i_IobaseAddon + 2);	/*  0x1000 is out putted in windows driver */

		var = devpriv->ul_DmaBufferHw[next_dma_buf];
		low_word = var & 0xffff;
		var = devpriv->ul_DmaBufferHw[next_dma_buf];
		high_word = var / 65536;

		/* DMA Start Adress Low */
		outw(APCI3120_ADD_ON_MWAR_LOW, devpriv->i_IobaseAddon + 0);
		outw(low_word, devpriv->i_IobaseAddon + 2);

		/* DMA Start Adress High */
		outw(APCI3120_ADD_ON_MWAR_HIGH, devpriv->i_IobaseAddon + 0);
		outw(high_word, devpriv->i_IobaseAddon + 2);

		var = devpriv->ui_DmaBufferUsesize[next_dma_buf];
		low_word = var & 0xffff;
		var = devpriv->ui_DmaBufferUsesize[next_dma_buf];
		high_word = var / 65536;

		/* Nbr of acquisition LOW */
		outw(APCI3120_ADD_ON_MWTC_LOW, devpriv->i_IobaseAddon + 0);
		outw(low_word, devpriv->i_IobaseAddon + 2);

		/* Nbr of acquisition HIGH */
		outw(APCI3120_ADD_ON_MWTC_HIGH, devpriv->i_IobaseAddon + 0);
		outw(high_word, devpriv->i_IobaseAddon + 2);

/*
 * To configure A2P FIFO
 * ENABLE A2P FIFO WRITE AND ENABLE AMWEN
 * AMWEN_ENABLE | A2P_FIFO_WRITE_ENABLE (0x01|0x02)=0x03
 */
		outw(3, devpriv->i_IobaseAddon + 4);
		/* initialise end of dma interrupt  AINT_WRITE_COMPL = ENABLE_WRITE_TC_INT(ADDI) */
		outl((APCI3120_FIFO_ADVANCE_ON_BYTE_2 |
				APCI3120_ENABLE_WRITE_TC_INT),
			devpriv->i_IobaseAmcc + AMCC_OP_REG_INTCSR);

	}
	if (samplesinbuf) {
		v_APCI3120_InterruptDmaMoveBlock16bit(dev, s,
			devpriv->ul_DmaBufferVirtual[devpriv->
				ui_DmaActualBuffer], samplesinbuf);

		if (!(devpriv->ui_AiFlags & TRIG_WAKE_EOS)) {
			s->async->events |= COMEDI_CB_EOS;
			comedi_event(dev, s);
		}
	}
	if (!devpriv->b_AiContinuous)
		if (devpriv->ui_AiActualScan >= devpriv->ui_AiNbrofScans) {
			/*  all data sampled */
			i_APCI3120_StopCyclicAcquisition(dev, s);
			devpriv->b_AiCyclicAcquisition = APCI3120_DISABLE;
			s->async->events |= COMEDI_CB_EOA;
			comedi_event(dev, s);
			return;
		}

	if (devpriv->b_DmaDoubleBuffer) {	/*  switch dma buffers */
		devpriv->ui_DmaActualBuffer = 1 - devpriv->ui_DmaActualBuffer;
	} else {
/*
 * restart DMA if is not used double buffering
 * ADDED REINITIALISE THE DMA
 */
		ui_Tmp = AGCSTS_TC_ENABLE | AGCSTS_RESET_A2P_FIFO;
		outl(ui_Tmp, devpriv->i_IobaseAddon + AMCC_OP_REG_AGCSTS);

		/*  changed  since 16 bit interface for add on */
		outw(APCI3120_ADD_ON_AGCSTS_LOW, devpriv->i_IobaseAddon + 0);
		outw(APCI3120_ENABLE_TRANSFER_ADD_ON_LOW,
			devpriv->i_IobaseAddon + 2);
		outw(APCI3120_ADD_ON_AGCSTS_HIGH, devpriv->i_IobaseAddon + 0);
		outw(APCI3120_ENABLE_TRANSFER_ADD_ON_HIGH, devpriv->i_IobaseAddon + 2);	/*  */
/*
 * A2P FIFO MANAGEMENT
 * A2P fifo reset & transfer control enable
 */
		outl(APCI3120_A2P_FIFO_MANAGEMENT,
			devpriv->i_IobaseAmcc + AMCC_OP_REG_MCSR);

		var = devpriv->ul_DmaBufferHw[0];
		low_word = var & 0xffff;
		var = devpriv->ul_DmaBufferHw[0];
		high_word = var / 65536;
		outw(APCI3120_ADD_ON_MWAR_LOW, devpriv->i_IobaseAddon + 0);
		outw(low_word, devpriv->i_IobaseAddon + 2);
		outw(APCI3120_ADD_ON_MWAR_HIGH, devpriv->i_IobaseAddon + 0);
		outw(high_word, devpriv->i_IobaseAddon + 2);

		var = devpriv->ui_DmaBufferUsesize[0];
		low_word = var & 0xffff;	/* changed */
		var = devpriv->ui_DmaBufferUsesize[0];
		high_word = var / 65536;
		outw(APCI3120_ADD_ON_MWTC_LOW, devpriv->i_IobaseAddon + 0);
		outw(low_word, devpriv->i_IobaseAddon + 2);
		outw(APCI3120_ADD_ON_MWTC_HIGH, devpriv->i_IobaseAddon + 0);
		outw(high_word, devpriv->i_IobaseAddon + 2);

/*
 * To configure A2P FIFO
 * ENABLE A2P FIFO WRITE AND ENABLE AMWEN
 * AMWEN_ENABLE | A2P_FIFO_WRITE_ENABLE (0x01|0x02)=0x03
 */
		outw(3, devpriv->i_IobaseAddon + 4);
		/* initialise end of dma interrupt  AINT_WRITE_COMPL = ENABLE_WRITE_TC_INT(ADDI) */
		outl((APCI3120_FIFO_ADVANCE_ON_BYTE_2 |
				APCI3120_ENABLE_WRITE_TC_INT),
			devpriv->i_IobaseAmcc + AMCC_OP_REG_INTCSR);
	}
}