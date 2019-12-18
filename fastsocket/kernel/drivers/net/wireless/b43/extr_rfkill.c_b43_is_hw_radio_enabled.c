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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_RADIO_HWENABLED_HI ; 
 int B43_MMIO_RADIO_HWENABLED_HI_MASK ; 
 int b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 

bool b43_is_hw_radio_enabled(struct b43_wldev *dev)
{
	return !(b43_read32(dev, B43_MMIO_RADIO_HWENABLED_HI)
		& B43_MMIO_RADIO_HWENABLED_HI_MASK);
}