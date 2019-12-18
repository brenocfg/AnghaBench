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
struct dw_dma_chan {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SAR ; 
 int /*<<< orphan*/  channel_readl (struct dw_dma_chan*,int /*<<< orphan*/ ) ; 
 struct dw_dma_chan* to_dw_dma_chan (struct dma_chan*) ; 

inline dma_addr_t dw_dma_get_src_addr(struct dma_chan *chan)
{
	struct dw_dma_chan *dwc = to_dw_dma_chan(chan);
	return channel_readl(dwc, SAR);
}