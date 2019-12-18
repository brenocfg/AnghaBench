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
struct TYPE_4__ {int /*<<< orphan*/  (* stc_readw ) (struct comedi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mite; } ;
struct TYPE_3__ {int events; } ;

/* Variables and functions */
 unsigned short AO_BC_TC_St ; 
 int AO_Error_Interrupt_Enable ; 
 int AO_FIFO_Interrupt_Enable ; 
 unsigned short AO_FIFO_Request_St ; 
 unsigned short AO_Overrun_St ; 
 int /*<<< orphan*/  AO_Status_2_Register ; 
 unsigned int CHSR_DONE ; 
 unsigned int CHSR_DRDY ; 
 unsigned int CHSR_DRQ0 ; 
 unsigned int CHSR_DRQ1 ; 
 unsigned int CHSR_ERROR ; 
 unsigned int CHSR_INT ; 
 unsigned int CHSR_LINKC ; 
 unsigned int CHSR_LxERR_mask ; 
 unsigned int CHSR_MRDY ; 
 unsigned int CHSR_SABORT ; 
 unsigned int CHSR_XFERR ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 int COMEDI_CB_OVERFLOW ; 
 int /*<<< orphan*/  Interrupt_B_Enable_Register ; 
 int /*<<< orphan*/  MDPRINTK (char*,unsigned short,int /*<<< orphan*/ ) ; 
 int NI_AO_SUBDEV ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  mite_handle_b_linkc (int /*<<< orphan*/ ,struct comedi_device*) ; 
 int ni_ao_fifo_half_empty (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_event (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_mio_print_status_b (unsigned short) ; 
 int /*<<< orphan*/  ni_set_bits (struct comedi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_b_interrupt(struct comedi_device *dev,
			       unsigned short b_status, unsigned ao_mite_status)
{
	struct comedi_subdevice *s = dev->subdevices + NI_AO_SUBDEV;
	/* unsigned short ack=0; */
#ifdef DEBUG_INTERRUPT
	printk("ni_mio_common: interrupt: b_status=%04x m1_status=%08x\n",
	       b_status, ao_mite_status);
	ni_mio_print_status_b(b_status);
#endif

#ifdef PCIDMA
	/* Currently, mite.c requires us to handle LINKC */
	if (ao_mite_status & CHSR_LINKC) {
		mite_handle_b_linkc(devpriv->mite, dev);
	}

	if (ao_mite_status & ~(CHSR_INT | CHSR_LINKC | CHSR_DONE | CHSR_MRDY |
			       CHSR_DRDY | CHSR_DRQ1 | CHSR_DRQ0 | CHSR_ERROR |
			       CHSR_SABORT | CHSR_XFERR | CHSR_LxERR_mask)) {
		printk
		    ("unknown mite interrupt, ack! (ao_mite_status=%08x)\n",
		     ao_mite_status);
		/* mite_print_chsr(ao_mite_status); */
		s->async->events |= COMEDI_CB_EOA | COMEDI_CB_ERROR;
	}
#endif

	if (b_status == 0xffff)
		return;
	if (b_status & AO_Overrun_St) {
		printk
		    ("ni_mio_common: AO FIFO underrun status=0x%04x status2=0x%04x\n",
		     b_status, devpriv->stc_readw(dev, AO_Status_2_Register));
		s->async->events |= COMEDI_CB_OVERFLOW;
	}

	if (b_status & AO_BC_TC_St) {
		MDPRINTK
		    ("ni_mio_common: AO BC_TC status=0x%04x status2=0x%04x\n",
		     b_status, devpriv->stc_readw(dev, AO_Status_2_Register));
		s->async->events |= COMEDI_CB_EOA;
	}
#ifndef PCIDMA
	if (b_status & AO_FIFO_Request_St) {
		int ret;

		ret = ni_ao_fifo_half_empty(dev, s);
		if (!ret) {
			printk("ni_mio_common: AO buffer underrun\n");
			ni_set_bits(dev, Interrupt_B_Enable_Register,
				    AO_FIFO_Interrupt_Enable |
				    AO_Error_Interrupt_Enable, 0);
			s->async->events |= COMEDI_CB_OVERFLOW;
		}
	}
#endif

	ni_event(dev, s);
}