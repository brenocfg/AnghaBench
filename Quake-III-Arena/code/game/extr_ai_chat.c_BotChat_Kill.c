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
struct TYPE_9__ {scalar_t__ lastchat_time; scalar_t__ lastkilledplayer; scalar_t__ client; scalar_t__ enemydeathtype; scalar_t__ botdeathtype; int /*<<< orphan*/  character; int /*<<< orphan*/  cs; int /*<<< orphan*/  chatto; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_11__ {int /*<<< orphan*/  integer; } ;
struct TYPE_10__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,int /*<<< orphan*/ *) ; 
 int BotNumActivePlayers () ; 
 scalar_t__ BotSameTeam (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  BotValidChatPosition (TYPE_1__*) ; 
 scalar_t__ BotVisibleEnemies (TYPE_1__*) ; 
 int /*<<< orphan*/  CHARACTERISTIC_CHAT_INSULT ; 
 int /*<<< orphan*/  CHARACTERISTIC_CHAT_KILL ; 
 int /*<<< orphan*/  CHAT_ALL ; 
 int /*<<< orphan*/  CHAT_TEAM ; 
 int /*<<< orphan*/  EasyClientName (scalar_t__,char*,int) ; 
 scalar_t__ FloatTime () ; 
 scalar_t__ GT_TOURNAMENT ; 
 scalar_t__ MOD_GAUNTLET ; 
 scalar_t__ MOD_KAMIKAZE ; 
 scalar_t__ MOD_RAILGUN ; 
 scalar_t__ MOD_TELEFRAG ; 
 scalar_t__ TIME_BETWEENCHATTING ; 
 scalar_t__ TeamPlayIsOn () ; 
 TYPE_3__ bot_fastchat ; 
 TYPE_2__ bot_nochat ; 
 scalar_t__ gametype ; 
 int qfalse ; 
 int qtrue ; 
 float random () ; 
 scalar_t__ trap_BotNumInitialChats (int /*<<< orphan*/ ,char*) ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_EA_Command (scalar_t__,char*) ; 

int BotChat_Kill(bot_state_t *bs) {
	char name[32];
	float rnd;

	if (bot_nochat.integer) return qfalse;
	if (bs->lastchat_time > FloatTime() - TIME_BETWEENCHATTING) return qfalse;
	rnd = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_KILL, 0, 1);
	// don't chat in tournament mode
	if (gametype == GT_TOURNAMENT) return qfalse;
	//if fast chat is off
	if (!bot_fastchat.integer) {
		if (random() > rnd) return qfalse;
	}
	if (bs->lastkilledplayer == bs->client) return qfalse;
	if (BotNumActivePlayers() <= 1) return qfalse;
	if (!BotValidChatPosition(bs)) return qfalse;
	//
	if (BotVisibleEnemies(bs)) return qfalse;
	//
	EasyClientName(bs->lastkilledplayer, name, 32);
	//
	bs->chatto = CHAT_ALL;
	if (TeamPlayIsOn() && BotSameTeam(bs, bs->lastkilledplayer)) {
		BotAI_BotInitialChat(bs, "kill_teammate", name, NULL);
		bs->chatto = CHAT_TEAM;
	}
	else
	{
		//don't chat in teamplay
		if (TeamPlayIsOn()) {
			trap_EA_Command(bs->client, "vtaunt");
			return qfalse;			// don't wait
		}
		//
		if (bs->enemydeathtype == MOD_GAUNTLET) {
			BotAI_BotInitialChat(bs, "kill_gauntlet", name, NULL);
		}
		else if (bs->enemydeathtype == MOD_RAILGUN) {
			BotAI_BotInitialChat(bs, "kill_rail", name, NULL);
		}
		else if (bs->enemydeathtype == MOD_TELEFRAG) {
			BotAI_BotInitialChat(bs, "kill_telefrag", name, NULL);
		}
#ifdef MISSIONPACK
		else if (bs->botdeathtype == MOD_KAMIKAZE && trap_BotNumInitialChats(bs->cs, "kill_kamikaze"))
			BotAI_BotInitialChat(bs, "kill_kamikaze", name, NULL);
#endif
		//choose between insult and praise
		else if (random() < trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_INSULT, 0, 1)) {
			BotAI_BotInitialChat(bs, "kill_insult", name, NULL);
		}
		else {
			BotAI_BotInitialChat(bs, "kill_praise", name, NULL);
		}
	}
	bs->lastchat_time = FloatTime();
	return qtrue;
}