#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int moveflags; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  thinktime; int /*<<< orphan*/  client; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  viewoffset; int /*<<< orphan*/  velocity; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ bot_movestate_t ;
struct TYPE_6__ {int or_moveflags; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  thinktime; int /*<<< orphan*/  client; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  viewoffset; int /*<<< orphan*/  velocity; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ bot_initmove_t ;

/* Variables and functions */
 TYPE_1__* BotMoveStateFromHandle (int) ; 
 int MFL_GRAPPLEPULL ; 
 int MFL_ONGROUND ; 
 int MFL_TELEPORTED ; 
 int MFL_WALK ; 
 int MFL_WATERJUMP ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BotInitMoveState(int handle, bot_initmove_t *initmove)
{
	bot_movestate_t *ms;

	ms = BotMoveStateFromHandle(handle);
	if (!ms) return;
	VectorCopy(initmove->origin, ms->origin);
	VectorCopy(initmove->velocity, ms->velocity);
	VectorCopy(initmove->viewoffset, ms->viewoffset);
	ms->entitynum = initmove->entitynum;
	ms->client = initmove->client;
	ms->thinktime = initmove->thinktime;
	ms->presencetype = initmove->presencetype;
	VectorCopy(initmove->viewangles, ms->viewangles);
	//
	ms->moveflags &= ~MFL_ONGROUND;
	if (initmove->or_moveflags & MFL_ONGROUND) ms->moveflags |= MFL_ONGROUND;
	ms->moveflags &= ~MFL_TELEPORTED;	
	if (initmove->or_moveflags & MFL_TELEPORTED) ms->moveflags |= MFL_TELEPORTED;
	ms->moveflags &= ~MFL_WATERJUMP;
	if (initmove->or_moveflags & MFL_WATERJUMP) ms->moveflags |= MFL_WATERJUMP;
	ms->moveflags &= ~MFL_WALK;
	if (initmove->or_moveflags & MFL_WALK) ms->moveflags |= MFL_WALK;
	ms->moveflags &= ~MFL_GRAPPLEPULL;
	if (initmove->or_moveflags & MFL_GRAPPLEPULL) ms->moveflags |= MFL_GRAPPLEPULL;
}