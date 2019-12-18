#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_1__ event_t ;
typedef  int boolean ;
struct TYPE_10__ {size_t type; } ;
struct TYPE_9__ {size_t deathstate; scalar_t__ deathsound; } ;
struct TYPE_8__ {int /*<<< orphan*/  tics; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,scalar_t__) ; 
 int castattacking ; 
 int castdeath ; 
 scalar_t__ castframes ; 
 size_t castnum ; 
 TYPE_5__* castorder ; 
 TYPE_2__* caststate ; 
 int /*<<< orphan*/  casttics ; 
 scalar_t__ ev_keydown ; 
 TYPE_3__* mobjinfo ; 
 TYPE_2__* states ; 

boolean F_CastResponder (event_t* ev)
{
    if (ev->type != ev_keydown)
	return false;
		
    if (castdeath)
	return true;			// already in dying frames
		
    // go into death frame
    castdeath = true;
    caststate = &states[mobjinfo[castorder[castnum].type].deathstate];
    casttics = caststate->tics;
    castframes = 0;
    castattacking = false;
    if (mobjinfo[castorder[castnum].type].deathsound)
	S_StartSound (NULL, mobjinfo[castorder[castnum].type].deathsound);
	
    return true;
}