#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mobjtype_t ;
struct TYPE_10__ {int flags; int type; int height; int tics; int /*<<< orphan*/  y; int /*<<< orphan*/  x; TYPE_1__* info; int /*<<< orphan*/  health; TYPE_3__* player; } ;
typedef  TYPE_2__ mobj_t ;
struct TYPE_11__ {int /*<<< orphan*/  playerstate; int /*<<< orphan*/ * frags; int /*<<< orphan*/  killcount; } ;
struct TYPE_9__ {scalar_t__ deathstate; scalar_t__ xdeathstate; int /*<<< orphan*/  spawnhealth; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_Stop () ; 
 int MF_CORPSE ; 
 int MF_COUNTKILL ; 
 int MF_DROPOFF ; 
 int MF_DROPPED ; 
 int MF_FLOAT ; 
 int MF_NOGRAVITY ; 
 int MF_SHOOTABLE ; 
 int MF_SKULLFLY ; 
 int MF_SOLID ; 
 int /*<<< orphan*/  MT_CHAINGUN ; 
#define  MT_CHAINGUY 131 
 int /*<<< orphan*/  MT_CLIP ; 
#define  MT_POSSESSED 130 
 int /*<<< orphan*/  MT_SHOTGUN ; 
#define  MT_SHOTGUY 129 
 int MT_SKULL ; 
#define  MT_WOLFSS 128 
 int /*<<< orphan*/  ONFLOORZ ; 
 int /*<<< orphan*/  PST_DEAD ; 
 int /*<<< orphan*/  P_DropWeapon (TYPE_3__*) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_2__*,scalar_t__) ; 
 TYPE_2__* P_SpawnMobj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ automapactive ; 
 size_t consoleplayer ; 
 int /*<<< orphan*/  netgame ; 
 TYPE_3__* players ; 

void
P_KillMobj
( mobj_t*	source,
  mobj_t*	target )
{
    mobjtype_t	item;
    mobj_t*	mo;
	
    target->flags &= ~(MF_SHOOTABLE|MF_FLOAT|MF_SKULLFLY);

    if (target->type != MT_SKULL)
	target->flags &= ~MF_NOGRAVITY;

    target->flags |= MF_CORPSE|MF_DROPOFF;
    target->height >>= 2;

    if (source && source->player)
    {
	// count for intermission
	if (target->flags & MF_COUNTKILL)
	    source->player->killcount++;	

	if (target->player)
	    source->player->frags[target->player-players]++;
    }
    else if (!netgame && (target->flags & MF_COUNTKILL) )
    {
	// count all monster deaths,
	// even those caused by other monsters
	players[0].killcount++;
    }
    
    if (target->player)
    {
	// count environment kills against you
	if (!source)	
	    target->player->frags[target->player-players]++;
			
	target->flags &= ~MF_SOLID;
	target->player->playerstate = PST_DEAD;
	P_DropWeapon (target->player);

	if (target->player == &players[consoleplayer]
	    && automapactive)
	{
	    // don't die in auto map,
	    // switch view prior to dying
	    AM_Stop ();
	}
	
    }

    if (target->health < -target->info->spawnhealth 
	&& target->info->xdeathstate)
    {
	P_SetMobjState (target, target->info->xdeathstate);
    }
    else
	P_SetMobjState (target, target->info->deathstate);
    target->tics -= P_Random()&3;

    if (target->tics < 1)
	target->tics = 1;
		
    //	I_StartSound (&actor->r, actor->info->deathsound);


    // Drop stuff.
    // This determines the kind of object spawned
    // during the death frame of a thing.
    switch (target->type)
    {
      case MT_WOLFSS:
      case MT_POSSESSED:
	item = MT_CLIP;
	break;
	
      case MT_SHOTGUY:
	item = MT_SHOTGUN;
	break;
	
      case MT_CHAINGUY:
	item = MT_CHAINGUN;
	break;
	
      default:
	return;
    }

    mo = P_SpawnMobj (target->x,target->y,ONFLOORZ, item);
    mo->flags |= MF_DROPPED;	// special versions of items
}