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
struct dma_pub {int dummy; } ;
struct dma_info {int nrxd; int /*<<< orphan*/  rxdpa; scalar_t__ aligndesc_4k; int /*<<< orphan*/  rxd64; scalar_t__ rxout; scalar_t__ rxin; int /*<<< orphan*/  name; int /*<<< orphan*/  core; } ;
struct dma64desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX ; 
 int /*<<< orphan*/  _dma_ddtable_init (struct dma_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _dma_rxenable (struct dma_info*) ; 
 int /*<<< orphan*/  brcms_dbg_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 

void dma_rxinit(struct dma_pub *pub)
{
	struct dma_info *di = (struct dma_info *)pub;

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	if (di->nrxd == 0)
		return;

	di->rxin = di->rxout = 0;

	/* clear rx descriptor ring */
	memset(di->rxd64, '\0', di->nrxd * sizeof(struct dma64desc));

	/* DMA engine with out alignment requirement requires table to be inited
	 * before enabling the engine
	 */
	if (!di->aligndesc_4k)
		_dma_ddtable_init(di, DMA_RX, di->rxdpa);

	_dma_rxenable(di);

	if (di->aligndesc_4k)
		_dma_ddtable_init(di, DMA_RX, di->rxdpa);
}