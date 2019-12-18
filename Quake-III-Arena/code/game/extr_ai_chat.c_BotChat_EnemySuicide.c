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
struct TYPE_8__ {scalar_t__ lastchat_time; scalar_t__ enemy; int /*<<< orphan*/  chatto; int /*<<< orphan*/  character; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;
struct TYPE_9__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,int /*<<< orphan*/ *) ; 
 int BotNumActivePlayers () ; 
 int /*<<< orphan*/  BotValidChatPosition (TYPE_1__*) ; 
 scalar_t__ BotVisibleEnemies (TYPE_1__*) ; 
 int /*<<< orphan*/  CHARACTERISTIC_CHAT_KILL ; 
 int /*<<< orphan*/  CHAT_ALL ; 
 int /*<<< orphan*/  EasyClientName (scalar_t__,char*,int) ; 
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
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int BotChat_EnemySuicide(bot_state_t *bs) {
	char name[32];
	float rnd;

	if (bot_nochat.integer) return qfalse;
	if (bs->lastchat_time > FloatTime() - TIME_BETWEENCHATTING) return qfalse;
	if (BotNumActivePlayers() <= 1) return qfalse;
	//
	rnd = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_CHAT_KILL, 0, 1);
	//don't chat in teamplay
	if (TeamPlayIsOn()) return qfalse;
	// don't chat in tournament mode
	if (gametype == GT_TOURNAMENT) return qfalse;
	//if fast chat is off
	if (!bot_fastchat.integer) {
		if (random() > rnd) return qfalse;
	}
	if (!BotValidChatPosition(bs)) return qfalse;
	//
	if (BotVisibleEnemies(bs)) return qfalse;
	//
	if (bs->enemy >= 0) EasyClientName(bs->enemy, name, 32);
	else strcpy(name, "");
	BotAI_BotInitialChat(bs, "enemy_suicide", name, NULL);
	bs->lastchat_time = FloatTime();
	bs->chatto = CHAT_ALL;
	return qtrue;
}