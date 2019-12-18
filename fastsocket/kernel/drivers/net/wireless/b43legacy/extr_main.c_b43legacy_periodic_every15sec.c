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
struct TYPE_2__ {int /*<<< orphan*/  txerr_cnt; } ;
struct b43legacy_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_PHY_TX_BADNESS_LIMIT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_phy_xmitpower (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void b43legacy_periodic_every15sec(struct b43legacy_wldev *dev)
{
	b43legacy_phy_xmitpower(dev); /* FIXME: unless scanning? */

	atomic_set(&dev->phy.txerr_cnt, B43legacy_PHY_TX_BADNESS_LIMIT);
	wmb();
}