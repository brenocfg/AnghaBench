#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oldinventory ;
struct TYPE_6__ {int* stats; int* ammo; scalar_t__* powerups; int generic1; } ;
struct TYPE_7__ {int* inventory; TYPE_1__ cur_ps; } ;
typedef  TYPE_2__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotCheckItemPickup (TYPE_2__*,int*) ; 
 scalar_t__ BotTeam (TYPE_2__*) ; 
 size_t INVENTORY_AMMOREGEN ; 
 size_t INVENTORY_ARMOR ; 
 size_t INVENTORY_BELT ; 
 size_t INVENTORY_BFG10K ; 
 size_t INVENTORY_BFGAMMO ; 
 size_t INVENTORY_BLUECUBE ; 
 size_t INVENTORY_BLUEFLAG ; 
 size_t INVENTORY_BULLETS ; 
 size_t INVENTORY_CELLS ; 
 size_t INVENTORY_CHAINGUN ; 
 size_t INVENTORY_DOUBLER ; 
 size_t INVENTORY_ENVIRONMENTSUIT ; 
 size_t INVENTORY_FLIGHT ; 
 size_t INVENTORY_GAUNTLET ; 
 size_t INVENTORY_GRAPPLINGHOOK ; 
 size_t INVENTORY_GRENADELAUNCHER ; 
 size_t INVENTORY_GRENADES ; 
 size_t INVENTORY_GUARD ; 
 size_t INVENTORY_HASTE ; 
 size_t INVENTORY_HEALTH ; 
 size_t INVENTORY_INVISIBILITY ; 
 size_t INVENTORY_INVULNERABILITY ; 
 size_t INVENTORY_KAMIKAZE ; 
 size_t INVENTORY_LIGHTNING ; 
 size_t INVENTORY_LIGHTNINGAMMO ; 
 size_t INVENTORY_MACHINEGUN ; 
 size_t INVENTORY_MEDKIT ; 
 size_t INVENTORY_MINES ; 
 size_t INVENTORY_NAILGUN ; 
 size_t INVENTORY_NAILS ; 
 size_t INVENTORY_NEUTRALFLAG ; 
 size_t INVENTORY_PLASMAGUN ; 
 size_t INVENTORY_PORTAL ; 
 size_t INVENTORY_PROXLAUNCHER ; 
 size_t INVENTORY_QUAD ; 
 size_t INVENTORY_RAILGUN ; 
 size_t INVENTORY_REDCUBE ; 
 size_t INVENTORY_REDFLAG ; 
 size_t INVENTORY_REGEN ; 
 size_t INVENTORY_ROCKETLAUNCHER ; 
 size_t INVENTORY_ROCKETS ; 
 size_t INVENTORY_SCOUT ; 
 size_t INVENTORY_SHELLS ; 
 size_t INVENTORY_SHOTGUN ; 
 size_t INVENTORY_SLUGS ; 
 size_t INVENTORY_TELEPORTER ; 
 int MAX_ITEMS ; 
 int MODELINDEX_AMMOREGEN ; 
 int MODELINDEX_DOUBLER ; 
 int MODELINDEX_GUARD ; 
 int MODELINDEX_INVULNERABILITY ; 
 int MODELINDEX_KAMIKAZE ; 
 int MODELINDEX_MEDKIT ; 
 int MODELINDEX_PORTAL ; 
 int MODELINDEX_SCOUT ; 
 int MODELINDEX_TELEPORTER ; 
 size_t PW_BATTLESUIT ; 
 size_t PW_BLUEFLAG ; 
 size_t PW_FLIGHT ; 
 size_t PW_HASTE ; 
 size_t PW_INVIS ; 
 size_t PW_NEUTRALFLAG ; 
 size_t PW_QUAD ; 
 size_t PW_REDFLAG ; 
 size_t PW_REGEN ; 
 size_t STAT_ARMOR ; 
 size_t STAT_HEALTH ; 
 size_t STAT_HOLDABLE_ITEM ; 
 size_t STAT_PERSISTANT_POWERUP ; 
 size_t STAT_WEAPONS ; 
 scalar_t__ TEAM_RED ; 
 int WP_BFG ; 
 int WP_CHAINGUN ; 
 int WP_GAUNTLET ; 
 int WP_GRAPPLING_HOOK ; 
 int WP_GRENADE_LAUNCHER ; 
 int WP_LIGHTNING ; 
 int WP_MACHINEGUN ; 
 int WP_NAILGUN ; 
 int WP_PLASMAGUN ; 
 int WP_PROX_LAUNCHER ; 
 int WP_RAILGUN ; 
 int WP_ROCKET_LAUNCHER ; 
 int WP_SHOTGUN ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void BotUpdateInventory(bot_state_t *bs) {
	int oldinventory[MAX_ITEMS];

	memcpy(oldinventory, bs->inventory, sizeof(oldinventory));
	//armor
	bs->inventory[INVENTORY_ARMOR] = bs->cur_ps.stats[STAT_ARMOR];
	//weapons
	bs->inventory[INVENTORY_GAUNTLET] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_GAUNTLET)) != 0;
	bs->inventory[INVENTORY_SHOTGUN] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_SHOTGUN)) != 0;
	bs->inventory[INVENTORY_MACHINEGUN] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_MACHINEGUN)) != 0;
	bs->inventory[INVENTORY_GRENADELAUNCHER] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_GRENADE_LAUNCHER)) != 0;
	bs->inventory[INVENTORY_ROCKETLAUNCHER] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_ROCKET_LAUNCHER)) != 0;
	bs->inventory[INVENTORY_LIGHTNING] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_LIGHTNING)) != 0;
	bs->inventory[INVENTORY_RAILGUN] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_RAILGUN)) != 0;
	bs->inventory[INVENTORY_PLASMAGUN] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_PLASMAGUN)) != 0;
	bs->inventory[INVENTORY_BFG10K] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_BFG)) != 0;
	bs->inventory[INVENTORY_GRAPPLINGHOOK] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_GRAPPLING_HOOK)) != 0;
#ifdef MISSIONPACK
	bs->inventory[INVENTORY_NAILGUN] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_NAILGUN)) != 0;;
	bs->inventory[INVENTORY_PROXLAUNCHER] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_PROX_LAUNCHER)) != 0;;
	bs->inventory[INVENTORY_CHAINGUN] = (bs->cur_ps.stats[STAT_WEAPONS] & (1 << WP_CHAINGUN)) != 0;;
#endif
	//ammo
	bs->inventory[INVENTORY_SHELLS] = bs->cur_ps.ammo[WP_SHOTGUN];
	bs->inventory[INVENTORY_BULLETS] = bs->cur_ps.ammo[WP_MACHINEGUN];
	bs->inventory[INVENTORY_GRENADES] = bs->cur_ps.ammo[WP_GRENADE_LAUNCHER];
	bs->inventory[INVENTORY_CELLS] = bs->cur_ps.ammo[WP_PLASMAGUN];
	bs->inventory[INVENTORY_LIGHTNINGAMMO] = bs->cur_ps.ammo[WP_LIGHTNING];
	bs->inventory[INVENTORY_ROCKETS] = bs->cur_ps.ammo[WP_ROCKET_LAUNCHER];
	bs->inventory[INVENTORY_SLUGS] = bs->cur_ps.ammo[WP_RAILGUN];
	bs->inventory[INVENTORY_BFGAMMO] = bs->cur_ps.ammo[WP_BFG];
#ifdef MISSIONPACK
	bs->inventory[INVENTORY_NAILS] = bs->cur_ps.ammo[WP_NAILGUN];
	bs->inventory[INVENTORY_MINES] = bs->cur_ps.ammo[WP_PROX_LAUNCHER];
	bs->inventory[INVENTORY_BELT] = bs->cur_ps.ammo[WP_CHAINGUN];
#endif
	//powerups
	bs->inventory[INVENTORY_HEALTH] = bs->cur_ps.stats[STAT_HEALTH];
	bs->inventory[INVENTORY_TELEPORTER] = bs->cur_ps.stats[STAT_HOLDABLE_ITEM] == MODELINDEX_TELEPORTER;
	bs->inventory[INVENTORY_MEDKIT] = bs->cur_ps.stats[STAT_HOLDABLE_ITEM] == MODELINDEX_MEDKIT;
#ifdef MISSIONPACK
	bs->inventory[INVENTORY_KAMIKAZE] = bs->cur_ps.stats[STAT_HOLDABLE_ITEM] == MODELINDEX_KAMIKAZE;
	bs->inventory[INVENTORY_PORTAL] = bs->cur_ps.stats[STAT_HOLDABLE_ITEM] == MODELINDEX_PORTAL;
	bs->inventory[INVENTORY_INVULNERABILITY] = bs->cur_ps.stats[STAT_HOLDABLE_ITEM] == MODELINDEX_INVULNERABILITY;
#endif
	bs->inventory[INVENTORY_QUAD] = bs->cur_ps.powerups[PW_QUAD] != 0;
	bs->inventory[INVENTORY_ENVIRONMENTSUIT] = bs->cur_ps.powerups[PW_BATTLESUIT] != 0;
	bs->inventory[INVENTORY_HASTE] = bs->cur_ps.powerups[PW_HASTE] != 0;
	bs->inventory[INVENTORY_INVISIBILITY] = bs->cur_ps.powerups[PW_INVIS] != 0;
	bs->inventory[INVENTORY_REGEN] = bs->cur_ps.powerups[PW_REGEN] != 0;
	bs->inventory[INVENTORY_FLIGHT] = bs->cur_ps.powerups[PW_FLIGHT] != 0;
#ifdef MISSIONPACK
	bs->inventory[INVENTORY_SCOUT] = bs->cur_ps.stats[STAT_PERSISTANT_POWERUP] == MODELINDEX_SCOUT;
	bs->inventory[INVENTORY_GUARD] = bs->cur_ps.stats[STAT_PERSISTANT_POWERUP] == MODELINDEX_GUARD;
	bs->inventory[INVENTORY_DOUBLER] = bs->cur_ps.stats[STAT_PERSISTANT_POWERUP] == MODELINDEX_DOUBLER;
	bs->inventory[INVENTORY_AMMOREGEN] = bs->cur_ps.stats[STAT_PERSISTANT_POWERUP] == MODELINDEX_AMMOREGEN;
#endif
	bs->inventory[INVENTORY_REDFLAG] = bs->cur_ps.powerups[PW_REDFLAG] != 0;
	bs->inventory[INVENTORY_BLUEFLAG] = bs->cur_ps.powerups[PW_BLUEFLAG] != 0;
#ifdef MISSIONPACK
	bs->inventory[INVENTORY_NEUTRALFLAG] = bs->cur_ps.powerups[PW_NEUTRALFLAG] != 0;
	if (BotTeam(bs) == TEAM_RED) {
		bs->inventory[INVENTORY_REDCUBE] = bs->cur_ps.generic1;
		bs->inventory[INVENTORY_BLUECUBE] = 0;
	}
	else {
		bs->inventory[INVENTORY_REDCUBE] = 0;
		bs->inventory[INVENTORY_BLUECUBE] = bs->cur_ps.generic1;
	}
#endif
	BotCheckItemPickup(bs, oldinventory);
}