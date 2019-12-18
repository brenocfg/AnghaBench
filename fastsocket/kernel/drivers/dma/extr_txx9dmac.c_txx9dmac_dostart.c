#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct txx9dmac_slave {int reg_width; scalar_t__ tx_reg; } ;
struct TYPE_3__ {int phys; int /*<<< orphan*/  cookie; } ;
struct txx9dmac_desc {TYPE_1__ txd; } ;
struct TYPE_4__ {struct txx9dmac_slave* private; } ;
struct txx9dmac_chan {int ccr; TYPE_2__ chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CHAR ; 
 int /*<<< orphan*/  CNTR ; 
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  DAIR ; 
 int /*<<< orphan*/  SAIR ; 
 int TXX9_DMA_CSR_XFACT ; 
 int /*<<< orphan*/  chan2dev (TYPE_2__*) ; 
 int /*<<< orphan*/  channel32_writel (struct txx9dmac_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  channel64_write_CHAR (struct txx9dmac_chan*,int) ; 
 int /*<<< orphan*/  channel64_writel (struct txx9dmac_chan*,int /*<<< orphan*/ ,int) ; 
 int channel_readl (struct txx9dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct txx9dmac_desc*) ; 
 scalar_t__ is_dmac64 (struct txx9dmac_chan*) ; 
 scalar_t__ txx9_dma_have_SMPCHN () ; 
 int /*<<< orphan*/  txx9dmac_dump_regs (struct txx9dmac_chan*) ; 

__attribute__((used)) static void txx9dmac_dostart(struct txx9dmac_chan *dc,
			     struct txx9dmac_desc *first)
{
	struct txx9dmac_slave *ds = dc->chan.private;
	u32 sai, dai;

	dev_vdbg(chan2dev(&dc->chan), "dostart %u %p\n",
		 first->txd.cookie, first);
	/* ASSERT:  channel is idle */
	if (channel_readl(dc, CSR) & TXX9_DMA_CSR_XFACT) {
		dev_err(chan2dev(&dc->chan),
			"BUG: Attempted to start non-idle channel\n");
		txx9dmac_dump_regs(dc);
		/* The tasklet will hopefully advance the queue... */
		return;
	}

	if (is_dmac64(dc)) {
		channel64_writel(dc, CNTR, 0);
		channel64_writel(dc, CSR, 0xffffffff);
		if (ds) {
			if (ds->tx_reg) {
				sai = ds->reg_width;
				dai = 0;
			} else {
				sai = 0;
				dai = ds->reg_width;
			}
		} else {
			sai = 8;
			dai = 8;
		}
		channel64_writel(dc, SAIR, sai);
		channel64_writel(dc, DAIR, dai);
		/* All 64-bit DMAC supports SMPCHN */
		channel64_writel(dc, CCR, dc->ccr);
		/* Writing a non zero value to CHAR will assert XFACT */
		channel64_write_CHAR(dc, first->txd.phys);
	} else {
		channel32_writel(dc, CNTR, 0);
		channel32_writel(dc, CSR, 0xffffffff);
		if (ds) {
			if (ds->tx_reg) {
				sai = ds->reg_width;
				dai = 0;
			} else {
				sai = 0;
				dai = ds->reg_width;
			}
		} else {
			sai = 4;
			dai = 4;
		}
		channel32_writel(dc, SAIR, sai);
		channel32_writel(dc, DAIR, dai);
		if (txx9_dma_have_SMPCHN()) {
			channel32_writel(dc, CCR, dc->ccr);
			/* Writing a non zero value to CHAR will assert XFACT */
			channel32_writel(dc, CHAR, first->txd.phys);
		} else {
			channel32_writel(dc, CHAR, first->txd.phys);
			channel32_writel(dc, CCR, dc->ccr);
		}
	}
}