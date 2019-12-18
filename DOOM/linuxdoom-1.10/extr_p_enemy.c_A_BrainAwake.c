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
struct TYPE_7__ {scalar_t__ acp1; } ;
struct TYPE_8__ {TYPE_1__ function; struct TYPE_8__* next; } ;
typedef  TYPE_2__ thinker_t ;
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_3__ mobj_t ;
typedef  scalar_t__ actionf_p1 ;

/* Variables and functions */
 scalar_t__ MT_BOSSTARGET ; 
 scalar_t__ P_MobjThinker ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ braintargeton ; 
 TYPE_3__** braintargets ; 
 size_t numbraintargets ; 
 int /*<<< orphan*/  sfx_bossit ; 
 TYPE_2__ thinkercap ; 

void A_BrainAwake (mobj_t* mo)
{
    thinker_t*	thinker;
    mobj_t*	m;
	
    // find all the target spots
    numbraintargets = 0;
    braintargeton = 0;
	
    thinker = thinkercap.next;
    for (thinker = thinkercap.next ;
	 thinker != &thinkercap ;
	 thinker = thinker->next)
    {
	if (thinker->function.acp1 != (actionf_p1)P_MobjThinker)
	    continue;	// not a mobj

	m = (mobj_t *)thinker;

	if (m->type == MT_BOSSTARGET )
	{
	    braintargets[numbraintargets] = m;
	    numbraintargets++;
	}
    }
	
    S_StartSound (NULL,sfx_bossit);
}