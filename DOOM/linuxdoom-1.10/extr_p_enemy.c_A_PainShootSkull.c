#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ acp1; } ;
struct TYPE_16__ {struct TYPE_16__* next; TYPE_1__ function; } ;
typedef  TYPE_3__ thinker_t ;
struct TYPE_17__ {size_t type; int /*<<< orphan*/  target; scalar_t__ y; scalar_t__ x; scalar_t__ z; TYPE_2__* info; } ;
typedef  TYPE_4__ mobj_t ;
typedef  scalar_t__ fixed_t ;
typedef  size_t angle_t ;
typedef  scalar_t__ actionf_p1 ;
struct TYPE_18__ {int radius; } ;
struct TYPE_15__ {int radius; } ;

/* Variables and functions */
 size_t ANGLETOFINESHIFT ; 
 int /*<<< orphan*/  A_SkullAttack (TYPE_4__*) ; 
 int FRACUNIT ; 
 scalar_t__ FixedMul (int,int /*<<< orphan*/ ) ; 
 size_t MT_SKULL ; 
 int /*<<< orphan*/  P_DamageMobj (TYPE_4__*,TYPE_4__*,TYPE_4__*,int) ; 
 scalar_t__ P_MobjThinker ; 
 TYPE_4__* P_SpawnMobj (scalar_t__,scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  P_TryMove (TYPE_4__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * finecosine ; 
 int /*<<< orphan*/ * finesine ; 
 TYPE_6__* mobjinfo ; 
 TYPE_3__ thinkercap ; 

void
A_PainShootSkull
( mobj_t*	actor,
  angle_t	angle )
{
    fixed_t	x;
    fixed_t	y;
    fixed_t	z;
    
    mobj_t*	newmobj;
    angle_t	an;
    int		prestep;
    int		count;
    thinker_t*	currentthinker;

    // count total number of skull currently on the level
    count = 0;

    currentthinker = thinkercap.next;
    while (currentthinker != &thinkercap)
    {
	if (   (currentthinker->function.acp1 == (actionf_p1)P_MobjThinker)
	    && ((mobj_t *)currentthinker)->type == MT_SKULL)
	    count++;
	currentthinker = currentthinker->next;
    }

    // if there are allready 20 skulls on the level,
    // don't spit another one
    if (count > 20)
	return;


    // okay, there's playe for another one
    an = angle >> ANGLETOFINESHIFT;
    
    prestep =
	4*FRACUNIT
	+ 3*(actor->info->radius + mobjinfo[MT_SKULL].radius)/2;
    
    x = actor->x + FixedMul (prestep, finecosine[an]);
    y = actor->y + FixedMul (prestep, finesine[an]);
    z = actor->z + 8*FRACUNIT;
		
    newmobj = P_SpawnMobj (x , y, z, MT_SKULL);

    // Check for movements.
    if (!P_TryMove (newmobj, newmobj->x, newmobj->y))
    {
	// kill it immediately
	P_DamageMobj (newmobj,actor,actor,10000);	
	return;
    }
		
    newmobj->target = actor->target;
    A_SkullAttack (newmobj);
}