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
struct TYPE_4__ {int* children; int /*<<< orphan*/ * bbox; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int NF_SUBSECTOR ; 
 scalar_t__ R_CheckBBox (int /*<<< orphan*/ ) ; 
 int R_PointOnSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  R_Subsector (int) ; 
 TYPE_1__* nodes ; 
 int /*<<< orphan*/  viewx ; 
 int /*<<< orphan*/  viewy ; 

void R_RenderBSPNode (int bspnum)
{
    node_t*	bsp;
    int		side;

    // Found a subsector?
    if (bspnum & NF_SUBSECTOR)
    {
	if (bspnum == -1)			
	    R_Subsector (0);
	else
	    R_Subsector (bspnum&(~NF_SUBSECTOR));
	return;
    }
		
    bsp = &nodes[bspnum];
    
    // Decide which side the view point is on.
    side = R_PointOnSide (viewx, viewy, bsp);

    // Recursively divide front space.
    R_RenderBSPNode (bsp->children[side]); 

    // Possibly divide back space.
    if (R_CheckBBox (bsp->bbox[side^1]))	
	R_RenderBSPNode (bsp->children[side^1]);
}