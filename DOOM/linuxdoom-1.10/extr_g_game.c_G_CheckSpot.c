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
typedef  int /*<<< orphan*/  mobj_t ;
struct TYPE_12__ {int x; int y; int angle; } ;
typedef  TYPE_3__ mapthing_t ;
typedef  int fixed_t ;
typedef  int boolean ;
struct TYPE_14__ {int x; int y; } ;
struct TYPE_13__ {int viewz; TYPE_5__* mo; } ;
struct TYPE_10__ {int /*<<< orphan*/  floorheight; } ;

/* Variables and functions */
 int ANG45 ; 
 int ANGLETOFINESHIFT ; 
 size_t BODYQUESIZE ; 
 int FRACBITS ; 
 int /*<<< orphan*/  MT_TFOG ; 
 int /*<<< orphan*/  P_CheckPosition (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  P_RemoveMobj (TYPE_5__*) ; 
 int /*<<< orphan*/ * P_SpawnMobj (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* R_PointInSubsector (int,int) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__** bodyque ; 
 size_t bodyqueslot ; 
 size_t consoleplayer ; 
 int* finecosine ; 
 int* finesine ; 
 TYPE_4__* players ; 
 int /*<<< orphan*/  sfx_telept ; 

boolean
G_CheckSpot
( int		playernum,
  mapthing_t*	mthing ) 
{ 
    fixed_t		x;
    fixed_t		y; 
    subsector_t*	ss; 
    unsigned		an; 
    mobj_t*		mo; 
    int			i;
	
    if (!players[playernum].mo)
    {
	// first spawn of level, before corpses
	for (i=0 ; i<playernum ; i++)
	    if (players[i].mo->x == mthing->x << FRACBITS
		&& players[i].mo->y == mthing->y << FRACBITS)
		return false;	
	return true;
    }
		
    x = mthing->x << FRACBITS; 
    y = mthing->y << FRACBITS; 
	 
    if (!P_CheckPosition (players[playernum].mo, x, y) ) 
	return false; 
 
    // flush an old corpse if needed 
    if (bodyqueslot >= BODYQUESIZE) 
	P_RemoveMobj (bodyque[bodyqueslot%BODYQUESIZE]); 
    bodyque[bodyqueslot%BODYQUESIZE] = players[playernum].mo; 
    bodyqueslot++; 
	
    // spawn a teleport fog 
    ss = R_PointInSubsector (x,y); 
    an = ( ANG45 * (mthing->angle/45) ) >> ANGLETOFINESHIFT; 
 
    mo = P_SpawnMobj (x+20*finecosine[an], y+20*finesine[an] 
		      , ss->sector->floorheight 
		      , MT_TFOG); 
	 
    if (players[consoleplayer].viewz != 1) 
	S_StartSound (mo, sfx_telept);	// don't start sound on first frame 
 
    return true; 
}