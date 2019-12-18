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
struct TYPE_5__ {scalar_t__ slopetype; void* dy; void* dx; } ;
typedef  TYPE_1__ line_t ;
typedef  void* fixed_t ;
typedef  size_t angle_t ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 size_t ANG180 ; 
 size_t ANGLETOFINESHIFT ; 
 void* FixedMul (void*,int /*<<< orphan*/ ) ; 
 void* P_AproxDistance (void*,void*) ; 
 int P_PointOnLineSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t R_PointToAngle2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ ST_HORIZONTAL ; 
 scalar_t__ ST_VERTICAL ; 
 int /*<<< orphan*/ * finecosine ; 
 int /*<<< orphan*/ * finesine ; 
 TYPE_2__* slidemo ; 
 void* tmxmove ; 
 void* tmymove ; 

void P_HitSlideLine (line_t* ld)
{
    int			side;

    angle_t		lineangle;
    angle_t		moveangle;
    angle_t		deltaangle;
    
    fixed_t		movelen;
    fixed_t		newlen;
	
	
    if (ld->slopetype == ST_HORIZONTAL)
    {
	tmymove = 0;
	return;
    }
    
    if (ld->slopetype == ST_VERTICAL)
    {
	tmxmove = 0;
	return;
    }
	
    side = P_PointOnLineSide (slidemo->x, slidemo->y, ld);
	
    lineangle = R_PointToAngle2 (0,0, ld->dx, ld->dy);

    if (side == 1)
	lineangle += ANG180;

    moveangle = R_PointToAngle2 (0,0, tmxmove, tmymove);
    deltaangle = moveangle-lineangle;

    if (deltaangle > ANG180)
	deltaangle += ANG180;
    //	I_Error ("SlideLine: ang>ANG180");

    lineangle >>= ANGLETOFINESHIFT;
    deltaangle >>= ANGLETOFINESHIFT;
	
    movelen = P_AproxDistance (tmxmove, tmymove);
    newlen = FixedMul (movelen, finecosine[deltaangle]);

    tmxmove = FixedMul (newlen, finecosine[lineangle]);	
    tmymove = FixedMul (newlen, finesine[lineangle]);	
}