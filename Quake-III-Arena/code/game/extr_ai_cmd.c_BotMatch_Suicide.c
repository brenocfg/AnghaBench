#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
struct TYPE_5__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_AFFIRMATIVE ; 
 int /*<<< orphan*/  BotAddressedToBot (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotVoiceChat (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int ClientFromName (char*) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  NETNAME ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 int /*<<< orphan*/  VOICECHAT_TAUNT ; 
 int /*<<< orphan*/  trap_BotMatchVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_EA_Action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_EA_Command (int /*<<< orphan*/ ,char*) ; 

void BotMatch_Suicide(bot_state_t *bs, bot_match_t *match) {
	char netname[MAX_MESSAGE_SIZE];
	int client;

	if (!TeamPlayIsOn()) return;
	//if not addressed to this bot
	if (!BotAddressedToBot(bs, match)) return;
	//
	trap_EA_Command(bs->client, "kill");
	//
	trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
	client = ClientFromName(netname);
	//
	BotVoiceChat(bs, client, VOICECHAT_TAUNT);
	trap_EA_Action(bs->client, ACTION_AFFIRMATIVE);
}