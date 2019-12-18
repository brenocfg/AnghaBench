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
struct TYPE_7__ {size_t type; } ;
struct TYPE_6__ {size_t seestate; } ;
struct TYPE_5__ {int /*<<< orphan*/  tics; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ChangeMusic (int /*<<< orphan*/ ,int) ; 
 int castattacking ; 
 int castdeath ; 
 scalar_t__ castframes ; 
 size_t castnum ; 
 scalar_t__ castonmelee ; 
 TYPE_4__* castorder ; 
 TYPE_1__* caststate ; 
 int /*<<< orphan*/  casttics ; 
 int finalestage ; 
 TYPE_2__* mobjinfo ; 
 int /*<<< orphan*/  mus_evil ; 
 TYPE_1__* states ; 
 int wipegamestate ; 

void F_StartCast (void)
{
    wipegamestate = -1;		// force a screen wipe
    castnum = 0;
    caststate = &states[mobjinfo[castorder[castnum].type].seestate];
    casttics = caststate->tics;
    castdeath = false;
    finalestage = 2;	
    castframes = 0;
    castonmelee = 0;
    castattacking = false;
    S_ChangeMusic(mus_evil, true);
}