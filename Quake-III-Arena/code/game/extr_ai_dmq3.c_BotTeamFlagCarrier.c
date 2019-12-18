#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int client; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_8__ {int /*<<< orphan*/  valid; } ;
typedef  TYPE_2__ aas_entityinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_2__*) ; 
 int /*<<< orphan*/  BotSameTeam (TYPE_1__*,int) ; 
 int /*<<< orphan*/  EntityCarriesFlag (TYPE_2__*) ; 
 int MAX_CLIENTS ; 
 int maxclients ; 

int BotTeamFlagCarrier(bot_state_t *bs) {
	int i;
	aas_entityinfo_t entinfo;

	for (i = 0; i < maxclients && i < MAX_CLIENTS; i++) {
		if (i == bs->client)
			continue;
		//
		BotEntityInfo(i, &entinfo);
		//if this player is active
		if (!entinfo.valid)
			continue;
		//if this player is carrying a flag
		if (!EntityCarriesFlag(&entinfo))
			continue;
		//if the flag carrier is not on the same team
		if (!BotSameTeam(bs, i))
			continue;
		//
		return i;
	}
	return -1;
}