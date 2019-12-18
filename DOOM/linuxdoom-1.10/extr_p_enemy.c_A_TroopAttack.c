#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  target; } ;
typedef  TYPE_1__ mobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_FaceTarget (TYPE_1__*) ; 
 int /*<<< orphan*/  MT_TROOPSHOT ; 
 scalar_t__ P_CheckMeleeRange (TYPE_1__*) ; 
 int /*<<< orphan*/  P_DamageMobj (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SpawnMissile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfx_claw ; 

void A_TroopAttack (mobj_t* actor)
{
    int		damage;
	
    if (!actor->target)
	return;
		
    A_FaceTarget (actor);
    if (P_CheckMeleeRange (actor))
    {
	S_StartSound (actor, sfx_claw);
	damage = (P_Random()%8+1)*3;
	P_DamageMobj (actor->target, actor, actor, damage);
	return;
    }

    
    // launch a missile
    P_SpawnMissile (actor, actor->target, MT_TROOPSHOT);
}