#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_n {scalar_t__ txcal_bbmult; } ;
struct TYPE_6__ {scalar_t__ percent; scalar_t__ g_env; } ;
struct TYPE_5__ {scalar_t__ percent; scalar_t__ g_env; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* ladder_iq ; 
 TYPE_2__* ladder_lo ; 

__attribute__((used)) static void b43_nphy_update_tx_cal_ladder(struct b43_wldev *dev, u16 core)
{
	struct b43_phy_n *nphy = dev->phy.n;
	int i;
	u16 scale, entry;

	u16 tmp = nphy->txcal_bbmult;
	if (core == 0)
		tmp >>= 8;
	tmp &= 0xff;

	for (i = 0; i < 18; i++) {
		scale = (ladder_lo[i].percent * tmp) / 100;
		entry = ((scale & 0xFF) << 8) | ladder_lo[i].g_env;
		b43_ntab_write(dev, B43_NTAB16(15, i), entry);

		scale = (ladder_iq[i].percent * tmp) / 100;
		entry = ((scale & 0xFF) << 8) | ladder_iq[i].g_env;
		b43_ntab_write(dev, B43_NTAB16(15, i + 32), entry);
	}
}