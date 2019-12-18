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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct mii_phy {TYPE_2__* def; int /*<<< orphan*/  mii_id; } ;
struct spider_net_card {int /*<<< orphan*/  netdev; struct mii_phy phy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setup_aneg ) (struct mii_phy*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_100baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Half ; 
 int BMSR_100FULL ; 
 int BMSR_100HALF ; 
 int BMSR_10FULL ; 
 int BMSR_10HALF ; 
 int BMSR_ESTATEN ; 
 int ESTATUS_1000_TFULL ; 
 int ESTATUS_1000_THALF ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_ESTATUS ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Half ; 
 int /*<<< orphan*/  mii_phy_probe (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int spider_net_read_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mii_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spider_net_setup_aneg(struct spider_net_card *card)
{
	struct mii_phy *phy = &card->phy;
	u32 advertise = 0;
	u16 bmsr, estat;

	bmsr  = spider_net_read_phy(card->netdev, phy->mii_id, MII_BMSR);
	estat = spider_net_read_phy(card->netdev, phy->mii_id, MII_ESTATUS);

	if (bmsr & BMSR_10HALF)
		advertise |= ADVERTISED_10baseT_Half;
	if (bmsr & BMSR_10FULL)
		advertise |= ADVERTISED_10baseT_Full;
	if (bmsr & BMSR_100HALF)
		advertise |= ADVERTISED_100baseT_Half;
	if (bmsr & BMSR_100FULL)
		advertise |= ADVERTISED_100baseT_Full;

	if ((bmsr & BMSR_ESTATEN) && (estat & ESTATUS_1000_TFULL))
		advertise |= SUPPORTED_1000baseT_Full;
	if ((bmsr & BMSR_ESTATEN) && (estat & ESTATUS_1000_THALF))
		advertise |= SUPPORTED_1000baseT_Half;

	mii_phy_probe(phy, phy->mii_id);
	phy->def->ops->setup_aneg(phy, advertise);

}