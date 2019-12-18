#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
typedef  int /*<<< orphan*/  goalname ;
typedef  int /*<<< orphan*/  carrying ;
struct TYPE_10__ {scalar_t__ entitynum; int /*<<< orphan*/  number; } ;
struct TYPE_11__ {char** inventory; int ltgtype; scalar_t__ client; int /*<<< orphan*/  gs; TYPE_1__ teamgoal; int /*<<< orphan*/  teammate; int /*<<< orphan*/  teamleader; } ;
typedef  TYPE_2__ bot_state_t ;
struct TYPE_12__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_3__ bot_goal_t ;
typedef  int /*<<< orphan*/  action ;

/* Variables and functions */
 scalar_t__ Bot1FCTFCarryingFlag (TYPE_2__*) ; 
 scalar_t__ BotCTFCarryingFlag (TYPE_2__*) ; 
 scalar_t__ BotHarvesterCarryingCubes (TYPE_2__*) ; 
 scalar_t__ BotTeam (TYPE_2__*) ; 
 scalar_t__ CS_BOTINFO ; 
 int /*<<< orphan*/  ClientName (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  EasyClientName (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_HARVESTER ; 
 size_t INVENTORY_BLUECUBE ; 
 size_t INVENTORY_REDCUBE ; 
#define  LTG_ATTACKENEMYBASE 140 
#define  LTG_CAMP 139 
#define  LTG_CAMPORDER 138 
#define  LTG_DEFENDKEYAREA 137 
#define  LTG_GETFLAG 136 
#define  LTG_GETITEM 135 
#define  LTG_HARVEST 134 
#define  LTG_KILL 133 
#define  LTG_PATROL 132 
#define  LTG_RETURNFLAG 131 
#define  LTG_RUSHBASE 130 
#define  LTG_TEAMACCOMPANY 129 
#define  LTG_TEAMHELP 128 
 int MAX_MESSAGE_SIZE ; 
 scalar_t__ Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ TEAM_RED ; 
 scalar_t__ gametype ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  trap_BotGetTopGoal (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  trap_BotGoalName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_SetConfigstring (scalar_t__,char*) ; 
 char* va (char*,char*,char*,char*) ; 

void BotSetInfoConfigString(bot_state_t *bs) {
	char goalname[MAX_MESSAGE_SIZE];
	char netname[MAX_MESSAGE_SIZE];
	char action[MAX_MESSAGE_SIZE];
	char *leader, carrying[32], *cs;
	bot_goal_t goal;
	//
	ClientName(bs->client, netname, sizeof(netname));
	if (Q_stricmp(netname, bs->teamleader) == 0) leader = "L";
	else leader = " ";

	strcpy(carrying, "  ");
	if (gametype == GT_CTF) {
		if (BotCTFCarryingFlag(bs)) {
			strcpy(carrying, "F ");
		}
	}
#ifdef MISSIONPACK
	else if (gametype == GT_1FCTF) {
		if (Bot1FCTFCarryingFlag(bs)) {
			strcpy(carrying, "F ");
		}
	}
	else if (gametype == GT_HARVESTER) {
		if (BotHarvesterCarryingCubes(bs)) {
			if (BotTeam(bs) == TEAM_RED) Com_sprintf(carrying, sizeof(carrying), "%2d", bs->inventory[INVENTORY_REDCUBE]);
			else Com_sprintf(carrying, sizeof(carrying), "%2d", bs->inventory[INVENTORY_BLUECUBE]);
		}
	}
#endif

	switch(bs->ltgtype) {
		case LTG_TEAMHELP:
		{
			EasyClientName(bs->teammate, goalname, sizeof(goalname));
			Com_sprintf(action, sizeof(action), "helping %s", goalname);
			break;
		}
		case LTG_TEAMACCOMPANY:
		{
			EasyClientName(bs->teammate, goalname, sizeof(goalname));
			Com_sprintf(action, sizeof(action), "accompanying %s", goalname);
			break;
		}
		case LTG_DEFENDKEYAREA:
		{
			trap_BotGoalName(bs->teamgoal.number, goalname, sizeof(goalname));
			Com_sprintf(action, sizeof(action), "defending %s", goalname);
			break;
		}
		case LTG_GETITEM:
		{
			trap_BotGoalName(bs->teamgoal.number, goalname, sizeof(goalname));
			Com_sprintf(action, sizeof(action), "getting item %s", goalname);
			break;
		}
		case LTG_KILL:
		{
			ClientName(bs->teamgoal.entitynum, goalname, sizeof(goalname));
			Com_sprintf(action, sizeof(action), "killing %s", goalname);
			break;
		}
		case LTG_CAMP:
		case LTG_CAMPORDER:
		{
			Com_sprintf(action, sizeof(action), "camping");
			break;
		}
		case LTG_PATROL:
		{
			Com_sprintf(action, sizeof(action), "patrolling");
			break;
		}
		case LTG_GETFLAG:
		{
			Com_sprintf(action, sizeof(action), "capturing flag");
			break;
		}
		case LTG_RUSHBASE:
		{
			Com_sprintf(action, sizeof(action), "rushing base");
			break;
		}
		case LTG_RETURNFLAG:
		{
			Com_sprintf(action, sizeof(action), "returning flag");
			break;
		}
		case LTG_ATTACKENEMYBASE:
		{
			Com_sprintf(action, sizeof(action), "attacking the enemy base");
			break;
		}
		case LTG_HARVEST:
		{
			Com_sprintf(action, sizeof(action), "harvesting");
			break;
		}
		default:
		{
			trap_BotGetTopGoal(bs->gs, &goal);
			trap_BotGoalName(goal.number, goalname, sizeof(goalname));
			Com_sprintf(action, sizeof(action), "roaming %s", goalname);
			break;
		}
	}
  	cs = va("l\\%s\\c\\%s\\a\\%s",
				leader,
				carrying,
				action);
  	trap_SetConfigstring (CS_BOTINFO + bs->client, cs);
}