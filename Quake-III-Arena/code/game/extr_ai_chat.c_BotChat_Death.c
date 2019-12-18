#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ lastchat_time; scalar_t__ lastkilledby; scalar_t__ client; scalar_t__ botdeathtype; int /*<<< orphan*/  chatto; int /*<<< orphan*/  character; int /*<<< orphan*/  cs; scalar_t__ botsuicide; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;
struct TYPE_9__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,...) ; 
 int BotNumActivePlayers () ; 
 int /*<<< orphan*/  BotRandomOpponentName (TYPE_1__*) ; 
 scalar_t__ BotSameTeam (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  BotWeaponNameForMeansOfDeath (scalar_t__) ; 
 int /*<<< orphan*/  CHARACTERISTIC_CHAT_DEATH ; 
 int /*<<< orphan*/  CHARACTERISTIC_CHAT_INSULT ; 
 int /*<<< orphan*/  CHAT_ALL ; 
 int /*<<< orphan*/  CHAT_TEAM ; 
 int /*<<< orphan*/  EasyClientName (scalar_t__,char*,int) ; 
 scalar_t__ FloatTime () ; 
 scalar_t__ GT_TOURNAMENT ; 
 scalar_t__ MAX_CLIENTS ; 
 scalar_t__ MOD_BFG ; 
 scalar_t__ MOD_BFG_SPLASH ; 
 scalar_t__ MOD_CRUSH ; 
 scalar_t__ MOD_FALLING ; 
 scalar_t__ MOD_GAUNTLET ; 
 scalar_t__ MOD_KAMIKAZE ; 
 scalar_t__ MOD_LAVA ; 
 scalar_t__ MOD_RAILGUN ; 
 scalar_t__ MOD_SLIME ; 
 scalar_t__ MOD_SUICIDE ; 
 scalar_t__ MOD_TARGET_LASER ; 
 scalar_t__ MOD_TELEFRAG ; 
 scalar_t__ MOD_TRIGGER_HURT ; 
 scalar_t__ MOD_UNKNOWN ; 
 scalar_t__ MOD_WATER ; 
 scalar_t__ TIME_BETWEENCHATTING ; 
 scalar_t__ TeamPlayIsOn () ; 
 TYPE_3__ bot_fastchat ; 
 TYPE_2__ bot_nochat ; 
 scalar_t__ gametype ; 
 int qfalse ; 
 int qtrue ; 
 double random () ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ trap_BotNumInitialChats (int /*<<< orphan*/ ,char*) ; 
 double trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_EA_Command (scalar_t__,char*) ; 

int BotChat_Death(bot_state_t *bs) {
	char name[32];
	float rnd;

	if (bot_nochat.integer) return qfalse;
	if (bs->lastchat_time > FloatTime() - TIME_BETWEENCHATTING) return qfalse;
	rnd = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_DEATH, 0, 1);
	// don't chat in tournament mode
	if (gametype == GT_TOURNAMENT) return qfalse;
	//if fast chatting is off
	if (!bot_fastchat.integer) {
		if (random() > rnd) return qfalse;
	}
	if (BotNumActivePlayers() <= 1) return qfalse;
	//
	if (bs->lastkilledby >= 0 && bs->lastkilledby < MAX_CLIENTS)
		EasyClientName(bs->lastkilledby, name, 32);
	else
		strcpy(name, "[world]");
	//
	if (TeamPlayIsOn() && BotSameTeam(bs, bs->lastkilledby)) {
		if (bs->lastkilledby == bs->client) return qfalse;
		BotAI_BotInitialChat(bs, "death_teammate", name, NULL);
		bs->chatto = CHAT_TEAM;
	}
	else
	{
		//teamplay
		if (TeamPlayIsOn()) {
			trap_EA_Command(bs->client, "vtaunt");
			return qtrue;
		}
		//
		if (bs->botdeathtype == MOD_WATER)
			BotAI_BotInitialChat(bs, "death_drown", BotRandomOpponentName(bs), NULL);
		else if (bs->botdeathtype == MOD_SLIME)
			BotAI_BotInitialChat(bs, "death_slime", BotRandomOpponentName(bs), NULL);
		else if (bs->botdeathtype == MOD_LAVA)
			BotAI_BotInitialChat(bs, "death_lava", BotRandomOpponentName(bs), NULL);
		else if (bs->botdeathtype == MOD_FALLING)
			BotAI_BotInitialChat(bs, "death_cratered", BotRandomOpponentName(bs), NULL);
		else if (bs->botsuicide || //all other suicides by own weapon
				bs->botdeathtype == MOD_CRUSH ||
				bs->botdeathtype == MOD_SUICIDE ||
				bs->botdeathtype == MOD_TARGET_LASER ||
				bs->botdeathtype == MOD_TRIGGER_HURT ||
				bs->botdeathtype == MOD_UNKNOWN)
			BotAI_BotInitialChat(bs, "death_suicide", BotRandomOpponentName(bs), NULL);
		else if (bs->botdeathtype == MOD_TELEFRAG)
			BotAI_BotInitialChat(bs, "death_telefrag", name, NULL);
#ifdef MISSIONPACK
		else if (bs->botdeathtype == MOD_KAMIKAZE && trap_BotNumInitialChats(bs->cs, "death_kamikaze"))
			BotAI_BotInitialChat(bs, "death_kamikaze", name, NULL);
#endif
		else {
			if ((bs->botdeathtype == MOD_GAUNTLET ||
				bs->botdeathtype == MOD_RAILGUN ||
				bs->botdeathtype == MOD_BFG ||
				bs->botdeathtype == MOD_BFG_SPLASH) && random() < 0.5) {

				if (bs->botdeathtype == MOD_GAUNTLET)
					BotAI_BotInitialChat(bs, "death_gauntlet",
							name,												// 0
							BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
							NULL);
				else if (bs->botdeathtype == MOD_RAILGUN)
					BotAI_BotInitialChat(bs, "death_rail",
							name,												// 0
							BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
							NULL);
				else
					BotAI_BotInitialChat(bs, "death_bfg",
							name,												// 0
							BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
							NULL);
			}
			//choose between insult and praise
			else if (random() < trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_INSULT, 0, 1)) {
				BotAI_BotInitialChat(bs, "death_insult",
							name,												// 0
							BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
							NULL);
			}
			else {
				BotAI_BotInitialChat(bs, "death_praise",
							name,												// 0
							BotWeaponNameForMeansOfDeath(bs->botdeathtype),		// 1
							NULL);
			}
		}
		bs->chatto = CHAT_ALL;
	}
	bs->lastchat_time = FloatTime();
	return qtrue;
}