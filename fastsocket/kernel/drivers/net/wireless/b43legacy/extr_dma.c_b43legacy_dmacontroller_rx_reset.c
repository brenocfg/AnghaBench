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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; } ;
typedef  enum b43legacy_dmatype { ____Placeholder_b43legacy_dmatype } b43legacy_dmatype ;

/* Variables and functions */
 scalar_t__ B43legacy_DMA32_RXCTL ; 
 int /*<<< orphan*/  B43legacy_DMA32_RXSTATE ; 
 scalar_t__ B43legacy_DMA32_RXSTATUS ; 
 int /*<<< orphan*/  B43legacy_DMA32_RXSTAT_DISABLED ; 
 int ENODEV ; 
 int /*<<< orphan*/  b43legacy_read32 (struct b43legacy_wldev*,scalar_t__) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int b43legacy_dmacontroller_rx_reset(struct b43legacy_wldev *dev,
					    u16 mmio_base,
					    enum b43legacy_dmatype type)
{
	int i;
	u32 value;
	u16 offset;

	might_sleep();

	offset = B43legacy_DMA32_RXCTL;
	b43legacy_write32(dev, mmio_base + offset, 0);
	for (i = 0; i < 10; i++) {
		offset = B43legacy_DMA32_RXSTATUS;
		value = b43legacy_read32(dev, mmio_base + offset);
		value &= B43legacy_DMA32_RXSTATE;
		if (value == B43legacy_DMA32_RXSTAT_DISABLED) {
			i = -1;
			break;
		}
		msleep(1);
	}
	if (i != -1) {
		b43legacyerr(dev->wl, "DMA RX reset timed out\n");
		return -ENODEV;
	}

	return 0;
}