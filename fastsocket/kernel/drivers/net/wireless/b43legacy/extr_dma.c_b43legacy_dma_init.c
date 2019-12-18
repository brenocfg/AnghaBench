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
typedef  int /*<<< orphan*/  u64 ;
struct b43legacy_dma {struct b43legacy_dmaring* tx_ring0; struct b43legacy_dmaring* tx_ring1; struct b43legacy_dmaring* tx_ring2; struct b43legacy_dmaring* tx_ring3; struct b43legacy_dmaring* tx_ring4; struct b43legacy_dmaring* tx_ring5; struct b43legacy_dmaring* rx_ring0; struct b43legacy_dmaring* rx_ring3; int /*<<< orphan*/  translation; } ;
struct b43legacy_wldev {int __using_pio; int /*<<< orphan*/  wl; TYPE_2__* dev; struct b43legacy_dma dma; } ;
struct b43legacy_dmaring {int dummy; } ;
typedef  enum b43legacy_dmatype { ____Placeholder_b43legacy_dmatype } b43legacy_dmatype ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  b43legacy_destroy_dmaring (struct b43legacy_dmaring*) ; 
 int b43legacy_dma_set_mask (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 struct b43legacy_dmaring* b43legacy_setup_dmaring (struct b43legacy_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43legacydbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  b43legacywarn (int /*<<< orphan*/ ,char*) ; 
 int dma_mask_to_engine_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_dma_translation (TYPE_2__*) ; 
 int /*<<< orphan*/  supported_dma_mask (struct b43legacy_wldev*) ; 

int b43legacy_dma_init(struct b43legacy_wldev *dev)
{
	struct b43legacy_dma *dma = &dev->dma;
	struct b43legacy_dmaring *ring;
	int err;
	u64 dmamask;
	enum b43legacy_dmatype type;

	dmamask = supported_dma_mask(dev);
	type = dma_mask_to_engine_type(dmamask);
	err = b43legacy_dma_set_mask(dev, dmamask);
	if (err) {
#ifdef CONFIG_B43LEGACY_PIO
		b43legacywarn(dev->wl, "DMA for this device not supported. "
			"Falling back to PIO\n");
		dev->__using_pio = true;
		return -EAGAIN;
#else
		b43legacyerr(dev->wl, "DMA for this device not supported and "
		       "no PIO support compiled in\n");
		return -EOPNOTSUPP;
#endif
	}
	dma->translation = ssb_dma_translation(dev->dev);

	err = -ENOMEM;
	/* setup TX DMA channels. */
	ring = b43legacy_setup_dmaring(dev, 0, 1, type);
	if (!ring)
		goto out;
	dma->tx_ring0 = ring;

	ring = b43legacy_setup_dmaring(dev, 1, 1, type);
	if (!ring)
		goto err_destroy_tx0;
	dma->tx_ring1 = ring;

	ring = b43legacy_setup_dmaring(dev, 2, 1, type);
	if (!ring)
		goto err_destroy_tx1;
	dma->tx_ring2 = ring;

	ring = b43legacy_setup_dmaring(dev, 3, 1, type);
	if (!ring)
		goto err_destroy_tx2;
	dma->tx_ring3 = ring;

	ring = b43legacy_setup_dmaring(dev, 4, 1, type);
	if (!ring)
		goto err_destroy_tx3;
	dma->tx_ring4 = ring;

	ring = b43legacy_setup_dmaring(dev, 5, 1, type);
	if (!ring)
		goto err_destroy_tx4;
	dma->tx_ring5 = ring;

	/* setup RX DMA channels. */
	ring = b43legacy_setup_dmaring(dev, 0, 0, type);
	if (!ring)
		goto err_destroy_tx5;
	dma->rx_ring0 = ring;

	if (dev->dev->id.revision < 5) {
		ring = b43legacy_setup_dmaring(dev, 3, 0, type);
		if (!ring)
			goto err_destroy_rx0;
		dma->rx_ring3 = ring;
	}

	b43legacydbg(dev->wl, "%u-bit DMA initialized\n", (unsigned int)type);
	err = 0;
out:
	return err;

err_destroy_rx0:
	b43legacy_destroy_dmaring(dma->rx_ring0);
	dma->rx_ring0 = NULL;
err_destroy_tx5:
	b43legacy_destroy_dmaring(dma->tx_ring5);
	dma->tx_ring5 = NULL;
err_destroy_tx4:
	b43legacy_destroy_dmaring(dma->tx_ring4);
	dma->tx_ring4 = NULL;
err_destroy_tx3:
	b43legacy_destroy_dmaring(dma->tx_ring3);
	dma->tx_ring3 = NULL;
err_destroy_tx2:
	b43legacy_destroy_dmaring(dma->tx_ring2);
	dma->tx_ring2 = NULL;
err_destroy_tx1:
	b43legacy_destroy_dmaring(dma->tx_ring1);
	dma->tx_ring1 = NULL;
err_destroy_tx0:
	b43legacy_destroy_dmaring(dma->tx_ring0);
	dma->tx_ring0 = NULL;
	goto out;
}