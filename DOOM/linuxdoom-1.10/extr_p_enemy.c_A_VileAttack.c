#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int angle; TYPE_6__* target; void* y; void* x; struct TYPE_14__* tracer; } ;
typedef  TYPE_2__ mobj_t ;
struct TYPE_15__ {int momz; void* x; void* y; TYPE_1__* info; } ;
struct TYPE_13__ {int mass; } ;

/* Variables and functions */
 int ANGLETOFINESHIFT ; 
 int /*<<< orphan*/  A_FaceTarget (TYPE_2__*) ; 
 int FRACUNIT ; 
 void* FixedMul (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_CheckSight (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  P_DamageMobj (TYPE_6__*,TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  P_RadiusAttack (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * finecosine ; 
 int /*<<< orphan*/ * finesine ; 
 int /*<<< orphan*/  sfx_barexp ; 

void A_VileAttack (mobj_t* actor)
{	
    mobj_t*	fire;
    int		an;
	
    if (!actor->target)
	return;
    
    A_FaceTarget (actor);

    if (!P_CheckSight (actor, actor->target) )
	return;

    S_StartSound (actor, sfx_barexp);
    P_DamageMobj (actor->target, actor, actor, 20);
    actor->target->momz = 1000*FRACUNIT/actor->target->info->mass;
	
    an = actor->angle >> ANGLETOFINESHIFT;

    fire = actor->tracer;

    if (!fire)
	return;
		
    // move the fire between the vile and the player
    fire->x = actor->target->x - FixedMul (24*FRACUNIT, finecosine[an]);
    fire->y = actor->target->y - FixedMul (24*FRACUNIT, finesine[an]);	
    P_RadiusAttack (fire, actor, 70 );
}