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
typedef  int /*<<< orphan*/  bot_goal_t ;

/* Variables and functions */
 int BotClientTravelTimeToGoal (int,int /*<<< orphan*/ *) ; 
 scalar_t__ BotSameTeam (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BotTeam (int /*<<< orphan*/ *) ; 
 scalar_t__ CS_PLAYERS ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_CLIENTS ; 
 int MAX_INFO_STRING ; 
 scalar_t__ TEAM_RED ; 
 scalar_t__ TEAM_SPECTATOR ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  blueobelisk ; 
 int /*<<< orphan*/  ctf_blueflag ; 
 int /*<<< orphan*/  ctf_redflag ; 
 scalar_t__ gametype ; 
 int /*<<< orphan*/  redobelisk ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int trap_Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  trap_GetConfigstring (scalar_t__,char*,int) ; 

int BotSortTeamMatesByBaseTravelTime(bot_state_t *bs, int *teammates, int maxteammates) {

	int i, j, k, numteammates, traveltime;
	char buf[MAX_INFO_STRING];
	static int maxclients;
	int traveltimes[MAX_CLIENTS];
	bot_goal_t *goal = NULL;

	if (gametype == GT_CTF || gametype == GT_1FCTF) {
		if (BotTeam(bs) == TEAM_RED)
			goal = &ctf_redflag;
		else
			goal = &ctf_blueflag;
	}
#ifdef MISSIONPACK
	else {
		if (BotTeam(bs) == TEAM_RED)
			goal = &redobelisk;
		else
			goal = &blueobelisk;
	}
#endif
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
			//
			traveltime = BotClientTravelTimeToGoal(i, goal);
			//
			for (j = 0; j < numteammates; j++) {
				if (traveltime < traveltimes[j]) {
					for (k = numteammates; k > j; k--) {
						traveltimes[k] = traveltimes[k-1];
						teammates[k] = teammates[k-1];
					}
					break;
				}
			}
			traveltimes[j] = traveltime;
			teammates[j] = i;
			numteammates++;
			if (numteammates >= maxteammates) break;
		}
	}
	return numteammates;
}