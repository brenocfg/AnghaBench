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
struct s3c2410_dma_chan {scalar_t__ regs; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ PL080S_CH_CONFIG ; 
 scalar_t__ PL080S_CH_CONTROL2 ; 
 scalar_t__ PL080_CH_CONTROL ; 
 scalar_t__ PL080_CH_DST_ADDR ; 
 scalar_t__ PL080_CH_LLI ; 
 scalar_t__ PL080_CH_SRC_ADDR ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void dbg_showchan(struct s3c2410_dma_chan *chan)
{
	pr_debug("DMA%d: %08x->%08x L %08x C %08x,%08x S %08x\n",
		 chan->number,
		 readl(chan->regs + PL080_CH_SRC_ADDR),
		 readl(chan->regs + PL080_CH_DST_ADDR),
		 readl(chan->regs + PL080_CH_LLI),
		 readl(chan->regs + PL080_CH_CONTROL),
		 readl(chan->regs + PL080S_CH_CONTROL2),
		 readl(chan->regs + PL080S_CH_CONFIG));
}