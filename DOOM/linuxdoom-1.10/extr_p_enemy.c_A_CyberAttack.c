#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  target; } ;
typedef  TYPE_1__ mobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_FaceTarget (TYPE_1__*) ; 
 int /*<<< orphan*/  MT_ROCKET ; 
 int /*<<< orphan*/  P_SpawnMissile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void A_CyberAttack (mobj_t* actor)
{	
    if (!actor->target)
	return;
		
    A_FaceTarget (actor);
    P_SpawnMissile (actor, actor->target, MT_ROCKET);
}