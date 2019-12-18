#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* sidedef; TYPE_7__* backsector; TYPE_2__* v2; TYPE_1__* v1; } ;
typedef  TYPE_4__ seg_t ;
typedef  int angle_t ;
struct TYPE_14__ {scalar_t__ ceilingheight; scalar_t__ floorheight; scalar_t__ ceilingpic; scalar_t__ floorpic; scalar_t__ lightlevel; } ;
struct TYPE_13__ {scalar_t__ floorheight; scalar_t__ ceilingheight; scalar_t__ ceilingpic; scalar_t__ floorpic; scalar_t__ lightlevel; } ;
struct TYPE_11__ {scalar_t__ midtexture; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int ANG180 ; 
 int ANG90 ; 
 int ANGLETOFINESHIFT ; 
 int /*<<< orphan*/  R_ClipPassWallSegment (int,int) ; 
 int /*<<< orphan*/  R_ClipSolidWallSegment (int,int) ; 
 int R_PointToAngle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* backsector ; 
 int clipangle ; 
 TYPE_4__* curline ; 
 TYPE_5__* frontsector ; 
 int rw_angle1 ; 
 scalar_t__ viewangle ; 
 int* viewangletox ; 

void R_AddLine (seg_t*	line)
{
    int			x1;
    int			x2;
    angle_t		angle1;
    angle_t		angle2;
    angle_t		span;
    angle_t		tspan;
    
    curline = line;

    // OPTIMIZE: quickly reject orthogonal back sides.
    angle1 = R_PointToAngle (line->v1->x, line->v1->y);
    angle2 = R_PointToAngle (line->v2->x, line->v2->y);
    
    // Clip to view edges.
    // OPTIMIZE: make constant out of 2*clipangle (FIELDOFVIEW).
    span = angle1 - angle2;
    
    // Back side? I.e. backface culling?
    if (span >= ANG180)
	return;		

    // Global angle needed by segcalc.
    rw_angle1 = angle1;
    angle1 -= viewangle;
    angle2 -= viewangle;
	
    tspan = angle1 + clipangle;
    if (tspan > 2*clipangle)
    {
	tspan -= 2*clipangle;

	// Totally off the left edge?
	if (tspan >= span)
	    return;
	
	angle1 = clipangle;
    }
    tspan = clipangle - angle2;
    if (tspan > 2*clipangle)
    {
	tspan -= 2*clipangle;

	// Totally off the left edge?
	if (tspan >= span)
	    return;	
	angle2 = -clipangle;
    }
    
    // The seg is in the view range,
    // but not necessarily visible.
    angle1 = (angle1+ANG90)>>ANGLETOFINESHIFT;
    angle2 = (angle2+ANG90)>>ANGLETOFINESHIFT;
    x1 = viewangletox[angle1];
    x2 = viewangletox[angle2];

    // Does not cross a pixel?
    if (x1 == x2)
	return;				
	
    backsector = line->backsector;

    // Single sided line?
    if (!backsector)
	goto clipsolid;		

    // Closed door.
    if (backsector->ceilingheight <= frontsector->floorheight
	|| backsector->floorheight >= frontsector->ceilingheight)
	goto clipsolid;		

    // Window.
    if (backsector->ceilingheight != frontsector->ceilingheight
	|| backsector->floorheight != frontsector->floorheight)
	goto clippass;	
		
    // Reject empty lines used for triggers
    //  and special events.
    // Identical floor and ceiling on both sides,
    // identical light levels on both sides,
    // and no middle texture.
    if (backsector->ceilingpic == frontsector->ceilingpic
	&& backsector->floorpic == frontsector->floorpic
	&& backsector->lightlevel == frontsector->lightlevel
	&& curline->sidedef->midtexture == 0)
    {
	return;
    }
    
				
  clippass:
    R_ClipPassWallSegment (x1, x2-1);	
    return;
		
  clipsolid:
    R_ClipSolidWallSegment (x1, x2-1);
}