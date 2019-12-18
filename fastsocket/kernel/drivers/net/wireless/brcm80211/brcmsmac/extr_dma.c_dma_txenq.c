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
typedef  int /*<<< orphan*/  uint ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {unsigned char* data; int /*<<< orphan*/  len; } ;
struct dma_info {int txout; scalar_t__ txin; int ntxd; struct sk_buff** txp; int /*<<< orphan*/  txd64; int /*<<< orphan*/  dmadev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int D64_CTRL1_EOF ; 
 int D64_CTRL1_EOT ; 
 int D64_CTRL1_IOC ; 
 int D64_CTRL1_SOF ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dma64_dd_upd (struct dma_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nexttxd (struct dma_info*,int) ; 
 size_t prevtxd (struct dma_info*,int) ; 

__attribute__((used)) static void dma_txenq(struct dma_info *di, struct sk_buff *p)
{
	unsigned char *data;
	uint len;
	u16 txout;
	u32 flags = 0;
	dma_addr_t pa;

	txout = di->txout;

	if (WARN_ON(nexttxd(di, txout) == di->txin))
		return;

	/*
	 * obtain and initialize transmit descriptor entry.
	 */
	data = p->data;
	len = p->len;

	/* get physical address of buffer start */
	pa = dma_map_single(di->dmadev, data, len, DMA_TO_DEVICE);

	/* With a DMA segment list, Descriptor table is filled
	 * using the segment list instead of looping over
	 * buffers in multi-chain DMA. Therefore, EOF for SGLIST
	 * is when end of segment list is reached.
	 */
	flags = D64_CTRL1_SOF | D64_CTRL1_IOC | D64_CTRL1_EOF;
	if (txout == (di->ntxd - 1))
		flags |= D64_CTRL1_EOT;

	dma64_dd_upd(di, di->txd64, pa, txout, &flags, len);

	txout = nexttxd(di, txout);

	/* save the packet */
	di->txp[prevtxd(di, txout)] = p;

	/* bump the tx descriptor index */
	di->txout = txout;
}