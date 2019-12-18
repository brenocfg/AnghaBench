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
 int /*<<< orphan*/  B43_MMIO_BTCOEX_CTL ; 
 int /*<<< orphan*/  B43_MMIO_BTCOEX_TXCTL ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpphy_btcoex_override(struct b43_wldev *dev)
{
	b43_write16(dev, B43_MMIO_BTCOEX_CTL, 0x3);
	b43_write16(dev, B43_MMIO_BTCOEX_TXCTL, 0xFF);
}