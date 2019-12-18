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
struct TYPE_5__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  teamleader; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotVoiceChatOnly (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAT_TEAM ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 int /*<<< orphan*/  VOICECHAT_STARTLEADER ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotVoiceChat_WhoIsLeader(bot_state_t *bs, int client, int mode) {
	char netname[MAX_MESSAGE_SIZE];

	if (!TeamPlayIsOn()) return;

	ClientName(bs->client, netname, sizeof(netname));
	//if this bot IS the team leader
	if (!Q_stricmp(netname, bs->teamleader)) {
		BotAI_BotInitialChat(bs, "iamteamleader", NULL);
		trap_BotEnterChat(bs->cs, 0, CHAT_TEAM);
		BotVoiceChatOnly(bs, -1, VOICECHAT_STARTLEADER);
	}
}