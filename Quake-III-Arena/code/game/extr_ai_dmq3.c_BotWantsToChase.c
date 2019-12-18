#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ enemy; scalar_t__ ltgtype; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  aas_entityinfo_t ;
struct TYPE_11__ {scalar_t__ entitynum; } ;
struct TYPE_10__ {scalar_t__ entitynum; } ;

/* Variables and functions */
 scalar_t__ Bot1FCTFCarryingFlag (TYPE_1__*) ; 
 int BotAggression (TYPE_1__*) ; 
 scalar_t__ BotCTFCarryingFlag (TYPE_1__*) ; 
 int /*<<< orphan*/  BotEntityInfo (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ BotHarvesterCarryingCubes (TYPE_1__*) ; 
 scalar_t__ EntityCarriesFlag (int /*<<< orphan*/ *) ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_HARVESTER ; 
 scalar_t__ GT_OBELISK ; 
 scalar_t__ LTG_ATTACKENEMYBASE ; 
 scalar_t__ LTG_GETFLAG ; 
 TYPE_3__ blueobelisk ; 
 scalar_t__ gametype ; 
 int qfalse ; 
 int qtrue ; 
 TYPE_2__ redobelisk ; 

int BotWantsToChase(bot_state_t *bs) {
	aas_entityinfo_t entinfo;

	if (gametype == GT_CTF) {
		//never chase when carrying a CTF flag
		if (BotCTFCarryingFlag(bs))
			return qfalse;
		//always chase if the enemy is carrying a flag
		BotEntityInfo(bs->enemy, &entinfo);
		if (EntityCarriesFlag(&entinfo))
			return qtrue;
	}
#ifdef MISSIONPACK
	else if (gametype == GT_1FCTF) {
		//never chase if carrying the flag
		if (Bot1FCTFCarryingFlag(bs))
			return qfalse;
		//always chase if the enemy is carrying a flag
		BotEntityInfo(bs->enemy, &entinfo);
		if (EntityCarriesFlag(&entinfo))
			return qtrue;
	}
	else if (gametype == GT_OBELISK) {
		//the bots should be dedicated to attacking the enemy obelisk
		if (bs->ltgtype == LTG_ATTACKENEMYBASE) {
			if (bs->enemy != redobelisk.entitynum ||
						bs->enemy != blueobelisk.entitynum) {
				return qfalse;
			}
		}
	}
	else if (gametype == GT_HARVESTER) {
		//never chase if carrying cubes
		if (BotHarvesterCarryingCubes(bs))
			return qfalse;
	}
#endif
	//if the bot is getting the flag
	if (bs->ltgtype == LTG_GETFLAG)
		return qfalse;
	//
	if (BotAggression(bs) > 50)
		return qtrue;
	return qfalse;
}