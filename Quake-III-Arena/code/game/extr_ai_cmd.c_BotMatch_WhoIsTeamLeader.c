#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
struct TYPE_3__ {int /*<<< orphan*/  client; int /*<<< orphan*/  teamleader; } ;
typedef  TYPE_1__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 int /*<<< orphan*/  trap_EA_SayTeam (int /*<<< orphan*/ ,char*) ; 

void BotMatch_WhoIsTeamLeader(bot_state_t *bs, bot_match_t *match) {
	char netname[MAX_MESSAGE_SIZE];

	if (!TeamPlayIsOn()) return;

	ClientName(bs->client, netname, sizeof(netname));
	//if this bot IS the team leader
	if (!Q_stricmp(netname, bs->teamleader)) {
		trap_EA_SayTeam(bs->client, "I'm the team leader\n");
	}
}