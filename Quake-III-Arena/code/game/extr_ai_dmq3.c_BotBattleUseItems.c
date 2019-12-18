#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* inventory; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  Bot1FCTFCarryingFlag (TYPE_1__*) ; 
 int /*<<< orphan*/  BotCTFCarryingFlag (TYPE_1__*) ; 
 int /*<<< orphan*/  BotHarvesterCarryingCubes (TYPE_1__*) ; 
 int /*<<< orphan*/  BotUseInvulnerability (TYPE_1__*) ; 
 int /*<<< orphan*/  BotUseKamikaze (TYPE_1__*) ; 
 size_t INVENTORY_HEALTH ; 
 size_t INVENTORY_MEDKIT ; 
 size_t INVENTORY_TELEPORTER ; 
 int /*<<< orphan*/  trap_EA_Use (int /*<<< orphan*/ ) ; 

void BotBattleUseItems(bot_state_t *bs) {
	if (bs->inventory[INVENTORY_HEALTH] < 40) {
		if (bs->inventory[INVENTORY_TELEPORTER] > 0) {
			if (!BotCTFCarryingFlag(bs)
#ifdef MISSIONPACK
				&& !Bot1FCTFCarryingFlag(bs)
				&& !BotHarvesterCarryingCubes(bs)
#endif
				) {
				trap_EA_Use(bs->client);
			}
		}
	}
	if (bs->inventory[INVENTORY_HEALTH] < 60) {
		if (bs->inventory[INVENTORY_MEDKIT] > 0) {
			trap_EA_Use(bs->client);
		}
	}
#ifdef MISSIONPACK
	BotUseKamikaze(bs);
	BotUseInvulnerability(bs);
#endif
}