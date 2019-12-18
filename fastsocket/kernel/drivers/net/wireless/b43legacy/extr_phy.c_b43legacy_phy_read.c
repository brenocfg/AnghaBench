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
typedef  int /*<<< orphan*/  u16 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_PHY_CONTROL ; 
 int /*<<< orphan*/  B43legacy_MMIO_PHY_DATA ; 
 int /*<<< orphan*/  b43legacy_read16 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 b43legacy_phy_read(struct b43legacy_wldev *dev, u16 offset)
{
	b43legacy_write16(dev, B43legacy_MMIO_PHY_CONTROL, offset);
	return b43legacy_read16(dev, B43legacy_MMIO_PHY_DATA);
}