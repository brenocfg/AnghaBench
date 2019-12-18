#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; } ;
typedef  TYPE_2__ line_t ;
struct TYPE_10__ {TYPE_2__* line; } ;
struct TYPE_12__ {scalar_t__ frac; TYPE_1__ d; int /*<<< orphan*/  isaline; } ;
typedef  TYPE_3__ intercept_t ;
typedef  int boolean ;
struct TYPE_13__ {scalar_t__ height; scalar_t__ z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int FRACUNIT ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int ML_TWOSIDED ; 
 int /*<<< orphan*/  P_LineOpening (TYPE_2__*) ; 
 scalar_t__ P_PointOnLineSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ bestslidefrac ; 
 TYPE_2__* bestslideline ; 
 int openbottom ; 
 scalar_t__ openrange ; 
 scalar_t__ opentop ; 
 scalar_t__ secondslidefrac ; 
 TYPE_2__* secondslideline ; 
 TYPE_4__* slidemo ; 

boolean PTR_SlideTraverse (intercept_t* in)
{
    line_t*	li;
	
    if (!in->isaline)
	I_Error ("PTR_SlideTraverse: not a line?");
		
    li = in->d.line;
    
    if ( ! (li->flags & ML_TWOSIDED) )
    {
	if (P_PointOnLineSide (slidemo->x, slidemo->y, li))
	{
	    // don't hit the back side
	    return true;		
	}
	goto isblocking;
    }

    // set openrange, opentop, openbottom
    P_LineOpening (li);
    
    if (openrange < slidemo->height)
	goto isblocking;		// doesn't fit
		
    if (opentop - slidemo->z < slidemo->height)
	goto isblocking;		// mobj is too high

    if (openbottom - slidemo->z > 24*FRACUNIT )
	goto isblocking;		// too big a step up

    // this line doesn't block movement
    return true;		
	
    // the line does block movement,
    // see if it is closer than best so far
  isblocking:		
    if (in->frac < bestslidefrac)
    {
	secondslidefrac = bestslidefrac;
	secondslideline = bestslideline;
	bestslidefrac = in->frac;
	bestslideline = li;
    }
	
    return false;	// stop
}