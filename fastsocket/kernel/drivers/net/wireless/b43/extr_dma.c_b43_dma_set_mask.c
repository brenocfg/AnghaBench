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
typedef  scalar_t__ u64 ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  b43info (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 scalar_t__ dma_mask_to_engine_type (scalar_t__) ; 
 int dma_set_coherent_mask (int /*<<< orphan*/ ,scalar_t__) ; 
 int dma_set_mask (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int b43_dma_set_mask(struct b43_wldev *dev, u64 mask)
{
	u64 orig_mask = mask;
	bool fallback = false;
	int err;

	/* Try to set the DMA mask. If it fails, try falling back to a
	 * lower mask, as we can always also support a lower one. */
	while (1) {
		err = dma_set_mask(dev->dev->dma_dev, mask);
		if (!err) {
			err = dma_set_coherent_mask(dev->dev->dma_dev, mask);
			if (!err)
				break;
		}
		if (mask == DMA_BIT_MASK(64)) {
			mask = DMA_BIT_MASK(32);
			fallback = true;
			continue;
		}
		if (mask == DMA_BIT_MASK(32)) {
			mask = DMA_BIT_MASK(30);
			fallback = true;
			continue;
		}
		b43err(dev->wl, "The machine/kernel does not support "
		       "the required %u-bit DMA mask\n",
		       (unsigned int)dma_mask_to_engine_type(orig_mask));
		return -EOPNOTSUPP;
	}
	if (fallback) {
		b43info(dev->wl, "DMA mask fallback from %u-bit to %u-bit\n",
			(unsigned int)dma_mask_to_engine_type(orig_mask),
			(unsigned int)dma_mask_to_engine_type(mask));
	}

	return 0;
}