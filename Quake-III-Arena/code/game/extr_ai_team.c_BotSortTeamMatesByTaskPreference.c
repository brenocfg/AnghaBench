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
typedef  int /*<<< orphan*/  bot_state_t ;

/* Variables and functions */
 int BotGetTeamMateTaskPreference (int /*<<< orphan*/ *,int) ; 
 int MAX_CLIENTS ; 
 int TEAMTP_ATTACKER ; 
 int TEAMTP_DEFENDER ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int BotSortTeamMatesByTaskPreference(bot_state_t *bs, int *teammates, int numteammates) {
	int defenders[MAX_CLIENTS], numdefenders;
	int attackers[MAX_CLIENTS], numattackers;
	int roamers[MAX_CLIENTS], numroamers;
	int i, preference;

	numdefenders = numattackers = numroamers = 0;
	for (i = 0; i < numteammates; i++) {
		preference = BotGetTeamMateTaskPreference(bs, teammates[i]);
		if (preference & TEAMTP_DEFENDER) {
			defenders[numdefenders++] = teammates[i];
		}
		else if (preference & TEAMTP_ATTACKER) {
			attackers[numattackers++] = teammates[i];
		}
		else {
			roamers[numroamers++] = teammates[i];
		}
	}
	numteammates = 0;
	//defenders at the front of the list
	memcpy(&teammates[numteammates], defenders, numdefenders * sizeof(int));
	numteammates += numdefenders;
	//roamers in the middle
	memcpy(&teammates[numteammates], roamers, numroamers * sizeof(int));
	numteammates += numroamers;
	//attacker in the back of the list
	memcpy(&teammates[numteammates], attackers, numattackers * sizeof(int));
	numteammates += numattackers;

	return numteammates;
}