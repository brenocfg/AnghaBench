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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int bus_type; int /*<<< orphan*/  sdev; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
#define  B43_BUS_BCMA 129 
#define  B43_BUS_SSB 128 
 int B43_DMA32_TXADDREXT_MASK ; 
 scalar_t__ B43_DMA32_TXCTL ; 
 int /*<<< orphan*/  BCMA_IOST ; 
 int BCMA_IOST_DMA64 ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  SSB_TMSHIGH ; 
 int SSB_TMSHIGH_DMA64 ; 
 scalar_t__ b43_dmacontroller_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int b43_read32 (struct b43_wldev*,scalar_t__) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,scalar_t__,int) ; 
 int bcma_aread32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssb_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 supported_dma_mask(struct b43_wldev *dev)
{
	u32 tmp;
	u16 mmio_base;

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_aread32(dev->dev->bdev, BCMA_IOST);
		if (tmp & BCMA_IOST_DMA64)
			return DMA_BIT_MASK(64);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_read32(dev->dev->sdev, SSB_TMSHIGH);
		if (tmp & SSB_TMSHIGH_DMA64)
			return DMA_BIT_MASK(64);
		break;
#endif
	}

	mmio_base = b43_dmacontroller_base(0, 0);
	b43_write32(dev, mmio_base + B43_DMA32_TXCTL, B43_DMA32_TXADDREXT_MASK);
	tmp = b43_read32(dev, mmio_base + B43_DMA32_TXCTL);
	if (tmp & B43_DMA32_TXADDREXT_MASK)
		return DMA_BIT_MASK(32);

	return DMA_BIT_MASK(30);
}