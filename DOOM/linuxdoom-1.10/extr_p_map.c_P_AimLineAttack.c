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
struct TYPE_4__ {int x; int y; int height; scalar_t__ z; } ;
typedef  TYPE_1__ mobj_t ;
typedef  int fixed_t ;
typedef  size_t angle_t ;

/* Variables and functions */
 size_t ANGLETOFINESHIFT ; 
 int FRACBITS ; 
 int FRACUNIT ; 
 int /*<<< orphan*/  PTR_AimTraverse ; 
 int PT_ADDLINES ; 
 int PT_ADDTHINGS ; 
 int /*<<< orphan*/  P_PathTraverse (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int aimslope ; 
 int attackrange ; 
 int bottomslope ; 
 int* finecosine ; 
 int* finesine ; 
 int /*<<< orphan*/ * linetarget ; 
 TYPE_1__* shootthing ; 
 scalar_t__ shootz ; 
 int topslope ; 

fixed_t
P_AimLineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance )
{
    fixed_t	x2;
    fixed_t	y2;
	
    angle >>= ANGLETOFINESHIFT;
    shootthing = t1;
    
    x2 = t1->x + (distance>>FRACBITS)*finecosine[angle];
    y2 = t1->y + (distance>>FRACBITS)*finesine[angle];
    shootz = t1->z + (t1->height>>1) + 8*FRACUNIT;

    // can't shoot outside view angles
    topslope = 100*FRACUNIT/160;	
    bottomslope = -100*FRACUNIT/160;
    
    attackrange = distance;
    linetarget = NULL;
	
    P_PathTraverse ( t1->x, t1->y,
		     x2, y2,
		     PT_ADDLINES|PT_ADDTHINGS,
		     PTR_AimTraverse );
		
    if (linetarget)
	return aimslope;

    return 0;
}