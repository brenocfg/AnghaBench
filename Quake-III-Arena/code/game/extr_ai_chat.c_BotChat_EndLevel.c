#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ lastchat_time; int /*<<< orphan*/  chatto; int /*<<< orphan*/  client; int /*<<< orphan*/  character; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_12__ {int /*<<< orphan*/  integer; } ;
struct TYPE_11__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* BotFirstClientInRankings () ; 
 scalar_t__ BotIsFirstInRankings (TYPE_1__*) ; 
 scalar_t__ BotIsLastInRankings (TYPE_1__*) ; 
 scalar_t__ BotIsObserver (TYPE_1__*) ; 
 char* BotLastClientInRankings () ; 
 int /*<<< orphan*/  BotMapTitle () ; 
 int BotNumActivePlayers () ; 
 int /*<<< orphan*/  BotRandomOpponentName (TYPE_1__*) ; 
 int /*<<< orphan*/  CHARACTERISTIC_CHAT_STARTENDLEVEL ; 
 int /*<<< orphan*/  CHAT_ALL ; 
 int /*<<< orphan*/  EasyClientName (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ FloatTime () ; 
 scalar_t__ GT_TOURNAMENT ; 
 scalar_t__ TIME_BETWEENCHATTING ; 
 scalar_t__ TeamPlayIsOn () ; 
 TYPE_3__ bot_fastchat ; 
 TYPE_2__ bot_nochat ; 
 scalar_t__ gametype ; 
 int qfalse ; 
 int qtrue ; 
 float random () ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_EA_Command (int /*<<< orphan*/ ,char*) ; 

int BotChat_EndLevel(bot_state_t *bs) {
	char name[32];
	float rnd;

	if (bot_nochat.integer) return qfalse;
	if (BotIsObserver(bs)) return qfalse;
	if (bs->lastchat_time > FloatTime() - TIME_BETWEENCHATTING) return qfalse;
	// teamplay
	if (TeamPlayIsOn()) 
	{
		if (BotIsFirstInRankings(bs)) {
			trap_EA_Command(bs->client, "vtaunt");
		}
		return qtrue;
	}
	// don't chat in tournament mode
	if (gametype == GT_TOURNAMENT) return qfalse;
	rnd = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_STARTENDLEVEL, 0, 1);
	if (!bot_fastchat.integer) {
		if (random() > rnd) return qfalse;
	}
	if (BotNumActivePlayers() <= 1) return qfalse;
	//
	if (BotIsFirstInRankings(bs)) {
		BotAI_BotInitialChat(bs, "level_end_victory",
				EasyClientName(bs->client, name, 32),	// 0
				BotRandomOpponentName(bs),				// 1
				"[invalid var]",						// 2
				BotLastClientInRankings(),				// 3
				BotMapTitle(),							// 4
				NULL);
	}
	else if (BotIsLastInRankings(bs)) {
		BotAI_BotInitialChat(bs, "level_end_lose",
				EasyClientName(bs->client, name, 32),	// 0
				BotRandomOpponentName(bs),				// 1
				BotFirstClientInRankings(),				// 2
				"[invalid var]",						// 3
				BotMapTitle(),							// 4
				NULL);
	}
	else {
		BotAI_BotInitialChat(bs, "level_end",
				EasyClientName(bs->client, name, 32),	// 0
				BotRandomOpponentName(bs),				// 1
				BotFirstClientInRankings(),				// 2
				BotLastClientInRankings(),				// 3
				BotMapTitle(),							// 4
				NULL);
	}
	bs->lastchat_time = FloatTime();
	bs->chatto = CHAT_ALL;
	return qtrue;
}