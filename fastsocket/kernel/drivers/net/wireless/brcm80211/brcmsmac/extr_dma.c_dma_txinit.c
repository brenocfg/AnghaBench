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
typedef  int /*<<< orphan*/  u32 ;
struct dma_pub {int dummy; } ;
struct TYPE_2__ {int txavail; int dmactrlflags; } ;
struct dma_info {int ntxd; int /*<<< orphan*/  txdpa; scalar_t__ aligndesc_4k; int /*<<< orphan*/  core; TYPE_1__ dma; int /*<<< orphan*/  txd64; scalar_t__ txout; scalar_t__ txin; int /*<<< orphan*/  name; } ;
struct dma64desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D64_XC_PD ; 
 int /*<<< orphan*/  D64_XC_XE ; 
 int /*<<< orphan*/  DMA64TXREGOFFS (struct dma_info*,int /*<<< orphan*/ ) ; 
 int DMA_CTRL_PEN ; 
 int /*<<< orphan*/  DMA_TX ; 
 int /*<<< orphan*/  _dma_ddtable_init (struct dma_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_dbg_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 

void dma_txinit(struct dma_pub *pub)
{
	struct dma_info *di = (struct dma_info *)pub;
	u32 control = D64_XC_XE;

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	if (di->ntxd == 0)
		return;

	di->txin = di->txout = 0;
	di->dma.txavail = di->ntxd - 1;

	/* clear tx descriptor ring */
	memset(di->txd64, '\0', (di->ntxd * sizeof(struct dma64desc)));

	/* DMA engine with out alignment requirement requires table to be inited
	 * before enabling the engine
	 */
	if (!di->aligndesc_4k)
		_dma_ddtable_init(di, DMA_TX, di->txdpa);

	if ((di->dma.dmactrlflags & DMA_CTRL_PEN) == 0)
		control |= D64_XC_PD;
	bcma_set32(di->core, DMA64TXREGOFFS(di, control), control);

	/* DMA engine with alignment requirement requires table to be inited
	 * before enabling the engine
	 */
	if (di->aligndesc_4k)
		_dma_ddtable_init(di, DMA_TX, di->txdpa);
}