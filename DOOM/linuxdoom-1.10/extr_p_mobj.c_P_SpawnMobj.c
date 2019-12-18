#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  sprite; int /*<<< orphan*/  tics; } ;
typedef  TYPE_4__ state_t ;
typedef  size_t mobjtype_t ;
struct TYPE_19__ {size_t spawnstate; scalar_t__ height; int /*<<< orphan*/  reactiontime; int /*<<< orphan*/  spawnhealth; int /*<<< orphan*/  flags; int /*<<< orphan*/  radius; } ;
typedef  TYPE_5__ mobjinfo_t ;
struct TYPE_17__ {scalar_t__ acp1; } ;
struct TYPE_14__ {TYPE_3__ function; } ;
struct TYPE_20__ {size_t type; int lastlook; TYPE_13__ thinker; scalar_t__ z; TYPE_5__* info; scalar_t__ ceilingz; scalar_t__ floorz; TYPE_2__* subsector; int /*<<< orphan*/  frame; int /*<<< orphan*/  sprite; int /*<<< orphan*/  tics; TYPE_4__* state; int /*<<< orphan*/  reactiontime; int /*<<< orphan*/  health; int /*<<< orphan*/  flags; scalar_t__ height; int /*<<< orphan*/  radius; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_6__ mobj_t ;
typedef  scalar_t__ fixed_t ;
typedef  scalar_t__ actionf_p1 ;
struct TYPE_16__ {TYPE_1__* sector; } ;
struct TYPE_15__ {scalar_t__ ceilingheight; scalar_t__ floorheight; } ;

/* Variables and functions */
 int MAXPLAYERS ; 
 scalar_t__ ONCEILINGZ ; 
 scalar_t__ ONFLOORZ ; 
 int /*<<< orphan*/  PU_LEVEL ; 
 int /*<<< orphan*/  P_AddThinker (TYPE_13__*) ; 
 scalar_t__ P_MobjThinker ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetThingPosition (TYPE_6__*) ; 
 TYPE_6__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gameskill ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* mobjinfo ; 
 scalar_t__ sk_nightmare ; 
 TYPE_4__* states ; 

mobj_t*
P_SpawnMobj
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  mobjtype_t	type )
{
    mobj_t*	mobj;
    state_t*	st;
    mobjinfo_t*	info;
	
    mobj = Z_Malloc (sizeof(*mobj), PU_LEVEL, NULL);
    memset (mobj, 0, sizeof (*mobj));
    info = &mobjinfo[type];
	
    mobj->type = type;
    mobj->info = info;
    mobj->x = x;
    mobj->y = y;
    mobj->radius = info->radius;
    mobj->height = info->height;
    mobj->flags = info->flags;
    mobj->health = info->spawnhealth;

    if (gameskill != sk_nightmare)
	mobj->reactiontime = info->reactiontime;
    
    mobj->lastlook = P_Random () % MAXPLAYERS;
    // do not set the state with P_SetMobjState,
    // because action routines can not be called yet
    st = &states[info->spawnstate];

    mobj->state = st;
    mobj->tics = st->tics;
    mobj->sprite = st->sprite;
    mobj->frame = st->frame;

    // set subsector and/or block links
    P_SetThingPosition (mobj);
	
    mobj->floorz = mobj->subsector->sector->floorheight;
    mobj->ceilingz = mobj->subsector->sector->ceilingheight;

    if (z == ONFLOORZ)
	mobj->z = mobj->floorz;
    else if (z == ONCEILINGZ)
	mobj->z = mobj->ceilingz - mobj->info->height;
    else 
	mobj->z = z;

    mobj->thinker.function.acp1 = (actionf_p1)P_MobjThinker;
	
    P_AddThinker (&mobj->thinker);

    return mobj;
}