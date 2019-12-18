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
struct dma_info {int txdalign; int rxdalign; struct dma_info* rxp; struct dma_info* txp; int /*<<< orphan*/  rxdpaorig; scalar_t__ rxd64; int /*<<< orphan*/  rxdalloc; int /*<<< orphan*/  dmadev; int /*<<< orphan*/  txdpaorig; scalar_t__ txd64; int /*<<< orphan*/  txdalloc; int /*<<< orphan*/  name; int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_dbg_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dma_info*) ; 

void dma_detach(struct dma_pub *pub)
{
	struct dma_info *di = (struct dma_info *)pub;

	brcms_dbg_dma(di->core, "%s:\n", di->name);

	/* free dma descriptor rings */
	if (di->txd64)
		dma_free_coherent(di->dmadev, di->txdalloc,
				  ((s8 *)di->txd64 - di->txdalign),
				  (di->txdpaorig));
	if (di->rxd64)
		dma_free_coherent(di->dmadev, di->rxdalloc,
				  ((s8 *)di->rxd64 - di->rxdalign),
				  (di->rxdpaorig));

	/* free packet pointer vectors */
	kfree(di->txp);
	kfree(di->rxp);

	/* free our private info structure */
	kfree(di);

}