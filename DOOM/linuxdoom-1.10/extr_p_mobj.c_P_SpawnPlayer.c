#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ playerstate; int* cards; int /*<<< orphan*/  viewheight; scalar_t__ fixedcolormap; scalar_t__ extralight; scalar_t__ bonuscount; scalar_t__ damagecount; int /*<<< orphan*/ * message; scalar_t__ refire; TYPE_2__* mo; int /*<<< orphan*/  health; } ;
typedef  TYPE_1__ player_t ;
struct TYPE_9__ {int flags; int angle; int /*<<< orphan*/  health; TYPE_1__* player; } ;
typedef  TYPE_2__ mobj_t ;
struct TYPE_10__ {int type; int x; int y; int angle; } ;
typedef  TYPE_3__ mapthing_t ;
typedef  int fixed_t ;

/* Variables and functions */
 int ANG45 ; 
 int FRACBITS ; 
 int /*<<< orphan*/  G_PlayerReborn (int) ; 
 int /*<<< orphan*/  HU_Start () ; 
 int MF_TRANSSHIFT ; 
 int /*<<< orphan*/  MT_PLAYER ; 
 int NUMCARDS ; 
 int ONFLOORZ ; 
 scalar_t__ PST_LIVE ; 
 scalar_t__ PST_REBORN ; 
 int /*<<< orphan*/  P_SetupPsprites (TYPE_1__*) ; 
 TYPE_2__* P_SpawnMobj (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_Start () ; 
 int /*<<< orphan*/  VIEWHEIGHT ; 
 int consoleplayer ; 
 scalar_t__ deathmatch ; 
 int /*<<< orphan*/ * playeringame ; 
 TYPE_1__* players ; 

void P_SpawnPlayer (mapthing_t* mthing)
{
    player_t*		p;
    fixed_t		x;
    fixed_t		y;
    fixed_t		z;

    mobj_t*		mobj;

    int			i;

    // not playing?
    if (!playeringame[mthing->type-1])
	return;					
		
    p = &players[mthing->type-1];

    if (p->playerstate == PST_REBORN)
	G_PlayerReborn (mthing->type-1);

    x 		= mthing->x << FRACBITS;
    y 		= mthing->y << FRACBITS;
    z		= ONFLOORZ;
    mobj	= P_SpawnMobj (x,y,z, MT_PLAYER);

    // set color translations for player sprites
    if (mthing->type > 1)		
	mobj->flags |= (mthing->type-1)<<MF_TRANSSHIFT;
		
    mobj->angle	= ANG45 * (mthing->angle/45);
    mobj->player = p;
    mobj->health = p->health;

    p->mo = mobj;
    p->playerstate = PST_LIVE;	
    p->refire = 0;
    p->message = NULL;
    p->damagecount = 0;
    p->bonuscount = 0;
    p->extralight = 0;
    p->fixedcolormap = 0;
    p->viewheight = VIEWHEIGHT;

    // setup gun psprite
    P_SetupPsprites (p);
    
    // give all cards in death match mode
    if (deathmatch)
	for (i=0 ; i<NUMCARDS ; i++)
	    p->cards[i] = true;
			
    if (mthing->type-1 == consoleplayer)
    {
	// wake up the status bar
	ST_Start ();
	// wake up the heads up text
	HU_Start ();		
    }
}