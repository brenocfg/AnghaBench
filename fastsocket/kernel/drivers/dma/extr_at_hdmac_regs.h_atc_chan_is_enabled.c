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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct at_dma_chan {int mask; TYPE_1__ chan_common; } ;
struct at_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSR ; 
 int dma_readl (struct at_dma*,int /*<<< orphan*/ ) ; 
 struct at_dma* to_at_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int atc_chan_is_enabled(struct at_dma_chan *atchan)
{
	struct at_dma	*atdma = to_at_dma(atchan->chan_common.device);

	return !!(dma_readl(atdma, CHSR) & atchan->mask);
}