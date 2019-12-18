#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t angle; int momz; int z; int height; scalar_t__ y; scalar_t__ x; void* momy; void* momx; TYPE_1__* info; int /*<<< orphan*/  flags; struct TYPE_7__* target; } ;
typedef  TYPE_2__ mobj_t ;
typedef  size_t angle_t ;
struct TYPE_6__ {int /*<<< orphan*/  attacksound; } ;

/* Variables and functions */
 size_t ANGLETOFINESHIFT ; 
 int /*<<< orphan*/  A_FaceTarget (TYPE_2__*) ; 
 void* FixedMul (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MF_SKULLFLY ; 
 int P_AproxDistance (scalar_t__,scalar_t__) ; 
 int SKULLSPEED ; 
 int /*<<< orphan*/  S_StartSound (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * finecosine ; 
 int /*<<< orphan*/ * finesine ; 

void A_SkullAttack (mobj_t* actor)
{
    mobj_t*		dest;
    angle_t		an;
    int			dist;

    if (!actor->target)
	return;
		
    dest = actor->target;	
    actor->flags |= MF_SKULLFLY;

    S_StartSound (actor, actor->info->attacksound);
    A_FaceTarget (actor);
    an = actor->angle >> ANGLETOFINESHIFT;
    actor->momx = FixedMul (SKULLSPEED, finecosine[an]);
    actor->momy = FixedMul (SKULLSPEED, finesine[an]);
    dist = P_AproxDistance (dest->x - actor->x, dest->y - actor->y);
    dist = dist / SKULLSPEED;
    
    if (dist < 1)
	dist = 1;
    actor->momz = (dest->z+(dest->height>>1) - actor->z) / dist;
}