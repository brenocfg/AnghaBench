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
typedef  double* vec3_t ;
typedef  int /*<<< orphan*/  netname ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_10__ {int /*<<< orphan*/ * origin; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; TYPE_1__ goal; struct TYPE_11__* prev; struct TYPE_11__* next; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_2__ bot_waypoint_t ;
struct TYPE_12__ {int /*<<< orphan*/  cs; TYPE_2__* checkpoints; } ;
typedef  TYPE_3__ bot_state_t ;
typedef  int /*<<< orphan*/  bot_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotAI_BotInitialChat (TYPE_3__*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ BotAddressedToBot (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* BotCreateWayPoint (char*,double*,int) ; 
 TYPE_2__* BotFindWayPoint (TYPE_2__*,char*) ; 
 int BotPointAreaNum (double*) ; 
 int /*<<< orphan*/  CHAT_TELL ; 
 int ClientFromName (char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  NAME ; 
 int /*<<< orphan*/  NETNAME ; 
 int /*<<< orphan*/  POSITION ; 
 int /*<<< orphan*/  TeamPlayIsOn () ; 
 int /*<<< orphan*/  VectorClear (double*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  sscanf (char*,char*,double*,double*,double*) ; 
 int /*<<< orphan*/  trap_BotEnterChat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMatchVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

void BotMatch_CheckPoint(bot_state_t *bs, bot_match_t *match) {
	int areanum, client;
	char buf[MAX_MESSAGE_SIZE];
	char netname[MAX_MESSAGE_SIZE];
	vec3_t position;
	bot_waypoint_t *cp;

	if (!TeamPlayIsOn()) return;
	//
	trap_BotMatchVariable(match, POSITION, buf, MAX_MESSAGE_SIZE);
	VectorClear(position);
	//
	trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
	client = ClientFromName(netname);
	//BotGPSToPosition(buf, position);
	sscanf(buf, "%f %f %f", &position[0], &position[1], &position[2]);
	position[2] += 0.5;
	areanum = BotPointAreaNum(position);
	if (!areanum) {
		if (BotAddressedToBot(bs, match)) {
			BotAI_BotInitialChat(bs, "checkpoint_invalid", NULL);
			trap_BotEnterChat(bs->cs, client, CHAT_TELL);
		}
		return;
	}
	//
	trap_BotMatchVariable(match, NAME, buf, MAX_MESSAGE_SIZE);
	//check if there already exists a checkpoint with this name
	cp = BotFindWayPoint(bs->checkpoints, buf);
	if (cp) {
		if (cp->next) cp->next->prev = cp->prev;
		if (cp->prev) cp->prev->next = cp->next;
		else bs->checkpoints = cp->next;
		cp->inuse = qfalse;
	}
	//create a new check point
	cp = BotCreateWayPoint(buf, position, areanum);
	//add the check point to the bot's known chech points
	cp->next = bs->checkpoints;
	if (bs->checkpoints) bs->checkpoints->prev = cp;
	bs->checkpoints = cp;
	//
	if (BotAddressedToBot(bs, match)) {
		Com_sprintf(buf, sizeof(buf), "%1.0f %1.0f %1.0f", cp->goal.origin[0],
													cp->goal.origin[1],
													cp->goal.origin[2]);

		BotAI_BotInitialChat(bs, "checkpoint_confirm", cp->name, buf, NULL);
		trap_BotEnterChat(bs->cs, client, CHAT_TELL);
	}
}