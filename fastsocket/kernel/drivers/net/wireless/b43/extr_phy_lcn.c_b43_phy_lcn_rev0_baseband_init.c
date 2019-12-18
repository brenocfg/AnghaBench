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
struct b43_wldev {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* bus_sprom; } ;
struct TYPE_3__ {int boardflags_lo; } ;

/* Variables and functions */
 int B43_BFL_FEM ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_phy_lcn_rev0_baseband_init(struct b43_wldev *dev)
{
	b43_radio_write(dev, 0x11c, 0);

	b43_phy_write(dev, 0x43b, 0);
	b43_phy_write(dev, 0x43c, 0);
	b43_phy_write(dev, 0x44c, 0);
	b43_phy_write(dev, 0x4e6, 0);
	b43_phy_write(dev, 0x4f9, 0);
	b43_phy_write(dev, 0x4b0, 0);
	b43_phy_write(dev, 0x938, 0);
	b43_phy_write(dev, 0x4b0, 0);
	b43_phy_write(dev, 0x44e, 0);

	b43_phy_set(dev, 0x567, 0x03);

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_write(dev, 0x44a, 0x80);

	if (!(dev->dev->bus_sprom->boardflags_lo & B43_BFL_FEM))
		; /* TODO */
	b43_phy_maskset(dev, 0x634, ~0xff, 0xc);
	if (dev->dev->bus_sprom->boardflags_lo & B43_BFL_FEM) {
		b43_phy_maskset(dev, 0x634, ~0xff, 0xa);
		b43_phy_write(dev, 0x910, 0x1);
	}

	b43_phy_write(dev, 0x910, 0x1);

	b43_phy_maskset(dev, 0x448, ~0x300, 0x100);
	b43_phy_maskset(dev, 0x608, ~0xff, 0x17);
	b43_phy_maskset(dev, 0x604, ~0x7ff, 0x3ea);
}