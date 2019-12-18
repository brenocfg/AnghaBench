#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* bbox; int flags; scalar_t__ special; int /*<<< orphan*/  backsector; } ;
typedef  TYPE_1__ line_t ;
typedef  int boolean ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  player; } ;

/* Variables and functions */
 size_t BOXBOTTOM ; 
 size_t BOXLEFT ; 
 size_t BOXRIGHT ; 
 size_t BOXTOP ; 
 int MF_MISSILE ; 
 int ML_BLOCKING ; 
 int ML_BLOCKMONSTERS ; 
 int P_BoxOnLineSide (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  P_LineOpening (TYPE_1__*) ; 
 TYPE_1__* ceilingline ; 
 scalar_t__ lowfloor ; 
 size_t numspechit ; 
 scalar_t__ openbottom ; 
 scalar_t__ opentop ; 
 TYPE_1__** spechit ; 
 scalar_t__* tmbbox ; 
 scalar_t__ tmceilingz ; 
 scalar_t__ tmdropoffz ; 
 scalar_t__ tmfloorz ; 
 TYPE_2__* tmthing ; 

boolean PIT_CheckLine (line_t* ld)
{
    if (tmbbox[BOXRIGHT] <= ld->bbox[BOXLEFT]
	|| tmbbox[BOXLEFT] >= ld->bbox[BOXRIGHT]
	|| tmbbox[BOXTOP] <= ld->bbox[BOXBOTTOM]
	|| tmbbox[BOXBOTTOM] >= ld->bbox[BOXTOP] )
	return true;

    if (P_BoxOnLineSide (tmbbox, ld) != -1)
	return true;
		
    // A line has been hit
    
    // The moving thing's destination position will cross
    // the given line.
    // If this should not be allowed, return false.
    // If the line is special, keep track of it
    // to process later if the move is proven ok.
    // NOTE: specials are NOT sorted by order,
    // so two special lines that are only 8 pixels apart
    // could be crossed in either order.
    
    if (!ld->backsector)
	return false;		// one sided line
		
    if (!(tmthing->flags & MF_MISSILE) )
    {
	if ( ld->flags & ML_BLOCKING )
	    return false;	// explicitly blocking everything

	if ( !tmthing->player && ld->flags & ML_BLOCKMONSTERS )
	    return false;	// block monsters only
    }

    // set openrange, opentop, openbottom
    P_LineOpening (ld);	
	
    // adjust floor / ceiling heights
    if (opentop < tmceilingz)
    {
	tmceilingz = opentop;
	ceilingline = ld;
    }

    if (openbottom > tmfloorz)
	tmfloorz = openbottom;	

    if (lowfloor < tmdropoffz)
	tmdropoffz = lowfloor;
		
    // if contacted a special line, add it to the list
    if (ld->special)
    {
	spechit[numspechit] = ld;
	numspechit++;
    }

    return true;
}