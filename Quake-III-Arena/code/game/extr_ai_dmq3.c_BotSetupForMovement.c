#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ groundEntityNum; int pm_flags; scalar_t__ pm_time; scalar_t__ viewheight; int /*<<< orphan*/  velocity; int /*<<< orphan*/  origin; } ;
struct TYPE_8__ {double walker; int /*<<< orphan*/  ms; int /*<<< orphan*/  viewangles; TYPE_1__ cur_ps; int /*<<< orphan*/  thinktime; int /*<<< orphan*/  client; int /*<<< orphan*/  entitynum; } ;
typedef  TYPE_2__ bot_state_t ;
struct TYPE_9__ {int /*<<< orphan*/  viewangles; int /*<<< orphan*/  or_moveflags; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  thinktime; int /*<<< orphan*/  client; int /*<<< orphan*/  entitynum; int /*<<< orphan*/ * viewoffset; int /*<<< orphan*/  velocity; int /*<<< orphan*/  origin; } ;
typedef  TYPE_3__ bot_initmove_t ;

/* Variables and functions */
 scalar_t__ ENTITYNUM_NONE ; 
 int /*<<< orphan*/  MFL_ONGROUND ; 
 int /*<<< orphan*/  MFL_TELEPORTED ; 
 int /*<<< orphan*/  MFL_WALK ; 
 int /*<<< orphan*/  MFL_WATERJUMP ; 
 int PMF_DUCKED ; 
 int PMF_TIME_KNOCKBACK ; 
 int PMF_TIME_WATERJUMP ; 
 int /*<<< orphan*/  PRESENCE_CROUCH ; 
 int /*<<< orphan*/  PRESENCE_NORMAL ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_BotInitMoveState (int /*<<< orphan*/ ,TYPE_3__*) ; 

void BotSetupForMovement(bot_state_t *bs) {
	bot_initmove_t initmove;

	memset(&initmove, 0, sizeof(bot_initmove_t));
	VectorCopy(bs->cur_ps.origin, initmove.origin);
	VectorCopy(bs->cur_ps.velocity, initmove.velocity);
	VectorClear(initmove.viewoffset);
	initmove.viewoffset[2] += bs->cur_ps.viewheight;
	initmove.entitynum = bs->entitynum;
	initmove.client = bs->client;
	initmove.thinktime = bs->thinktime;
	//set the onground flag
	if (bs->cur_ps.groundEntityNum != ENTITYNUM_NONE) initmove.or_moveflags |= MFL_ONGROUND;
	//set the teleported flag
	if ((bs->cur_ps.pm_flags & PMF_TIME_KNOCKBACK) && (bs->cur_ps.pm_time > 0)) {
		initmove.or_moveflags |= MFL_TELEPORTED;
	}
	//set the waterjump flag
	if ((bs->cur_ps.pm_flags & PMF_TIME_WATERJUMP) && (bs->cur_ps.pm_time > 0)) {
		initmove.or_moveflags |= MFL_WATERJUMP;
	}
	//set presence type
	if (bs->cur_ps.pm_flags & PMF_DUCKED) initmove.presencetype = PRESENCE_CROUCH;
	else initmove.presencetype = PRESENCE_NORMAL;
	//
	if (bs->walker > 0.5) initmove.or_moveflags |= MFL_WALK;
	//
	VectorCopy(bs->viewangles, initmove.viewangles);
	//
	trap_BotInitMoveState(bs->ms, &initmove);
}