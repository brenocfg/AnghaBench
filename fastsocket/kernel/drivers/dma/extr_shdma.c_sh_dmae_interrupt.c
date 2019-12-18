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
typedef  int u32 ;
struct sh_dmae_chan {int /*<<< orphan*/  tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR ; 
 int CHCR_TE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dmae_halt (struct sh_dmae_chan*) ; 
 int sh_dmae_readl (struct sh_dmae_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sh_dmae_interrupt(int irq, void *data)
{
	irqreturn_t ret = IRQ_NONE;
	struct sh_dmae_chan *sh_chan = (struct sh_dmae_chan *)data;
	u32 chcr = sh_dmae_readl(sh_chan, CHCR);

	if (chcr & CHCR_TE) {
		/* DMA stop */
		dmae_halt(sh_chan);

		ret = IRQ_HANDLED;
		tasklet_schedule(&sh_chan->tasklet);
	}

	return ret;
}