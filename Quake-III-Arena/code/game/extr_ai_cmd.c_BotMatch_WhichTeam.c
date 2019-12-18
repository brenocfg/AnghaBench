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
struct TYPE_5__ {int /*<<< orphan*/  client; int /*<<< orphan*/  cs; int /*<<< orphan*/  subteam; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_1__*,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  BotAddressedToBot (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHAT_TEAM ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotMatch_WhichTeam(bot_state_t *bs, bot_match_t *match) {
	if (!TeamPlayIsOn()) return;
	//if not addressed to this bot
	if (!BotAddressedToBot(bs, match)) return;
	//
	if (strlen(bs->subteam)) {
		BotAI_BotInitialChat(bs, "inteam", bs->subteam, NULL);
	}
	else {
		BotAI_BotInitialChat(bs, "noteam", NULL);
	}
	trap_BotEnterChat(bs->cs, bs->client, CHAT_TEAM);
}