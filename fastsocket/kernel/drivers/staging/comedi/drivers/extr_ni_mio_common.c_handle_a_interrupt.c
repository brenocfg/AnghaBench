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
struct comedi_subdevice {scalar_t__ type; TYPE_1__* async; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct TYPE_4__ {unsigned short (* stc_readw ) (struct comedi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ai_continuous; } ;
struct TYPE_3__ {int events; } ;

/* Variables and functions */
 unsigned short AI_FIFO_Half_Full_St ; 
 unsigned short AI_Overflow_St ; 
 unsigned short AI_Overrun_St ; 
 unsigned short AI_SC_TC_Error_St ; 
 unsigned short AI_SC_TC_St ; 
 unsigned short AI_START1_St ; 
 unsigned short AI_STOP_St ; 
 int /*<<< orphan*/  AI_Status_1_Register ; 
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
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 unsigned short Interrupt_A_St ; 
 int NI_AI_SUBDEV ; 
 int SRF_RUNNING ; 
 int comedi_get_subdevice_runflags (struct comedi_subdevice*) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  ni_event (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_handle_eos (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_handle_fifo_half_full (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_mio_print_status_a (unsigned short) ; 
 int /*<<< orphan*/  ni_sync_ai_dma (struct comedi_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  shutdown_ai_command (struct comedi_device*) ; 
 unsigned short stub1 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned short stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_a_interrupt(struct comedi_device *dev, unsigned short status,
			       unsigned ai_mite_status)
{
	struct comedi_subdevice *s = dev->subdevices + NI_AI_SUBDEV;

	/* 67xx boards don't have ai subdevice, but their gpct0 might generate an a interrupt */
	if (s->type == COMEDI_SUBD_UNUSED)
		return;

#ifdef DEBUG_INTERRUPT
	printk
	    ("ni_mio_common: interrupt: a_status=%04x ai_mite_status=%08x\n",
	     status, ai_mite_status);
	ni_mio_print_status_a(status);
#endif
#ifdef PCIDMA
	if (ai_mite_status & CHSR_LINKC) {
		ni_sync_ai_dma(dev);
	}

	if (ai_mite_status & ~(CHSR_INT | CHSR_LINKC | CHSR_DONE | CHSR_MRDY |
			       CHSR_DRDY | CHSR_DRQ1 | CHSR_DRQ0 | CHSR_ERROR |
			       CHSR_SABORT | CHSR_XFERR | CHSR_LxERR_mask)) {
		printk
		    ("unknown mite interrupt, ack! (ai_mite_status=%08x)\n",
		     ai_mite_status);
		/* mite_print_chsr(ai_mite_status); */
		s->async->events |= COMEDI_CB_ERROR | COMEDI_CB_EOA;
		/* disable_irq(dev->irq); */
	}
#endif

	/* test for all uncommon interrupt events at the same time */
	if (status & (AI_Overrun_St | AI_Overflow_St | AI_SC_TC_Error_St |
		      AI_SC_TC_St | AI_START1_St)) {
		if (status == 0xffff) {
			printk
			    ("ni_mio_common: a_status=0xffff.  Card removed?\n");
			/* we probably aren't even running a command now,
			 * so it's a good idea to be careful. */
			if (comedi_get_subdevice_runflags(s) & SRF_RUNNING) {
				s->async->events |=
				    COMEDI_CB_ERROR | COMEDI_CB_EOA;
				ni_event(dev, s);
			}
			return;
		}
		if (status & (AI_Overrun_St | AI_Overflow_St |
			      AI_SC_TC_Error_St)) {
			printk("ni_mio_common: ai error a_status=%04x\n",
			       status);
			ni_mio_print_status_a(status);

			shutdown_ai_command(dev);

			s->async->events |= COMEDI_CB_ERROR;
			if (status & (AI_Overrun_St | AI_Overflow_St))
				s->async->events |= COMEDI_CB_OVERFLOW;

			ni_event(dev, s);

			return;
		}
		if (status & AI_SC_TC_St) {
#ifdef DEBUG_INTERRUPT
			printk("ni_mio_common: SC_TC interrupt\n");
#endif
			if (!devpriv->ai_continuous) {
				shutdown_ai_command(dev);
			}
		}
	}
#ifndef PCIDMA
	if (status & AI_FIFO_Half_Full_St) {
		int i;
		static const int timeout = 10;
		/* pcmcia cards (at least 6036) seem to stop producing interrupts if we
		 *fail to get the fifo less than half full, so loop to be sure.*/
		for (i = 0; i < timeout; ++i) {
			ni_handle_fifo_half_full(dev);
			if ((devpriv->stc_readw(dev,
						AI_Status_1_Register) &
			     AI_FIFO_Half_Full_St) == 0)
				break;
		}
	}
#endif /*  !PCIDMA */

	if ((status & AI_STOP_St)) {
		ni_handle_eos(dev, s);
	}

	ni_event(dev, s);

#ifdef DEBUG_INTERRUPT
	status = devpriv->stc_readw(dev, AI_Status_1_Register);
	if (status & Interrupt_A_St) {
		printk
		    ("handle_a_interrupt: didn't clear interrupt? status=0x%x\n",
		     status);
	}
#endif
}