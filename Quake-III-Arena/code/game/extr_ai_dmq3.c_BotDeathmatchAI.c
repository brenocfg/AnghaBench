#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  userinfo ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  gender ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_21__ {int /*<<< orphan*/ * persistant; } ;
struct TYPE_20__ {int /*<<< orphan*/  team; } ;
struct TYPE_22__ {scalar_t__ setupcount; int entergame_time; TYPE_2__ cur_ps; int /*<<< orphan*/  lasthitcount; int /*<<< orphan*/ * inventory; int /*<<< orphan*/  lastframe_health; int /*<<< orphan*/  client; int /*<<< orphan*/  gs; int /*<<< orphan*/  inuse; scalar_t__ (* ainode ) (TYPE_3__*) ;scalar_t__ entergamechat; scalar_t__ stand_time; int /*<<< orphan*/  flags; int /*<<< orphan*/  cs; TYPE_1__ settings; int /*<<< orphan*/  map_restart; int /*<<< orphan*/  character; } ;
typedef  TYPE_3__ bot_state_t ;
struct TYPE_23__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Seek_LTG (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  AIEnter_Stand (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  BFL_IDEALVIEWSET ; 
 int /*<<< orphan*/  BotAI_Print (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 scalar_t__ BotChatTime (TYPE_3__*) ; 
 scalar_t__ BotChat_EnterGame (TYPE_3__*) ; 
 int /*<<< orphan*/  BotCheckAir (TYPE_3__*) ; 
 int /*<<< orphan*/  BotCheckConsoleMessages (TYPE_3__*) ; 
 int /*<<< orphan*/  BotCheckSnapshot (TYPE_3__*) ; 
 int /*<<< orphan*/  BotDumpNodeSwitches (TYPE_3__*) ; 
 int /*<<< orphan*/  BotIntermission (TYPE_3__*) ; 
 int /*<<< orphan*/  BotIsObserver (TYPE_3__*) ; 
 int /*<<< orphan*/  BotResetNodeSwitches () ; 
 int /*<<< orphan*/  BotSetTeleportTime (TYPE_3__*) ; 
 int /*<<< orphan*/  BotSetupAlternativeRouteGoals () ; 
 int /*<<< orphan*/  BotTeamAI (TYPE_3__*) ; 
 int /*<<< orphan*/  BotUpdateInventory (TYPE_3__*) ; 
 int /*<<< orphan*/  CHARACTERISTIC_GENDER ; 
 int /*<<< orphan*/  CHAT_GENDERFEMALE ; 
 int /*<<< orphan*/  CHAT_GENDERLESS ; 
 int /*<<< orphan*/  CHAT_GENDERMALE ; 
 int /*<<< orphan*/  ClientName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int FloatTime () ; 
 scalar_t__ GT_TOURNAMENT ; 
 size_t INVENTORY_HEALTH ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,char*) ; 
 int MAX_INFO_STRING ; 
 int MAX_NODESWITCHES ; 
 size_t PERS_HITS ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_5__ g_gametype ; 
 scalar_t__ qtrue ; 
 scalar_t__ stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  trap_BotDumpAvoidGoals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotDumpGoalStack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotSetChatGender (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotSetChatName (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Characteristic_String (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_EA_Command (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_GetUserinfo (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_SetUserinfo (int /*<<< orphan*/ ,char*) ; 

void BotDeathmatchAI(bot_state_t *bs, float thinktime) {
	char gender[144], name[144], buf[144];
	char userinfo[MAX_INFO_STRING];
	int i;

	//if the bot has just been setup
	if (bs->setupcount > 0) {
		bs->setupcount--;
		if (bs->setupcount > 0) return;
		//get the gender characteristic
		trap_Characteristic_String(bs->character, CHARACTERISTIC_GENDER, gender, sizeof(gender));
		//set the bot gender
		trap_GetUserinfo(bs->client, userinfo, sizeof(userinfo));
		Info_SetValueForKey(userinfo, "sex", gender);
		trap_SetUserinfo(bs->client, userinfo);
		//set the team
		if ( !bs->map_restart && g_gametype.integer != GT_TOURNAMENT ) {
			Com_sprintf(buf, sizeof(buf), "team %s", bs->settings.team);
			trap_EA_Command(bs->client, buf);
		}
		//set the chat gender
		if (gender[0] == 'm') trap_BotSetChatGender(bs->cs, CHAT_GENDERMALE);
		else if (gender[0] == 'f')  trap_BotSetChatGender(bs->cs, CHAT_GENDERFEMALE);
		else  trap_BotSetChatGender(bs->cs, CHAT_GENDERLESS);
		//set the chat name
		ClientName(bs->client, name, sizeof(name));
		trap_BotSetChatName(bs->cs, name, bs->client);
		//
		bs->lastframe_health = bs->inventory[INVENTORY_HEALTH];
		bs->lasthitcount = bs->cur_ps.persistant[PERS_HITS];
		//
		bs->setupcount = 0;
		//
		BotSetupAlternativeRouteGoals();
	}
	//no ideal view set
	bs->flags &= ~BFL_IDEALVIEWSET;
	//
	if (!BotIntermission(bs)) {
		//set the teleport time
		BotSetTeleportTime(bs);
		//update some inventory values
		BotUpdateInventory(bs);
		//check out the snapshot
		BotCheckSnapshot(bs);
		//check for air
		BotCheckAir(bs);
	}
	//check the console messages
	BotCheckConsoleMessages(bs);
	//if not in the intermission and not in observer mode
	if (!BotIntermission(bs) && !BotIsObserver(bs)) {
		//do team AI
		BotTeamAI(bs);
	}
	//if the bot has no ai node
	if (!bs->ainode) {
		AIEnter_Seek_LTG(bs, "BotDeathmatchAI: no ai node");
	}
	//if the bot entered the game less than 8 seconds ago
	if (!bs->entergamechat && bs->entergame_time > FloatTime() - 8) {
		if (BotChat_EnterGame(bs)) {
			bs->stand_time = FloatTime() + BotChatTime(bs);
			AIEnter_Stand(bs, "BotDeathmatchAI: chat enter game");
		}
		bs->entergamechat = qtrue;
	}
	//reset the node switches from the previous frame
	BotResetNodeSwitches();
	//execute AI nodes
	for (i = 0; i < MAX_NODESWITCHES; i++) {
		if (bs->ainode(bs)) break;
	}
	//if the bot removed itself :)
	if (!bs->inuse) return;
	//if the bot executed too many AI nodes
	if (i >= MAX_NODESWITCHES) {
		trap_BotDumpGoalStack(bs->gs);
		trap_BotDumpAvoidGoals(bs->gs);
		BotDumpNodeSwitches(bs);
		ClientName(bs->client, name, sizeof(name));
		BotAI_Print(PRT_ERROR, "%s at %1.1f switched more than %d AI nodes\n", name, FloatTime(), MAX_NODESWITCHES);
	}
	//
	bs->lastframe_health = bs->inventory[INVENTORY_HEALTH];
	bs->lasthitcount = bs->cur_ps.persistant[PERS_HITS];
}