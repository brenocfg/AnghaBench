#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {TYPE_3__* eUp; } ;
struct TYPE_27__ {struct TYPE_27__* Onext; int /*<<< orphan*/ * activeRegion; } ;
struct TYPE_26__ {int /*<<< orphan*/  env; TYPE_1__* event; } ;
struct TYPE_25__ {TYPE_3__* anEdge; } ;
typedef  TYPE_1__ TESSvertex ;
typedef  TYPE_2__ TESStesselator ;
typedef  TYPE_3__ TESShalfEdge ;
typedef  TYPE_4__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  AddRightEdges (TYPE_2__*,TYPE_4__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConnectLeftVertex (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ConnectRightVertex (TYPE_2__*,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  DebugEvent (TYPE_2__*) ; 
 TYPE_3__* FinishLeftRegions (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* RegionBelow (TYPE_4__*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* TopLeftRegion (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SweepEvent( TESStesselator *tess, TESSvertex *vEvent )
/*
* Does everything necessary when the sweep line crosses a vertex.
* Updates the mesh and the edge dictionary.
*/
{
	ActiveRegion *regUp, *reg;
	TESShalfEdge *e, *eTopLeft, *eBottomLeft;

	tess->event = vEvent;		/* for access in EdgeLeq() */
	DebugEvent( tess );

	/* Check if this vertex is the right endpoint of an edge that is
	* already in the dictionary.  In this case we don't need to waste
	* time searching for the location to insert new edges.
	*/
	e = vEvent->anEdge;
	while( e->activeRegion == NULL ) {
		e = e->Onext;
		if( e == vEvent->anEdge ) {
			/* All edges go right -- not incident to any processed edges */
			ConnectLeftVertex( tess, vEvent );
			return;
		}
	}

	/* Processing consists of two phases: first we "finish" all the
	* active regions where both the upper and lower edges terminate
	* at vEvent (ie. vEvent is closing off these regions).
	* We mark these faces "inside" or "outside" the polygon according
	* to their winding number, and delete the edges from the dictionary.
	* This takes care of all the left-going edges from vEvent.
	*/
	regUp = TopLeftRegion( tess, e->activeRegion );
	if (regUp == NULL) longjmp(tess->env,1);
	reg = RegionBelow( regUp );
	eTopLeft = reg->eUp;
	eBottomLeft = FinishLeftRegions( tess, reg, NULL );

	/* Next we process all the right-going edges from vEvent.  This
	* involves adding the edges to the dictionary, and creating the
	* associated "active regions" which record information about the
	* regions between adjacent dictionary edges.
	*/
	if( eBottomLeft->Onext == eTopLeft ) {
		/* No right-going edges -- add a temporary "fixable" edge */
		ConnectRightVertex( tess, regUp, eBottomLeft );
	} else {
		AddRightEdges( tess, regUp, eBottomLeft->Onext, eTopLeft, eTopLeft, TRUE );
	}
}