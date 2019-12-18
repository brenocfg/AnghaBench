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
struct mite_struct {scalar_t__ mite_io_addr; } ;
struct mite_channel {int /*<<< orphan*/  channel; struct mite_struct* mite; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDPRINTK (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ MITE_LKAR (int /*<<< orphan*/ ) ; 
 scalar_t__ MITE_TCR (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

unsigned mite_dma_tcr(struct mite_channel *mite_chan)
{
	struct mite_struct *mite = mite_chan->mite;
	int tcr;
	int lkar;

	lkar = readl(mite->mite_io_addr + MITE_LKAR(mite_chan->channel));
	tcr = readl(mite->mite_io_addr + MITE_TCR(mite_chan->channel));
	MDPRINTK("mite_dma_tcr ch%i, lkar=0x%08x tcr=%d\n", mite_chan->channel,
		 lkar, tcr);

	return tcr;
}