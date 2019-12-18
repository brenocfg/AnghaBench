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
typedef  int u16 ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_TXF_40CO_B1S2 ; 
 int /*<<< orphan*/  B43_NPHY_TXF_40CO_B32S2 ; 
 scalar_t__ b43_nphy_ipa (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_nphy_tx_lp_fbw(struct b43_wldev *dev)
{
	u16 tmp;

	if (dev->phy.rev >= 3) {
		if (b43_nphy_ipa(dev)) {
			tmp = 4;
			b43_phy_write(dev, B43_NPHY_TXF_40CO_B32S2,
			      (((((tmp << 3) | tmp) << 3) | tmp) << 3) | tmp);
		}

		tmp = 1;
		b43_phy_write(dev, B43_NPHY_TXF_40CO_B1S2,
			      (((((tmp << 3) | tmp) << 3) | tmp) << 3) | tmp);
	}
}