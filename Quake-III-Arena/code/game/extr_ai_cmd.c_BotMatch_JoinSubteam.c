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
typedef  int /*<<< orphan*/  teammate ;
typedef  int /*<<< orphan*/  netname ;
struct TYPE_5__ {char* subteam; int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotAddressedToBot (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHAT_TELL ; 
 int ClientFromName (char*) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  NETNAME ; 
 int /*<<< orphan*/  TEAMNAME ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMatchVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

void BotMatch_JoinSubteam(bot_state_t *bs, bot_match_t *match) {
	char teammate[MAX_MESSAGE_SIZE];
	char netname[MAX_MESSAGE_SIZE];
	int client;

	if (!TeamPlayIsOn()) return;
	//if not addressed to this bot
	if (!BotAddressedToBot(bs, match)) return;
	//get the sub team name
	trap_BotMatchVariable(match, TEAMNAME, teammate, sizeof(teammate));
	//set the sub team name
	strncpy(bs->subteam, teammate, 32);
	bs->subteam[31] = '\0';
	//
	trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
	BotAI_BotInitialChat(bs, "joinedteam", teammate, NULL);
	client = ClientFromName(netname);
	trap_BotEnterChat(bs->cs, client, CHAT_TELL);
}