#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mite_struct {int /*<<< orphan*/  lock; scalar_t__ mite_io_addr; } ;
struct mite_channel {int /*<<< orphan*/  channel; scalar_t__ done; struct mite_struct* mite; } ;

/* Variables and functions */
 int CHOR_START ; 
 int /*<<< orphan*/  MDPRINTK (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MITE_CHOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void mite_dma_arm(struct mite_channel *mite_chan)
{
	struct mite_struct *mite = mite_chan->mite;
	int chor;
	unsigned long flags;

	MDPRINTK("mite_dma_arm ch%i\n", channel);
	/* memory barrier is intended to insure any twiddling with the buffer
	   is done before writing to the mite to arm dma transfer */
	smp_mb();
	/* arm */
	chor = CHOR_START;
	spin_lock_irqsave(&mite->lock, flags);
	mite_chan->done = 0;
	writel(chor, mite->mite_io_addr + MITE_CHOR(mite_chan->channel));
	mmiowb();
	spin_unlock_irqrestore(&mite->lock, flags);
/*       mite_dma_tcr(mite, channel); */
}