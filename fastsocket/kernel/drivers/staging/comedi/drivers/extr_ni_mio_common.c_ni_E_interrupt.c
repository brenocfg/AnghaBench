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
struct mite_struct {scalar_t__ mite_io_addr; } ;
struct comedi_device {scalar_t__ attached; int /*<<< orphan*/  spinlock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {unsigned short (* stc_readw ) (struct comedi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mite_channel_lock; TYPE_1__* ao_mite_chan; TYPE_1__* ai_mite_chan; struct mite_struct* mite; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_Status_1_Register ; 
 int /*<<< orphan*/  AO_Status_1_Register ; 
 int /*<<< orphan*/  CHOR_CLRLC ; 
 unsigned int CHSR_INT ; 
 unsigned int CHSR_LINKC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned short Interrupt_A_St ; 
 unsigned short Interrupt_B_St ; 
 scalar_t__ MITE_CHOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ack_a_interrupt (struct comedi_device*,unsigned short) ; 
 int /*<<< orphan*/  ack_b_interrupt (struct comedi_device*,unsigned short) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  handle_a_interrupt (struct comedi_device*,unsigned short,unsigned int) ; 
 int /*<<< orphan*/  handle_b_interrupt (struct comedi_device*,unsigned short,unsigned int) ; 
 int /*<<< orphan*/  handle_cdio_interrupt (struct comedi_device*) ; 
 int /*<<< orphan*/  handle_gpct_interrupt (struct comedi_device*,int) ; 
 unsigned int mite_get_status (TYPE_1__*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned short stub1 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned short stub2 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t ni_E_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	unsigned short a_status;
	unsigned short b_status;
	unsigned int ai_mite_status = 0;
	unsigned int ao_mite_status = 0;
	unsigned long flags;
#ifdef PCIDMA
	struct mite_struct *mite = devpriv->mite;
#endif

	if (dev->attached == 0)
		return IRQ_NONE;
	smp_mb();		/*  make sure dev->attached is checked before handler does anything else. */

	/*  lock to avoid race with comedi_poll */
	spin_lock_irqsave(&dev->spinlock, flags);
	a_status = devpriv->stc_readw(dev, AI_Status_1_Register);
	b_status = devpriv->stc_readw(dev, AO_Status_1_Register);
#ifdef PCIDMA
	if (mite) {
		unsigned long flags_too;

		spin_lock_irqsave(&devpriv->mite_channel_lock, flags_too);
		if (devpriv->ai_mite_chan) {
			ai_mite_status = mite_get_status(devpriv->ai_mite_chan);
			if (ai_mite_status & CHSR_LINKC)
				writel(CHOR_CLRLC,
				       devpriv->mite->mite_io_addr +
				       MITE_CHOR(devpriv->
						 ai_mite_chan->channel));
		}
		if (devpriv->ao_mite_chan) {
			ao_mite_status = mite_get_status(devpriv->ao_mite_chan);
			if (ao_mite_status & CHSR_LINKC)
				writel(CHOR_CLRLC,
				       mite->mite_io_addr +
				       MITE_CHOR(devpriv->
						 ao_mite_chan->channel));
		}
		spin_unlock_irqrestore(&devpriv->mite_channel_lock, flags_too);
	}
#endif
	ack_a_interrupt(dev, a_status);
	ack_b_interrupt(dev, b_status);
	if ((a_status & Interrupt_A_St) || (ai_mite_status & CHSR_INT))
		handle_a_interrupt(dev, a_status, ai_mite_status);
	if ((b_status & Interrupt_B_St) || (ao_mite_status & CHSR_INT))
		handle_b_interrupt(dev, b_status, ao_mite_status);
	handle_gpct_interrupt(dev, 0);
	handle_gpct_interrupt(dev, 1);
	handle_cdio_interrupt(dev);

	spin_unlock_irqrestore(&dev->spinlock, flags);
	return IRQ_HANDLED;
}