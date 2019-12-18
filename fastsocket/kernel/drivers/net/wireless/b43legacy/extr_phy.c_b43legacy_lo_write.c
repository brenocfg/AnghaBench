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
typedef  int u8 ;
typedef  int u16 ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; } ;
struct b43legacy_lopair {int low; int high; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_PHY_G_LO_CONTROL ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacydbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dump_stack () ; 

__attribute__((used)) static inline
void b43legacy_lo_write(struct b43legacy_wldev *dev,
			struct b43legacy_lopair *pair)
{
	u16 value;

	value = (u8)(pair->low);
	value |= ((u8)(pair->high)) << 8;

#ifdef CONFIG_B43LEGACY_DEBUG
	/* Sanity check. */
	if (pair->low < -8 || pair->low > 8 ||
	    pair->high < -8 || pair->high > 8) {
		b43legacydbg(dev->wl,
		       "WARNING: Writing invalid LOpair "
		       "(low: %d, high: %d)\n",
		       pair->low, pair->high);
		dump_stack();
	}
#endif

	b43legacy_phy_write(dev, B43legacy_PHY_G_LO_CONTROL, value);
}