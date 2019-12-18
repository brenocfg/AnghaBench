#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pnx4008_dma_config {int /*<<< orphan*/  ch_cfg; int /*<<< orphan*/  ch_ctrl; int /*<<< orphan*/  ll_dma; scalar_t__ is_ll; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  src_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_Cx_CONFIG (int) ; 
 int /*<<< orphan*/  DMAC_Cx_CONTROL (int) ; 
 int /*<<< orphan*/  DMAC_Cx_DEST_ADDR (int) ; 
 int /*<<< orphan*/  DMAC_Cx_LLI (int) ; 
 int /*<<< orphan*/  DMAC_Cx_SRC_ADDR (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  VALID_CHANNEL (int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dma_channels ; 
 int /*<<< orphan*/  pnx4008_dma_lock () ; 
 int /*<<< orphan*/  pnx4008_dma_unlock () ; 

int pnx4008_config_channel(int ch, struct pnx4008_dma_config * config)
{
	if (!VALID_CHANNEL(ch) || !dma_channels[ch].name)
		return -EINVAL;

	pnx4008_dma_lock();
	__raw_writel(config->src_addr, DMAC_Cx_SRC_ADDR(ch));
	__raw_writel(config->dest_addr, DMAC_Cx_DEST_ADDR(ch));

	if (config->is_ll)
		__raw_writel(config->ll_dma, DMAC_Cx_LLI(ch));
	else
		__raw_writel(0, DMAC_Cx_LLI(ch));

	__raw_writel(config->ch_ctrl, DMAC_Cx_CONTROL(ch));
	__raw_writel(config->ch_cfg, DMAC_Cx_CONFIG(ch));
	pnx4008_dma_unlock();

	return 0;

}