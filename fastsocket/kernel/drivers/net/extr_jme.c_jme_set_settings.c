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
struct net_device {int dummy; } ;
struct ethtool_cmd {scalar_t__ speed; scalar_t__ autoneg; scalar_t__ duplex; } ;
struct TYPE_2__ {scalar_t__ full_duplex; scalar_t__ force_media; } ;
struct jme_adapter {struct ethtool_cmd old_ecmd; int /*<<< orphan*/  flags; int /*<<< orphan*/  phy_lock; TYPE_1__ mii_if; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  JME_FLAG_SSET ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  jme_reset_link (struct jme_adapter*) ; 
 int mii_ethtool_sset (TYPE_1__*,struct ethtool_cmd*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_set_settings(struct net_device *netdev,
		     struct ethtool_cmd *ecmd)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	int rc, fdc = 0;

	if (ecmd->speed == SPEED_1000 && ecmd->autoneg != AUTONEG_ENABLE)
		return -EINVAL;

	if (jme->mii_if.force_media &&
	ecmd->autoneg != AUTONEG_ENABLE &&
	(jme->mii_if.full_duplex != ecmd->duplex))
		fdc = 1;

	spin_lock_bh(&jme->phy_lock);
	rc = mii_ethtool_sset(&(jme->mii_if), ecmd);
	spin_unlock_bh(&jme->phy_lock);

	if (!rc && fdc)
		jme_reset_link(jme);

	if (!rc) {
		set_bit(JME_FLAG_SSET, &jme->flags);
		jme->old_ecmd = *ecmd;
	}

	return rc;
}