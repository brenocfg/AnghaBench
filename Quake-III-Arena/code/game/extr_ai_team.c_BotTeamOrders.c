#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotCreateGroup (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ BotSameTeam (int /*<<< orphan*/ *,int) ; 
 scalar_t__ CS_PLAYERS ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_CLIENTS ; 
 int MAX_INFO_STRING ; 
 scalar_t__ TEAM_SPECTATOR ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int trap_Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

void BotTeamOrders(bot_state_t *bs) {
	int teammates[MAX_CLIENTS];
	int numteammates, i;
	char buf[MAX_INFO_STRING];
	static int maxclients;

	if (!maxclients)
		maxclients = trap_Cvar_VariableIntegerValue("sv_maxclients");

	numteammates = 0;
	for (i = 0; i < maxclients && i < MAX_CLIENTS; i++) {
		trap_GetConfigstring(CS_PLAYERS+i, buf, sizeof(buf));
		//if no config string or no name
		if (!strlen(buf) || !strlen(Info_ValueForKey(buf, "n"))) continue;
		//skip spectators
		if (atoi(Info_ValueForKey(buf, "t")) == TEAM_SPECTATOR) continue;
		//
		if (BotSameTeam(bs, i)) {
			teammates[numteammates] = i;
			numteammates++;
		}
	}
	//
	switch(numteammates) {
		case 1: break;
		case 2:
		{
			//nothing special
			break;
		}
		case 3:
		{
			//have one follow another and one free roaming
			BotCreateGroup(bs, teammates, 2);
			break;
		}
		case 4:
		{
			BotCreateGroup(bs, teammates, 2);		//a group of 2
			BotCreateGroup(bs, &teammates[2], 2);	//a group of 2
			break;
		}
		case 5:
		{
			BotCreateGroup(bs, teammates, 2);		//a group of 2
			BotCreateGroup(bs, &teammates[2], 3);	//a group of 3
			break;
		}
		default:
		{
			if (numteammates <= 10) {
				for (i = 0; i < numteammates / 2; i++) {
					BotCreateGroup(bs, &teammates[i*2], 2);	//groups of 2
				}
			}
			break;
		}
	}
}