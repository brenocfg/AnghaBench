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
struct pnx4008_dma_config {int is_ll; void* dest_addr; void* src_addr; void* ll_dma; void* ch_ctrl; void* ch_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_Cx_CONFIG (int) ; 
 int /*<<< orphan*/  DMAC_Cx_CONTROL (int) ; 
 int /*<<< orphan*/  DMAC_Cx_DEST_ADDR (int) ; 
 int /*<<< orphan*/  DMAC_Cx_LLI (int) ; 
 int /*<<< orphan*/  DMAC_Cx_SRC_ADDR (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  VALID_CHANNEL (int) ; 
 void* __raw_readl (int /*<<< orphan*/ ) ; 
 TYPE_1__* dma_channels ; 
 int /*<<< orphan*/  pnx4008_dma_lock () ; 
 int /*<<< orphan*/  pnx4008_dma_unlock () ; 

int pnx4008_channel_get_config(int ch, struct pnx4008_dma_config * config)
{
	if (!VALID_CHANNEL(ch) || !dma_channels[ch].name || !config)
		return -EINVAL;

	pnx4008_dma_lock();
	config->ch_cfg = __raw_readl(DMAC_Cx_CONFIG(ch));
	config->ch_ctrl = __raw_readl(DMAC_Cx_CONTROL(ch));

	config->ll_dma = __raw_readl(DMAC_Cx_LLI(ch));
	config->is_ll = config->ll_dma ? 1 : 0;

	config->src_addr = __raw_readl(DMAC_Cx_SRC_ADDR(ch));
	config->dest_addr = __raw_readl(DMAC_Cx_DEST_ADDR(ch));
	pnx4008_dma_unlock();

	return 0;
}