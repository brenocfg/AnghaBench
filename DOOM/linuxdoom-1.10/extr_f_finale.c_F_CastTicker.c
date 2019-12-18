#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t type; int /*<<< orphan*/ * name; } ;
struct TYPE_6__ {int seesound; size_t seestate; size_t meleestate; size_t missilestate; } ;
struct TYPE_5__ {int tics; size_t nextstate; } ;

/* Variables and functions */
#define  S_BOS2_ATK2 153 
#define  S_BOSS_ATK2 152 
#define  S_BSPI_ATK2 151 
#define  S_CPOS_ATK2 150 
#define  S_CPOS_ATK3 149 
#define  S_CPOS_ATK4 148 
#define  S_CYBER_ATK2 147 
#define  S_CYBER_ATK4 146 
#define  S_CYBER_ATK6 145 
#define  S_FATT_ATK2 144 
#define  S_FATT_ATK5 143 
#define  S_FATT_ATK8 142 
#define  S_HEAD_ATK2 141 
 size_t S_NULL ; 
#define  S_PAIN_ATK3 140 
#define  S_PLAY_ATK1 139 
#define  S_POSS_ATK2 138 
#define  S_SARG_ATK2 137 
#define  S_SKEL_FIST2 136 
#define  S_SKEL_FIST4 135 
#define  S_SKEL_MISS2 134 
#define  S_SKULL_ATK2 133 
#define  S_SPID_ATK2 132 
#define  S_SPID_ATK3 131 
#define  S_SPOS_ATK2 130 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int) ; 
#define  S_TROO_ATK3 129 
#define  S_VILE_ATK2 128 
 int castattacking ; 
 int castdeath ; 
 int castframes ; 
 size_t castnum ; 
 int castonmelee ; 
 TYPE_4__* castorder ; 
 TYPE_1__* caststate ; 
 scalar_t__ casttics ; 
 TYPE_2__* mobjinfo ; 
 int sfx_claw ; 
 int sfx_dshtgn ; 
 int sfx_firsht ; 
 int sfx_pistol ; 
 int sfx_plasma ; 
 int sfx_rlaunc ; 
 int sfx_sgtatk ; 
 int sfx_shotgn ; 
 int sfx_skeatk ; 
 int sfx_skepch ; 
 int sfx_skeswg ; 
 int sfx_sklatk ; 
 int sfx_vilatk ; 
 TYPE_1__* states ; 

void F_CastTicker (void)
{
    int		st;
    int		sfx;
	
    if (--casttics > 0)
	return;			// not time to change state yet
		
    if (caststate->tics == -1 || caststate->nextstate == S_NULL)
    {
	// switch from deathstate to next monster
	castnum++;
	castdeath = false;
	if (castorder[castnum].name == NULL)
	    castnum = 0;
	if (mobjinfo[castorder[castnum].type].seesound)
	    S_StartSound (NULL, mobjinfo[castorder[castnum].type].seesound);
	caststate = &states[mobjinfo[castorder[castnum].type].seestate];
	castframes = 0;
    }
    else
    {
	// just advance to next state in animation
	if (caststate == &states[S_PLAY_ATK1])
	    goto stopattack;	// Oh, gross hack!
	st = caststate->nextstate;
	caststate = &states[st];
	castframes++;
	
	// sound hacks....
	switch (st)
	{
	  case S_PLAY_ATK1:	sfx = sfx_dshtgn; break;
	  case S_POSS_ATK2:	sfx = sfx_pistol; break;
	  case S_SPOS_ATK2:	sfx = sfx_shotgn; break;
	  case S_VILE_ATK2:	sfx = sfx_vilatk; break;
	  case S_SKEL_FIST2:	sfx = sfx_skeswg; break;
	  case S_SKEL_FIST4:	sfx = sfx_skepch; break;
	  case S_SKEL_MISS2:	sfx = sfx_skeatk; break;
	  case S_FATT_ATK8:
	  case S_FATT_ATK5:
	  case S_FATT_ATK2:	sfx = sfx_firsht; break;
	  case S_CPOS_ATK2:
	  case S_CPOS_ATK3:
	  case S_CPOS_ATK4:	sfx = sfx_shotgn; break;
	  case S_TROO_ATK3:	sfx = sfx_claw; break;
	  case S_SARG_ATK2:	sfx = sfx_sgtatk; break;
	  case S_BOSS_ATK2:
	  case S_BOS2_ATK2:
	  case S_HEAD_ATK2:	sfx = sfx_firsht; break;
	  case S_SKULL_ATK2:	sfx = sfx_sklatk; break;
	  case S_SPID_ATK2:
	  case S_SPID_ATK3:	sfx = sfx_shotgn; break;
	  case S_BSPI_ATK2:	sfx = sfx_plasma; break;
	  case S_CYBER_ATK2:
	  case S_CYBER_ATK4:
	  case S_CYBER_ATK6:	sfx = sfx_rlaunc; break;
	  case S_PAIN_ATK3:	sfx = sfx_sklatk; break;
	  default: sfx = 0; break;
	}
		
	if (sfx)
	    S_StartSound (NULL, sfx);
    }
	
    if (castframes == 12)
    {
	// go into attack frame
	castattacking = true;
	if (castonmelee)
	    caststate=&states[mobjinfo[castorder[castnum].type].meleestate];
	else
	    caststate=&states[mobjinfo[castorder[castnum].type].missilestate];
	castonmelee ^= 1;
	if (caststate == &states[S_NULL])
	{
	    if (castonmelee)
		caststate=
		    &states[mobjinfo[castorder[castnum].type].meleestate];
	    else
		caststate=
		    &states[mobjinfo[castorder[castnum].type].missilestate];
	}
    }
	
    if (castattacking)
    {
	if (castframes == 24
	    ||	caststate == &states[mobjinfo[castorder[castnum].type].seestate] )
	{
	  stopattack:
	    castattacking = false;
	    castframes = 0;
	    caststate = &states[mobjinfo[castorder[castnum].type].seestate];
	}
    }
	
    casttics = caststate->tics;
    if (casttics == -1)
	casttics = 15;
}