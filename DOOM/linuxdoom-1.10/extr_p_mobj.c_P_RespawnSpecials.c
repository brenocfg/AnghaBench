#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* sector; } ;
typedef  TYPE_2__ subsector_t ;
struct TYPE_13__ {int x; int y; scalar_t__ type; int angle; } ;
struct TYPE_12__ {int angle; TYPE_4__ spawnpoint; } ;
typedef  TYPE_3__ mobj_t ;
typedef  TYPE_4__ mapthing_t ;
typedef  int fixed_t ;
struct TYPE_14__ {scalar_t__ doomednum; int flags; } ;
struct TYPE_10__ {int floorheight; } ;

/* Variables and functions */
 int ANG45 ; 
 int FRACBITS ; 
 int ITEMQUESIZE ; 
 int MF_SPAWNCEILING ; 
 int MT_IFOG ; 
 int NUMMOBJTYPES ; 
 int ONCEILINGZ ; 
 int ONFLOORZ ; 
 TYPE_3__* P_SpawnMobj (int,int,int,int) ; 
 TYPE_2__* R_PointInSubsector (int,int) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int deathmatch ; 
 size_t iquehead ; 
 size_t iquetail ; 
 TYPE_4__* itemrespawnque ; 
 int* itemrespawntime ; 
 int leveltime ; 
 TYPE_5__* mobjinfo ; 
 int /*<<< orphan*/  sfx_itmbk ; 

void P_RespawnSpecials (void)
{
    fixed_t		x;
    fixed_t		y;
    fixed_t		z;
    
    subsector_t*	ss; 
    mobj_t*		mo;
    mapthing_t*		mthing;
    
    int			i;

    // only respawn items in deathmatch
    if (deathmatch != 2)
	return;	// 

    // nothing left to respawn?
    if (iquehead == iquetail)
	return;		

    // wait at least 30 seconds
    if (leveltime - itemrespawntime[iquetail] < 30*35)
	return;			

    mthing = &itemrespawnque[iquetail];
	
    x = mthing->x << FRACBITS; 
    y = mthing->y << FRACBITS; 
	  
    // spawn a teleport fog at the new spot
    ss = R_PointInSubsector (x,y); 
    mo = P_SpawnMobj (x, y, ss->sector->floorheight , MT_IFOG); 
    S_StartSound (mo, sfx_itmbk);

    // find which type to spawn
    for (i=0 ; i< NUMMOBJTYPES ; i++)
    {
	if (mthing->type == mobjinfo[i].doomednum)
	    break;
    }
    
    // spawn it
    if (mobjinfo[i].flags & MF_SPAWNCEILING)
	z = ONCEILINGZ;
    else
	z = ONFLOORZ;

    mo = P_SpawnMobj (x,y,z, i);
    mo->spawnpoint = *mthing;	
    mo->angle = ANG45 * (mthing->angle/45);

    // pull it from the que
    iquetail = (iquetail+1)&(ITEMQUESIZE-1);
}