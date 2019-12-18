#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* mo; } ;
typedef  TYPE_1__ player_t ;
typedef  scalar_t__ fixed_t ;
struct TYPE_5__ {int angle; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int ANGLETOFINESHIFT ; 
 int FRACBITS ; 
 int /*<<< orphan*/  PTR_UseTraverse ; 
 int /*<<< orphan*/  PT_ADDLINES ; 
 int /*<<< orphan*/  P_PathTraverse (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USERANGE ; 
 int* finecosine ; 
 int* finesine ; 
 TYPE_2__* usething ; 

void P_UseLines (player_t*	player) 
{
    int		angle;
    fixed_t	x1;
    fixed_t	y1;
    fixed_t	x2;
    fixed_t	y2;
	
    usething = player->mo;
		
    angle = player->mo->angle >> ANGLETOFINESHIFT;

    x1 = player->mo->x;
    y1 = player->mo->y;
    x2 = x1 + (USERANGE>>FRACBITS)*finecosine[angle];
    y2 = y1 + (USERANGE>>FRACBITS)*finesine[angle];
	
    P_PathTraverse ( x1, y1, x2, y2, PT_ADDLINES, PTR_UseTraverse );
}