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
struct TYPE_9__ {scalar_t__ z; scalar_t__ floorz; int momz; int flags; int height; scalar_t__ ceilingz; TYPE_2__* player; TYPE_1__* target; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ mobj_t ;
typedef  int fixed_t ;
struct TYPE_8__ {scalar_t__ viewheight; int deltaviewheight; } ;
struct TYPE_7__ {int z; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int FLOATSPEED ; 
 int GRAVITY ; 
 int MF_FLOAT ; 
 int MF_INFLOAT ; 
 int MF_MISSILE ; 
 int MF_NOCLIP ; 
 int MF_NOGRAVITY ; 
 int MF_SKULLFLY ; 
 int P_AproxDistance (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  P_ExplodeMissile (TYPE_3__*) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int VIEWHEIGHT ; 
 int /*<<< orphan*/  sfx_oof ; 

void P_ZMovement (mobj_t* mo)
{
    fixed_t	dist;
    fixed_t	delta;
    
    // check for smooth step up
    if (mo->player && mo->z < mo->floorz)
    {
	mo->player->viewheight -= mo->floorz-mo->z;

	mo->player->deltaviewheight
	    = (VIEWHEIGHT - mo->player->viewheight)>>3;
    }
    
    // adjust height
    mo->z += mo->momz;
	
    if ( mo->flags & MF_FLOAT
	 && mo->target)
    {
	// float down towards target if too close
	if ( !(mo->flags & MF_SKULLFLY)
	     && !(mo->flags & MF_INFLOAT) )
	{
	    dist = P_AproxDistance (mo->x - mo->target->x,
				    mo->y - mo->target->y);
	    
	    delta =(mo->target->z + (mo->height>>1)) - mo->z;

	    if (delta<0 && dist < -(delta*3) )
		mo->z -= FLOATSPEED;
	    else if (delta>0 && dist < (delta*3) )
		mo->z += FLOATSPEED;			
	}
	
    }
    
    // clip movement
    if (mo->z <= mo->floorz)
    {
	// hit the floor

	// Note (id):
	//  somebody left this after the setting momz to 0,
	//  kinda useless there.
	if (mo->flags & MF_SKULLFLY)
	{
	    // the skull slammed into something
	    mo->momz = -mo->momz;
	}
	
	if (mo->momz < 0)
	{
	    if (mo->player
		&& mo->momz < -GRAVITY*8)	
	    {
		// Squat down.
		// Decrease viewheight for a moment
		// after hitting the ground (hard),
		// and utter appropriate sound.
		mo->player->deltaviewheight = mo->momz>>3;
		S_StartSound (mo, sfx_oof);
	    }
	    mo->momz = 0;
	}
	mo->z = mo->floorz;

	if ( (mo->flags & MF_MISSILE)
	     && !(mo->flags & MF_NOCLIP) )
	{
	    P_ExplodeMissile (mo);
	    return;
	}
    }
    else if (! (mo->flags & MF_NOGRAVITY) )
    {
	if (mo->momz == 0)
	    mo->momz = -GRAVITY*2;
	else
	    mo->momz -= GRAVITY;
    }
	
    if (mo->z + mo->height > mo->ceilingz)
    {
	// hit the ceiling
	if (mo->momz > 0)
	    mo->momz = 0;
	{
	    mo->z = mo->ceilingz - mo->height;
	}

	if (mo->flags & MF_SKULLFLY)
	{	// the skull slammed into something
	    mo->momz = -mo->momz;
	}
	
	if ( (mo->flags & MF_MISSILE)
	     && !(mo->flags & MF_NOCLIP) )
	{
	    P_ExplodeMissile (mo);
	    return;
	}
    }
}