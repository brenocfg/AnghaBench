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
 scalar_t__ b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_voluntary_preempt () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u16 b43legacy_phy_lo_b_r15_loop(struct b43legacy_wldev *dev)
{
	int i;
	u16 ret = 0;
	unsigned long flags;

	local_irq_save(flags);
	for (i = 0; i < 10; i++) {
		b43legacy_phy_write(dev, 0x0015, 0xAFA0);
		udelay(1);
		b43legacy_phy_write(dev, 0x0015, 0xEFA0);
		udelay(10);
		b43legacy_phy_write(dev, 0x0015, 0xFFA0);
		udelay(40);
		ret += b43legacy_phy_read(dev, 0x002C);
	}
	local_irq_restore(flags);
	b43legacy_voluntary_preempt();

	return ret;
}