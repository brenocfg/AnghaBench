#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nextstate; } ;
typedef  TYPE_1__ state_t ;
struct TYPE_7__ {int tics; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; TYPE_1__* state; } ;
typedef  TYPE_2__ pspdef_t ;
struct TYPE_8__ {TYPE_2__* psprites; } ;
typedef  TYPE_3__ player_t ;

/* Variables and functions */
 int NUMPSPRITES ; 
 int /*<<< orphan*/  P_SetPsprite (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 size_t ps_flash ; 
 size_t ps_weapon ; 

void P_MovePsprites (player_t* player) 
{
    int		i;
    pspdef_t*	psp;
    state_t*	state;
	
    psp = &player->psprites[0];
    for (i=0 ; i<NUMPSPRITES ; i++, psp++)
    {
	// a null state means not active
	if ( (state = psp->state) )	
	{
	    // drop tic count and possibly change state

	    // a -1 tic count never changes
	    if (psp->tics != -1)	
	    {
		psp->tics--;
		if (!psp->tics)
		    P_SetPsprite (player, i, psp->state->nextstate);
	    }				
	}
    }
    
    player->psprites[ps_flash].sx = player->psprites[ps_weapon].sx;
    player->psprites[ps_flash].sy = player->psprites[ps_weapon].sy;
}