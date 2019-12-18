#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ x; scalar_t__ radius; scalar_t__ y; } ;
typedef  TYPE_2__ mobj_t ;
typedef  scalar_t__ fixed_t ;
struct TYPE_12__ {scalar_t__ dy; scalar_t__ dx; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ divline_t ;
typedef  int boolean ;
struct TYPE_10__ {TYPE_2__* thing; } ;
struct TYPE_14__ {int isaline; TYPE_1__ d; scalar_t__ frac; } ;
struct TYPE_13__ {int dx; int dy; } ;

/* Variables and functions */
 scalar_t__ P_InterceptVector (TYPE_4__*,TYPE_3__*) ; 
 int P_PointOnDivlineSide (scalar_t__,scalar_t__,TYPE_4__*) ; 
 TYPE_5__* intercept_p ; 
 TYPE_4__ trace ; 

boolean PIT_AddThingIntercepts (mobj_t* thing)
{
    fixed_t		x1;
    fixed_t		y1;
    fixed_t		x2;
    fixed_t		y2;
    
    int			s1;
    int			s2;
    
    boolean		tracepositive;

    divline_t		dl;
    
    fixed_t		frac;
	
    tracepositive = (trace.dx ^ trace.dy)>0;
		
    // check a corner to corner crossection for hit
    if (tracepositive)
    {
	x1 = thing->x - thing->radius;
	y1 = thing->y + thing->radius;
		
	x2 = thing->x + thing->radius;
	y2 = thing->y - thing->radius;			
    }
    else
    {
	x1 = thing->x - thing->radius;
	y1 = thing->y - thing->radius;
		
	x2 = thing->x + thing->radius;
	y2 = thing->y + thing->radius;			
    }
    
    s1 = P_PointOnDivlineSide (x1, y1, &trace);
    s2 = P_PointOnDivlineSide (x2, y2, &trace);

    if (s1 == s2)
	return true;		// line isn't crossed
	
    dl.x = x1;
    dl.y = y1;
    dl.dx = x2-x1;
    dl.dy = y2-y1;
    
    frac = P_InterceptVector (&trace, &dl);

    if (frac < 0)
	return true;		// behind source

    intercept_p->frac = frac;
    intercept_p->isaline = false;
    intercept_p->d.thing = thing;
    intercept_p++;

    return true;		// keep going
}