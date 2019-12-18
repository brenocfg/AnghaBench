#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x; int y; int momz; int tics; } ;
typedef  TYPE_1__ mobj_t ;

/* Variables and functions */
 int FRACUNIT ; 
 int /*<<< orphan*/  MT_ROCKET ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* P_SpawnMobj (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_BRAINEXPLODE1 ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfx_bosdth ; 

void A_BrainScream (mobj_t*	mo)
{
    int		x;
    int		y;
    int		z;
    mobj_t*	th;
	
    for (x=mo->x - 196*FRACUNIT ; x< mo->x + 320*FRACUNIT ; x+= FRACUNIT*8)
    {
	y = mo->y - 320*FRACUNIT;
	z = 128 + P_Random()*2*FRACUNIT;
	th = P_SpawnMobj (x,y,z, MT_ROCKET);
	th->momz = P_Random()*512;

	P_SetMobjState (th, S_BRAINEXPLODE1);

	th->tics -= P_Random()&7;
	if (th->tics < 1)
	    th->tics = 1;
    }
	
    S_StartSound (NULL,sfx_bosdth);
}