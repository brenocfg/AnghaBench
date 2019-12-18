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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct b43_wldev {TYPE_2__ phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phy_read ) (struct b43_wldev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* phy_write ) (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert_mac_suspended (struct b43_wldev*) ; 
 int /*<<< orphan*/  stub1 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct b43_wldev*,int /*<<< orphan*/ ) ; 

void b43_phy_copy(struct b43_wldev *dev, u16 destreg, u16 srcreg)
{
	assert_mac_suspended(dev);
	dev->phy.ops->phy_write(dev, destreg,
		dev->phy.ops->phy_read(dev, srcreg));
}