#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* inventory; scalar_t__ weaponnum; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 size_t ENEMY_HEIGHT ; 
 size_t ENEMY_HORIZONTAL_DIST ; 
 size_t INVENTORY_ARMOR ; 
 size_t INVENTORY_BFG10K ; 
 size_t INVENTORY_BFGAMMO ; 
 size_t INVENTORY_CELLS ; 
 size_t INVENTORY_GRENADELAUNCHER ; 
 size_t INVENTORY_GRENADES ; 
 size_t INVENTORY_HEALTH ; 
 size_t INVENTORY_LIGHTNING ; 
 size_t INVENTORY_LIGHTNINGAMMO ; 
 size_t INVENTORY_PLASMAGUN ; 
 size_t INVENTORY_QUAD ; 
 size_t INVENTORY_RAILGUN ; 
 size_t INVENTORY_ROCKETLAUNCHER ; 
 size_t INVENTORY_ROCKETS ; 
 size_t INVENTORY_SHELLS ; 
 size_t INVENTORY_SHOTGUN ; 
 size_t INVENTORY_SLUGS ; 
 scalar_t__ WP_GAUNTLET ; 

float BotAggression(bot_state_t *bs) {
	//if the bot has quad
	if (bs->inventory[INVENTORY_QUAD]) {
		//if the bot is not holding the gauntlet or the enemy is really nearby
		if (bs->weaponnum != WP_GAUNTLET ||
			bs->inventory[ENEMY_HORIZONTAL_DIST] < 80) {
			return 70;
		}
	}
	//if the enemy is located way higher than the bot
	if (bs->inventory[ENEMY_HEIGHT] > 200) return 0;
	//if the bot is very low on health
	if (bs->inventory[INVENTORY_HEALTH] < 60) return 0;
	//if the bot is low on health
	if (bs->inventory[INVENTORY_HEALTH] < 80) {
		//if the bot has insufficient armor
		if (bs->inventory[INVENTORY_ARMOR] < 40) return 0;
	}
	//if the bot can use the bfg
	if (bs->inventory[INVENTORY_BFG10K] > 0 &&
			bs->inventory[INVENTORY_BFGAMMO] > 7) return 100;
	//if the bot can use the railgun
	if (bs->inventory[INVENTORY_RAILGUN] > 0 &&
			bs->inventory[INVENTORY_SLUGS] > 5) return 95;
	//if the bot can use the lightning gun
	if (bs->inventory[INVENTORY_LIGHTNING] > 0 &&
			bs->inventory[INVENTORY_LIGHTNINGAMMO] > 50) return 90;
	//if the bot can use the rocketlauncher
	if (bs->inventory[INVENTORY_ROCKETLAUNCHER] > 0 &&
			bs->inventory[INVENTORY_ROCKETS] > 5) return 90;
	//if the bot can use the plasmagun
	if (bs->inventory[INVENTORY_PLASMAGUN] > 0 &&
			bs->inventory[INVENTORY_CELLS] > 40) return 85;
	//if the bot can use the grenade launcher
	if (bs->inventory[INVENTORY_GRENADELAUNCHER] > 0 &&
			bs->inventory[INVENTORY_GRENADES] > 10) return 80;
	//if the bot can use the shotgun
	if (bs->inventory[INVENTORY_SHOTGUN] > 0 &&
			bs->inventory[INVENTORY_SHELLS] > 10) return 50;
	//otherwise the bot is not feeling too good
	return 0;
}