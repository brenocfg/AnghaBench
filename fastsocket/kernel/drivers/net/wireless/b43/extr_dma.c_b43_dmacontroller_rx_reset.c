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
struct b43_wldev {int /*<<< orphan*/  wl; } ;
typedef  enum b43_dmatype { ____Placeholder_b43_dmatype } b43_dmatype ;

/* Variables and functions */
 scalar_t__ B43_DMA32_RXCTL ; 
 int /*<<< orphan*/  B43_DMA32_RXSTATE ; 
 scalar_t__ B43_DMA32_RXSTATUS ; 
 int /*<<< orphan*/  B43_DMA32_RXSTAT_DISABLED ; 
 scalar_t__ B43_DMA64_RXCTL ; 
 int /*<<< orphan*/  B43_DMA64_RXSTAT ; 
 scalar_t__ B43_DMA64_RXSTATUS ; 
 int /*<<< orphan*/  B43_DMA64_RXSTAT_DISABLED ; 
 int B43_DMA_64BIT ; 
 int ENODEV ; 
 int /*<<< orphan*/  b43_read32 (struct b43_wldev*,scalar_t__) ; 
 int /*<<< orphan*/  b43_write32 (struct b43_wldev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int b43_dmacontroller_rx_reset(struct b43_wldev *dev, u16 mmio_base,
				      enum b43_dmatype type)
{
	int i;
	u32 value;
	u16 offset;

	might_sleep();

	offset = (type == B43_DMA_64BIT) ? B43_DMA64_RXCTL : B43_DMA32_RXCTL;
	b43_write32(dev, mmio_base + offset, 0);
	for (i = 0; i < 10; i++) {
		offset = (type == B43_DMA_64BIT) ? B43_DMA64_RXSTATUS :
						   B43_DMA32_RXSTATUS;
		value = b43_read32(dev, mmio_base + offset);
		if (type == B43_DMA_64BIT) {
			value &= B43_DMA64_RXSTAT;
			if (value == B43_DMA64_RXSTAT_DISABLED) {
				i = -1;
				break;
			}
		} else {
			value &= B43_DMA32_RXSTATE;
			if (value == B43_DMA32_RXSTAT_DISABLED) {
				i = -1;
				break;
			}
		}
		msleep(1);
	}
	if (i != -1) {
		b43err(dev->wl, "DMA RX reset timed out\n");
		return -ENODEV;
	}

	return 0;
}