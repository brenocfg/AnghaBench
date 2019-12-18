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
struct TYPE_4__ {unsigned short ai_maskerr; int* dmabuf_use_size; size_t dma_actbuf; int* dmabuf_hw; int* dmabuf_used_size; int ai_do; int ai_data_len; scalar_t__ ai_act_scan; scalar_t__ ai_scans; scalar_t__ iobase_a; scalar_t__ dma_doublebuf; int /*<<< orphan*/  ai_neverending; int /*<<< orphan*/ * dmabuf_virt; } ;
struct TYPE_3__ {int events; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_MWAR ; 
 scalar_t__ AMCC_OP_REG_MWTC ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 unsigned int MASTER_ABORT_INT ; 
 unsigned int TARGET_ABORT_INT ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  interrupt_pci9118_ai_mode4_switch (struct comedi_device*) ; 
 int /*<<< orphan*/  move_block_from_dma (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  pci9118_ai_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 scalar_t__ pci9118_decode_error_status (struct comedi_device*,struct comedi_subdevice*,unsigned short) ; 

__attribute__((used)) static void interrupt_pci9118_ai_dma(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     unsigned short int_adstat,
				     unsigned int int_amcc,
				     unsigned short int_daq)
{
	unsigned int next_dma_buf, samplesinbuf, sampls, m;

	if (int_amcc & MASTER_ABORT_INT) {
		comedi_error(dev, "AMCC IRQ - MASTER DMA ABORT!");
		s->async->events |= COMEDI_CB_ERROR | COMEDI_CB_EOA;
		pci9118_ai_cancel(dev, s);
		comedi_event(dev, s);
		return;
	}

	if (int_amcc & TARGET_ABORT_INT) {
		comedi_error(dev, "AMCC IRQ - TARGET DMA ABORT!");
		s->async->events |= COMEDI_CB_ERROR | COMEDI_CB_EOA;
		pci9118_ai_cancel(dev, s);
		comedi_event(dev, s);
		return;
	}

	if (int_adstat & devpriv->ai_maskerr)
/* if (int_adstat & 0x106) */
		if (pci9118_decode_error_status(dev, s, int_adstat))
			return;

	samplesinbuf = devpriv->dmabuf_use_size[devpriv->dma_actbuf] >> 1;	/*  number of received real samples */
/* DPRINTK("dma_actbuf=%d\n",devpriv->dma_actbuf); */

	if (devpriv->dma_doublebuf) {	/*  switch DMA buffers if is used double buffering */
		next_dma_buf = 1 - devpriv->dma_actbuf;
		outl(devpriv->dmabuf_hw[next_dma_buf],
		     devpriv->iobase_a + AMCC_OP_REG_MWAR);
		outl(devpriv->dmabuf_use_size[next_dma_buf],
		     devpriv->iobase_a + AMCC_OP_REG_MWTC);
		devpriv->dmabuf_used_size[next_dma_buf] =
		    devpriv->dmabuf_use_size[next_dma_buf];
		if (devpriv->ai_do == 4)
			interrupt_pci9118_ai_mode4_switch(dev);
	}

	if (samplesinbuf) {
		m = devpriv->ai_data_len >> 1;	/*  how many samples is to end of buffer */
/* DPRINTK("samps=%d m=%d %d %d\n",samplesinbuf,m,s->async->buf_int_count,s->async->buf_int_ptr); */
		sampls = m;
		move_block_from_dma(dev, s,
				    devpriv->dmabuf_virt[devpriv->dma_actbuf],
				    samplesinbuf);
		m = m - sampls;	/*  m= how many samples was transfered */
	}
/* DPRINTK("YYY\n"); */

	if (!devpriv->ai_neverending)
		if (devpriv->ai_act_scan >= devpriv->ai_scans) {	/* all data sampled */
			pci9118_ai_cancel(dev, s);
			s->async->events |= COMEDI_CB_EOA;
		}

	if (devpriv->dma_doublebuf) {	/*  switch dma buffers */
		devpriv->dma_actbuf = 1 - devpriv->dma_actbuf;
	} else {		/*  restart DMA if is not used double buffering */
		outl(devpriv->dmabuf_hw[0],
		     devpriv->iobase_a + AMCC_OP_REG_MWAR);
		outl(devpriv->dmabuf_use_size[0],
		     devpriv->iobase_a + AMCC_OP_REG_MWTC);
		if (devpriv->ai_do == 4)
			interrupt_pci9118_ai_mode4_switch(dev);
	}

	comedi_event(dev, s);
}