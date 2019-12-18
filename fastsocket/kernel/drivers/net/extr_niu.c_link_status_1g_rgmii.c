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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct niu_link_config {int active_speed; int /*<<< orphan*/  active_duplex; } ;
struct niu {int /*<<< orphan*/  lock; int /*<<< orphan*/  phy_addr; struct niu_link_config link_config; } ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_INVALID ; 
 int EINVAL ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_ESTATUS ; 
 int /*<<< orphan*/  MII_LPA ; 
 int SPEED_1000 ; 
 int SPEED_INVALID ; 
 int mii_read (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int link_status_1g_rgmii(struct niu *np, int *link_up_p)
{
	struct niu_link_config *lp = &np->link_config;
	u16 current_speed, bmsr;
	unsigned long flags;
	u8 current_duplex;
	int err, link_up;

	link_up = 0;
	current_speed = SPEED_INVALID;
	current_duplex = DUPLEX_INVALID;

	spin_lock_irqsave(&np->lock, flags);

	err = -EINVAL;

	err = mii_read(np, np->phy_addr, MII_BMSR);
	if (err < 0)
		goto out;

	bmsr = err;
	if (bmsr & BMSR_LSTATUS) {
		u16 adv, lpa, common, estat;

		err = mii_read(np, np->phy_addr, MII_ADVERTISE);
		if (err < 0)
			goto out;
		adv = err;

		err = mii_read(np, np->phy_addr, MII_LPA);
		if (err < 0)
			goto out;
		lpa = err;

		common = adv & lpa;

		err = mii_read(np, np->phy_addr, MII_ESTATUS);
		if (err < 0)
			goto out;
		estat = err;
		link_up = 1;
		current_speed = SPEED_1000;
		current_duplex = DUPLEX_FULL;

	}
	lp->active_speed = current_speed;
	lp->active_duplex = current_duplex;
	err = 0;

out:
	spin_unlock_irqrestore(&np->lock, flags);

	*link_up_p = link_up;
	return err;
}