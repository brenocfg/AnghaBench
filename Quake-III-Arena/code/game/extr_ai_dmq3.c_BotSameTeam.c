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
typedef  int /*<<< orphan*/  info2 ;
typedef  int /*<<< orphan*/  info1 ;
struct TYPE_3__ {scalar_t__ client; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int CS_PLAYERS ; 
 scalar_t__ GT_TEAM ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_CLIENTS ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ gametype ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_GetConfigstring (int,char*,int) ; 

int BotSameTeam(bot_state_t *bs, int entnum) {
	char info1[1024], info2[1024];

	if (bs->client < 0 || bs->client >= MAX_CLIENTS) {
		//BotAI_Print(PRT_ERROR, "BotSameTeam: client out of range\n");
		return qfalse;
	}
	if (entnum < 0 || entnum >= MAX_CLIENTS) {
		//BotAI_Print(PRT_ERROR, "BotSameTeam: client out of range\n");
		return qfalse;
	}
	if ( gametype >= GT_TEAM ) {
		trap_GetConfigstring(CS_PLAYERS+bs->client, info1, sizeof(info1));
		trap_GetConfigstring(CS_PLAYERS+entnum, info2, sizeof(info2));
		//
		if (atoi(Info_ValueForKey(info1, "t")) == atoi(Info_ValueForKey(info2, "t"))) return qtrue;
	}
	return qfalse;
}