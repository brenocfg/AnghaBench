#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fixed_t ;
struct TYPE_3__ {int last; int first; } ;
typedef  TYPE_1__ cliprange_t ;
typedef  int boolean ;
typedef  int angle_t ;

/* Variables and functions */
 int ANG180 ; 
 int ANG90 ; 
 int ANGLETOFINESHIFT ; 
 size_t BOXBOTTOM ; 
 size_t BOXLEFT ; 
 size_t BOXRIGHT ; 
 size_t BOXTOP ; 
 int R_PointToAngle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t** checkcoord ; 
 int clipangle ; 
 TYPE_1__* solidsegs ; 
 int viewangle ; 
 int* viewangletox ; 
 int /*<<< orphan*/  viewx ; 
 int /*<<< orphan*/  viewy ; 

boolean R_CheckBBox (fixed_t*	bspcoord)
{
    int			boxx;
    int			boxy;
    int			boxpos;

    fixed_t		x1;
    fixed_t		y1;
    fixed_t		x2;
    fixed_t		y2;
    
    angle_t		angle1;
    angle_t		angle2;
    angle_t		span;
    angle_t		tspan;
    
    cliprange_t*	start;

    int			sx1;
    int			sx2;
    
    // Find the corners of the box
    // that define the edges from current viewpoint.
    if (viewx <= bspcoord[BOXLEFT])
	boxx = 0;
    else if (viewx < bspcoord[BOXRIGHT])
	boxx = 1;
    else
	boxx = 2;
		
    if (viewy >= bspcoord[BOXTOP])
	boxy = 0;
    else if (viewy > bspcoord[BOXBOTTOM])
	boxy = 1;
    else
	boxy = 2;
		
    boxpos = (boxy<<2)+boxx;
    if (boxpos == 5)
	return true;
	
    x1 = bspcoord[checkcoord[boxpos][0]];
    y1 = bspcoord[checkcoord[boxpos][1]];
    x2 = bspcoord[checkcoord[boxpos][2]];
    y2 = bspcoord[checkcoord[boxpos][3]];
    
    // check clip list for an open space
    angle1 = R_PointToAngle (x1, y1) - viewangle;
    angle2 = R_PointToAngle (x2, y2) - viewangle;
	
    span = angle1 - angle2;

    // Sitting on a line?
    if (span >= ANG180)
	return true;
    
    tspan = angle1 + clipangle;

    if (tspan > 2*clipangle)
    {
	tspan -= 2*clipangle;

	// Totally off the left edge?
	if (tspan >= span)
	    return false;	

	angle1 = clipangle;
    }
    tspan = clipangle - angle2;
    if (tspan > 2*clipangle)
    {
	tspan -= 2*clipangle;

	// Totally off the left edge?
	if (tspan >= span)
	    return false;
	
	angle2 = -clipangle;
    }


    // Find the first clippost
    //  that touches the source post
    //  (adjacent pixels are touching).
    angle1 = (angle1+ANG90)>>ANGLETOFINESHIFT;
    angle2 = (angle2+ANG90)>>ANGLETOFINESHIFT;
    sx1 = viewangletox[angle1];
    sx2 = viewangletox[angle2];

    // Does not cross a pixel.
    if (sx1 == sx2)
	return false;			
    sx2--;
	
    start = solidsegs;
    while (start->last < sx2)
	start++;
    
    if (sx1 >= start->first
	&& sx2 <= start->last)
    {
	// The clippost contains the new span.
	return false;
    }

    return true;
}