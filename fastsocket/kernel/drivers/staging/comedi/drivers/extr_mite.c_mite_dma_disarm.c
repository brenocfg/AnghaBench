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
 unsigned int CHOR_ABORT ; 
 scalar_t__ MITE_CHOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

void mite_dma_disarm(struct mite_channel *mite_chan)
{
	struct mite_struct *mite = mite_chan->mite;
	unsigned chor;

	/* disarm */
	chor = CHOR_ABORT;
	writel(chor, mite->mite_io_addr + MITE_CHOR(mite_chan->channel));
}