#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* line; } ;
struct TYPE_11__ {TYPE_1__ d; } ;
typedef  TYPE_2__ intercept_t ;
typedef  int boolean ;
struct TYPE_13__ {int /*<<< orphan*/  special; } ;
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_LineOpening (TYPE_6__*) ; 
 int P_PointOnLineSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  P_UseSpecialLine (TYPE_3__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ openrange ; 
 int /*<<< orphan*/  sfx_noway ; 
 TYPE_3__* usething ; 

boolean	PTR_UseTraverse (intercept_t* in)
{
    int		side;
	
    if (!in->d.line->special)
    {
	P_LineOpening (in->d.line);
	if (openrange <= 0)
	{
	    S_StartSound (usething, sfx_noway);
	    
	    // can't use through a wall
	    return false;	
	}
	// not a special line, but keep checking
	return true ;		
    }
	
    side = 0;
    if (P_PointOnLineSide (usething->x, usething->y, in->d.line) == 1)
	side = 1;
    
    //	return false;		// don't use back side
	
    P_UseSpecialLine (usething, in->d.line, side);

    // can't use for than one special line in a row
    return false;
}