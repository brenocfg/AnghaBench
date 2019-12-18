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
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  mapname ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_7__ {scalar_t__* origin; int client; scalar_t__ entitynum; int* ideal_viewangles; int /*<<< orphan*/  tfl; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  character; int /*<<< orphan*/  eye; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_8__ {scalar_t__ number; scalar_t__* origin; int /*<<< orphan*/  valid; } ;
typedef  TYPE_2__ aas_entityinfo_t ;

/* Variables and functions */
 void* AngleMod (int) ; 
 int /*<<< orphan*/  BFL_IDEALVIEWSET ; 
 int /*<<< orphan*/  BotEntityInfo (int,TYPE_2__*) ; 
 scalar_t__ BotSameTeam (TYPE_1__*,int) ; 
 int /*<<< orphan*/  CHARACTERISTIC_AIM_ACCURACY ; 
 scalar_t__ EntityIsDead (TYPE_2__*) ; 
 scalar_t__ InFieldOfVision (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_CLIENTS ; 
 size_t PITCH ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  TFL_FUNCBOB ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 size_t YAW ; 
 int crandom () ; 
 int maxclients ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 float trap_Characteristic_BFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_EA_Attack (int) ; 
 int /*<<< orphan*/  trap_GetServerinfo (char*,int) ; 
 int /*<<< orphan*/  vectoangles (scalar_t__*,int*) ; 

void BotMapScripts(bot_state_t *bs) {
	char info[1024];
	char mapname[128];
	int i, shootbutton;
	float aim_accuracy;
	aas_entityinfo_t entinfo;
	vec3_t dir;

	trap_GetServerinfo(info, sizeof(info));

	strncpy(mapname, Info_ValueForKey( info, "mapname" ), sizeof(mapname)-1);
	mapname[sizeof(mapname)-1] = '\0';

	if (!Q_stricmp(mapname, "q3tourney6")) {
		vec3_t mins = {700, 204, 672}, maxs = {964, 468, 680};
		vec3_t buttonorg = {304, 352, 920};
		//NOTE: NEVER use the func_bobbing in q3tourney6
		bs->tfl &= ~TFL_FUNCBOB;
		//if the bot is below the bounding box
		if (bs->origin[0] > mins[0] && bs->origin[0] < maxs[0]) {
			if (bs->origin[1] > mins[1] && bs->origin[1] < maxs[1]) {
				if (bs->origin[2] < mins[2]) {
					return;
				}
			}
		}
		shootbutton = qfalse;
		//if an enemy is below this bounding box then shoot the button
		for (i = 0; i < maxclients && i < MAX_CLIENTS; i++) {

			if (i == bs->client) continue;
			//
			BotEntityInfo(i, &entinfo);
			//
			if (!entinfo.valid) continue;
			//if the enemy isn't dead and the enemy isn't the bot self
			if (EntityIsDead(&entinfo) || entinfo.number == bs->entitynum) continue;
			//
			if (entinfo.origin[0] > mins[0] && entinfo.origin[0] < maxs[0]) {
				if (entinfo.origin[1] > mins[1] && entinfo.origin[1] < maxs[1]) {
					if (entinfo.origin[2] < mins[2]) {
						//if there's a team mate below the crusher
						if (BotSameTeam(bs, i)) {
							shootbutton = qfalse;
							break;
						}
						else {
							shootbutton = qtrue;
						}
					}
				}
			}
		}
		if (shootbutton) {
			bs->flags |= BFL_IDEALVIEWSET;
			VectorSubtract(buttonorg, bs->eye, dir);
			vectoangles(dir, bs->ideal_viewangles);
			aim_accuracy = trap_Characteristic_BFloat(bs->character, CHARACTERISTIC_AIM_ACCURACY, 0, 1);
			bs->ideal_viewangles[PITCH] += 8 * crandom() * (1 - aim_accuracy);
			bs->ideal_viewangles[PITCH] = AngleMod(bs->ideal_viewangles[PITCH]);
			bs->ideal_viewangles[YAW] += 8 * crandom() * (1 - aim_accuracy);
			bs->ideal_viewangles[YAW] = AngleMod(bs->ideal_viewangles[YAW]);
			//
			if (InFieldOfVision(bs->viewangles, 20, bs->ideal_viewangles)) {
				trap_EA_Attack(bs->client);
			}
		}
	}
	else if (!Q_stricmp(mapname, "mpq3tourney6")) {
		//NOTE: NEVER use the func_bobbing in mpq3tourney6
		bs->tfl &= ~TFL_FUNCBOB;
	}
}