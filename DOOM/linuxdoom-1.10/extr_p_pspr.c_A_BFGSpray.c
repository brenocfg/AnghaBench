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
struct TYPE_5__ {int angle; int /*<<< orphan*/  target; } ;
typedef  TYPE_1__ mobj_t ;
typedef  int angle_t ;
struct TYPE_6__ {int height; scalar_t__ z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int ANG90 ; 
 int FRACUNIT ; 
 int /*<<< orphan*/  MT_EXTRABFG ; 
 int /*<<< orphan*/  P_AimLineAttack (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  P_DamageMobj (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int P_Random () ; 
 int /*<<< orphan*/  P_SpawnMobj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* linetarget ; 

void A_BFGSpray (mobj_t* mo) 
{
    int			i;
    int			j;
    int			damage;
    angle_t		an;
	
    // offset angles from its attack angle
    for (i=0 ; i<40 ; i++)
    {
	an = mo->angle - ANG90/2 + ANG90/40*i;

	// mo->target is the originator (player)
	//  of the missile
	P_AimLineAttack (mo->target, an, 16*64*FRACUNIT);

	if (!linetarget)
	    continue;

	P_SpawnMobj (linetarget->x,
		     linetarget->y,
		     linetarget->z + (linetarget->height>>2),
		     MT_EXTRABFG);
	
	damage = 0;
	for (j=0;j<15;j++)
	    damage += (P_Random()&7) + 1;

	P_DamageMobj (linetarget, mo->target,mo->target, damage);
    }
}