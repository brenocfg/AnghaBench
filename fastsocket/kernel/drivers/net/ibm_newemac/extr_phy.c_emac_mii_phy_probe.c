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
typedef  int u32 ;
typedef  int u16 ;
struct mii_phy_def {int phy_id_mask; int phy_id; int /*<<< orphan*/  features; } ;
struct mii_phy {int address; int /*<<< orphan*/  features; int /*<<< orphan*/  advertising; struct mii_phy_def* def; scalar_t__ asym_pause; scalar_t__ pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int BMSR_100FULL ; 
 int BMSR_100HALF ; 
 int BMSR_10FULL ; 
 int BMSR_10HALF ; 
 int BMSR_ANEGCAPABLE ; 
 int BMSR_ESTATEN ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int ENODEV ; 
 int ESTATUS_1000_TFULL ; 
 int ESTATUS_1000_THALF ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_ESTATUS ; 
 int /*<<< orphan*/  MII_PHYSID1 ; 
 int /*<<< orphan*/  MII_PHYSID2 ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_1000baseT_Half ; 
 int /*<<< orphan*/  SUPPORTED_100baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_100baseT_Half ; 
 int /*<<< orphan*/  SUPPORTED_10baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_10baseT_Half ; 
 int /*<<< orphan*/  SUPPORTED_Autoneg ; 
 int /*<<< orphan*/  SUPPORTED_MII ; 
 scalar_t__ emac_mii_reset_phy (struct mii_phy*) ; 
 struct mii_phy_def** mii_phy_table ; 
 int phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 

int emac_mii_phy_probe(struct mii_phy *phy, int address)
{
	struct mii_phy_def *def;
	int i;
	u32 id;

	phy->autoneg = AUTONEG_DISABLE;
	phy->advertising = 0;
	phy->address = address;
	phy->speed = SPEED_10;
	phy->duplex = DUPLEX_HALF;
	phy->pause = phy->asym_pause = 0;

	/* Take PHY out of isolate mode and reset it. */
	if (emac_mii_reset_phy(phy))
		return -ENODEV;

	/* Read ID and find matching entry */
	id = (phy_read(phy, MII_PHYSID1) << 16) | phy_read(phy, MII_PHYSID2);
	for (i = 0; (def = mii_phy_table[i]) != NULL; i++)
		if ((id & def->phy_id_mask) == def->phy_id)
			break;
	/* Should never be NULL (we have a generic entry), but... */
	if (!def)
		return -ENODEV;

	phy->def = def;

	/* Determine PHY features if needed */
	phy->features = def->features;
	if (!phy->features) {
		u16 bmsr = phy_read(phy, MII_BMSR);
		if (bmsr & BMSR_ANEGCAPABLE)
			phy->features |= SUPPORTED_Autoneg;
		if (bmsr & BMSR_10HALF)
			phy->features |= SUPPORTED_10baseT_Half;
		if (bmsr & BMSR_10FULL)
			phy->features |= SUPPORTED_10baseT_Full;
		if (bmsr & BMSR_100HALF)
			phy->features |= SUPPORTED_100baseT_Half;
		if (bmsr & BMSR_100FULL)
			phy->features |= SUPPORTED_100baseT_Full;
		if (bmsr & BMSR_ESTATEN) {
			u16 esr = phy_read(phy, MII_ESTATUS);
			if (esr & ESTATUS_1000_TFULL)
				phy->features |= SUPPORTED_1000baseT_Full;
			if (esr & ESTATUS_1000_THALF)
				phy->features |= SUPPORTED_1000baseT_Half;
		}
		phy->features |= SUPPORTED_MII;
	}

	/* Setup default advertising */
	phy->advertising = phy->features;

	return 0;
}