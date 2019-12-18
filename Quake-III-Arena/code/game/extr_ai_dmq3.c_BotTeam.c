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
typedef  int /*<<< orphan*/  info ;
struct TYPE_3__ {scalar_t__ client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 scalar_t__ CS_PLAYERS ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 scalar_t__ MAX_CLIENTS ; 
 scalar_t__ TEAM_BLUE ; 
 int TEAM_FREE ; 
 scalar_t__ TEAM_RED ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int qfalse ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

int BotTeam(bot_state_t *bs) {
	char info[1024];

	if (bs->client < 0 || bs->client >= MAX_CLIENTS) {
		//BotAI_Print(PRT_ERROR, "BotCTFTeam: client out of range\n");
		return qfalse;
	}
	trap_GetConfigstring(CS_PLAYERS+bs->client, info, sizeof(info));
	//
	if (atoi(Info_ValueForKey(info, "t")) == TEAM_RED) return TEAM_RED;
	else if (atoi(Info_ValueForKey(info, "t")) == TEAM_BLUE) return TEAM_BLUE;
	return TEAM_FREE;
}