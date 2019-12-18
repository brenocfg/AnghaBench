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
struct TYPE_6__ {scalar_t__ type; TYPE_1__* info; } ;
typedef  TYPE_2__ mobj_t ;
struct TYPE_5__ {int deathsound; } ;

/* Variables and functions */
 scalar_t__ MT_CYBORG ; 
 scalar_t__ MT_SPIDER ; 
 int P_Random () ; 
 int /*<<< orphan*/  S_StartSound (TYPE_2__*,int) ; 
#define  sfx_bgdth1 132 
#define  sfx_bgdth2 131 
#define  sfx_podth1 130 
#define  sfx_podth2 129 
#define  sfx_podth3 128 

void A_Scream (mobj_t* actor)
{
    int		sound;
	
    switch (actor->info->deathsound)
    {
      case 0:
	return;
		
      case sfx_podth1:
      case sfx_podth2:
      case sfx_podth3:
	sound = sfx_podth1 + P_Random ()%3;
	break;
		
      case sfx_bgdth1:
      case sfx_bgdth2:
	sound = sfx_bgdth1 + P_Random ()%2;
	break;
	
      default:
	sound = actor->info->deathsound;
	break;
    }

    // Check for bosses.
    if (actor->type==MT_SPIDER
	|| actor->type == MT_CYBORG)
    {
	// full volume
	S_StartSound (NULL, sound);
    }
    else
	S_StartSound (actor, sound);
}