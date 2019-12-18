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
typedef  int /*<<< orphan*/  u64 ;
struct b43_dma {int parity; void* rx_ring; void* tx_ring_mcast; void* tx_ring_AC_VO; void* tx_ring_AC_VI; void* tx_ring_AC_BE; void* tx_ring_AC_BK; int /*<<< orphan*/  translation_in_low; int /*<<< orphan*/  translation; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; struct b43_dma dma; } ;
typedef  enum b43_dmatype { ____Placeholder_b43_dmatype } b43_dmatype ;
struct TYPE_2__ {int bus_type; int core_rev; int /*<<< orphan*/  sdev; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
#define  B43_BUS_BCMA 129 
#define  B43_BUS_SSB 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int ENOMEM ; 
 int b43_dma_set_mask (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_dma_translation_in_low_word (struct b43_wldev*,int) ; 
 void* b43_setup_dmaring (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  bcma_core_dma_translation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_ring (struct b43_dma*,int /*<<< orphan*/ ) ; 
 int dma_mask_to_engine_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_dma_translation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supported_dma_mask (struct b43_wldev*) ; 
 int /*<<< orphan*/  tx_ring_AC_BE ; 
 int /*<<< orphan*/  tx_ring_AC_BK ; 
 int /*<<< orphan*/  tx_ring_AC_VI ; 
 int /*<<< orphan*/  tx_ring_AC_VO ; 
 int /*<<< orphan*/  tx_ring_mcast ; 

int b43_dma_init(struct b43_wldev *dev)
{
	struct b43_dma *dma = &dev->dma;
	int err;
	u64 dmamask;
	enum b43_dmatype type;

	dmamask = supported_dma_mask(dev);
	type = dma_mask_to_engine_type(dmamask);
	err = b43_dma_set_mask(dev, dmamask);
	if (err)
		return err;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		dma->translation = bcma_core_dma_translation(dev->dev->bdev);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		dma->translation = ssb_dma_translation(dev->dev->sdev);
		break;
#endif
	}
	dma->translation_in_low = b43_dma_translation_in_low_word(dev, type);

	dma->parity = true;
#ifdef CONFIG_B43_BCMA
	/* TODO: find out which SSB devices need disabling parity */
	if (dev->dev->bus_type == B43_BUS_BCMA)
		dma->parity = false;
#endif

	err = -ENOMEM;
	/* setup TX DMA channels. */
	dma->tx_ring_AC_BK = b43_setup_dmaring(dev, 0, 1, type);
	if (!dma->tx_ring_AC_BK)
		goto out;

	dma->tx_ring_AC_BE = b43_setup_dmaring(dev, 1, 1, type);
	if (!dma->tx_ring_AC_BE)
		goto err_destroy_bk;

	dma->tx_ring_AC_VI = b43_setup_dmaring(dev, 2, 1, type);
	if (!dma->tx_ring_AC_VI)
		goto err_destroy_be;

	dma->tx_ring_AC_VO = b43_setup_dmaring(dev, 3, 1, type);
	if (!dma->tx_ring_AC_VO)
		goto err_destroy_vi;

	dma->tx_ring_mcast = b43_setup_dmaring(dev, 4, 1, type);
	if (!dma->tx_ring_mcast)
		goto err_destroy_vo;

	/* setup RX DMA channel. */
	dma->rx_ring = b43_setup_dmaring(dev, 0, 0, type);
	if (!dma->rx_ring)
		goto err_destroy_mcast;

	/* No support for the TX status DMA ring. */
	B43_WARN_ON(dev->dev->core_rev < 5);

	b43dbg(dev->wl, "%u-bit DMA initialized\n",
	       (unsigned int)type);
	err = 0;
out:
	return err;

err_destroy_mcast:
	destroy_ring(dma, tx_ring_mcast);
err_destroy_vo:
	destroy_ring(dma, tx_ring_AC_VO);
err_destroy_vi:
	destroy_ring(dma, tx_ring_AC_VI);
err_destroy_be:
	destroy_ring(dma, tx_ring_AC_BE);
err_destroy_bk:
	destroy_ring(dma, tx_ring_AC_BK);
	return err;
}