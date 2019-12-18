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
struct gelic_descr {int /*<<< orphan*/  dmac_cmd_status; } ;
typedef  enum gelic_descr_dma_status { ____Placeholder_gelic_descr_dma_status } gelic_descr_dma_status ;

/* Variables and functions */
 int GELIC_DESCR_DMA_STAT_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum gelic_descr_dma_status
gelic_descr_get_status(struct gelic_descr *descr)
{
	return be32_to_cpu(descr->dmac_cmd_status) & GELIC_DESCR_DMA_STAT_MASK;
}