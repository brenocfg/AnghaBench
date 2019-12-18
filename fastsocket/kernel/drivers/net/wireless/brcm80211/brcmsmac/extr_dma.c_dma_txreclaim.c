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
struct sk_buff {int dummy; } ;
struct dma_pub {int dummy; } ;
struct TYPE_2__ {int dmactrlflags; } ;
struct dma_info {scalar_t__ txin; scalar_t__ txout; TYPE_1__ dma; int /*<<< orphan*/  name; int /*<<< orphan*/  core; } ;
typedef  enum txd_range { ____Placeholder_txd_range } txd_range ;

/* Variables and functions */
 int DMA_CTRL_UNFRAMED ; 
 int DMA_RANGE_ALL ; 
 int DMA_RANGE_TRANSMITTED ; 
 int /*<<< orphan*/  brcms_dbg_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 struct sk_buff* dma_getnexttxp (struct dma_pub*,int) ; 

void dma_txreclaim(struct dma_pub *pub, enum txd_range range)
{
	struct dma_info *di = (struct dma_info *)pub;
	struct sk_buff *p;

	brcms_dbg_dma(di->core, "%s: %s\n",
		      di->name,
		      range == DMA_RANGE_ALL ? "all" :
		      range == DMA_RANGE_TRANSMITTED ? "transmitted" :
		      "transferred");

	if (di->txin == di->txout)
		return;

	while ((p = dma_getnexttxp(pub, range))) {
		/* For unframed data, we don't have any packets to free */
		if (!(di->dma.dmactrlflags & DMA_CTRL_UNFRAMED))
			brcmu_pkt_buf_free_skb(p);
	}
}