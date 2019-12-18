#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int angle; } ;
typedef  TYPE_1__ mobj_t ;
typedef  int angle_t ;

/* Variables and functions */
 int FRACUNIT ; 
 int /*<<< orphan*/  P_AimLineAttack (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  bulletslope ; 
 int /*<<< orphan*/  linetarget ; 

void P_BulletSlope (mobj_t*	mo)
{
    angle_t	an;
    
    // see which target is to be aimed at
    an = mo->angle;
    bulletslope = P_AimLineAttack (mo, an, 16*64*FRACUNIT);

    if (!linetarget)
    {
	an += 1<<26;
	bulletslope = P_AimLineAttack (mo, an, 16*64*FRACUNIT);
	if (!linetarget)
	{
	    an -= 2<<26;
	    bulletslope = P_AimLineAttack (mo, an, 16*64*FRACUNIT);
	}
    }
}