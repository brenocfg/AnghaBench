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
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* info; TYPE_5__* target; } ;
typedef  TYPE_2__ mobj_t ;
struct TYPE_10__ {scalar_t__ health; } ;
struct TYPE_8__ {int /*<<< orphan*/  seestate; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_FaceTarget (TYPE_2__*) ; 
 int /*<<< orphan*/  P_CheckSight (TYPE_2__*,TYPE_5__*) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SetMobjState (TYPE_2__*,int /*<<< orphan*/ ) ; 

void A_CPosRefire (mobj_t* actor)
{	
    // keep firing unless target got out of sight
    A_FaceTarget (actor);

    if (P_Random () < 40)
	return;

    if (!actor->target
	|| actor->target->health <= 0
	|| !P_CheckSight (actor, actor->target) )
    {
	P_SetMobjState (actor, actor->info->seestate);
    }
}