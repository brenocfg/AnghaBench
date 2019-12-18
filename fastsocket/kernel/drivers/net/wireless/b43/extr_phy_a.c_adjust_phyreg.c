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
typedef  int u16 ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int B43_PHYROUTE ; 
 int B43_PHYROUTE_BASE ; 
 int B43_PHYROUTE_EXT_GPHY ; 
 int B43_PHYROUTE_N_BMODE ; 
 int B43_PHYROUTE_OFDM_GPHY ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dump_stack () ; 

__attribute__((used)) static inline u16 adjust_phyreg(struct b43_wldev *dev, u16 offset)
{
	/* OFDM registers are base-registers for the A-PHY. */
	if ((offset & B43_PHYROUTE) == B43_PHYROUTE_OFDM_GPHY) {
		offset &= ~B43_PHYROUTE;
		offset |= B43_PHYROUTE_BASE;
	}

#if B43_DEBUG
	if ((offset & B43_PHYROUTE) == B43_PHYROUTE_EXT_GPHY) {
		/* Ext-G registers are only available on G-PHYs */
		b43err(dev->wl, "Invalid EXT-G PHY access at "
		       "0x%04X on A-PHY\n", offset);
		dump_stack();
	}
	if ((offset & B43_PHYROUTE) == B43_PHYROUTE_N_BMODE) {
		/* N-BMODE registers are only available on N-PHYs */
		b43err(dev->wl, "Invalid N-BMODE PHY access at "
		       "0x%04X on A-PHY\n", offset);
		dump_stack();
	}
#endif /* B43_DEBUG */

	return offset;
}