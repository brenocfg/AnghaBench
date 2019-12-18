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
struct TYPE_28__ {scalar_t__ windingNumber; void* dirty; int /*<<< orphan*/  inside; TYPE_1__* eUp; } ;
struct TYPE_27__ {scalar_t__ Org; scalar_t__ winding; int /*<<< orphan*/  Oprev; struct TYPE_27__* Onext; int /*<<< orphan*/  Sym; int /*<<< orphan*/  Dst; } ;
struct TYPE_26__ {int /*<<< orphan*/  env; int /*<<< orphan*/  mesh; } ;
struct TYPE_25__ {TYPE_3__* Sym; TYPE_3__* Rprev; } ;
typedef  TYPE_2__ TESStesselator ;
typedef  TYPE_3__ TESShalfEdge ;
typedef  TYPE_4__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  AddRegionBelow (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddWinding (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ CheckForRightSplice (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  DeleteRegion (TYPE_2__*,TYPE_4__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  IsWindingInside (TYPE_2__*,scalar_t__) ; 
 TYPE_4__* RegionBelow (TYPE_4__*) ; 
 void* TRUE ; 
 int VertLeq (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalkDirtyRegions (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tessMeshDelete (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  tessMeshSplice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void AddRightEdges( TESStesselator *tess, ActiveRegion *regUp,
						  TESShalfEdge *eFirst, TESShalfEdge *eLast, TESShalfEdge *eTopLeft,
						  int cleanUp )
/*
* Purpose: insert right-going edges into the edge dictionary, and update
* winding numbers and mesh connectivity appropriately.  All right-going
* edges share a common origin vOrg.  Edges are inserted CCW starting at
* eFirst; the last edge inserted is eLast->Oprev.  If vOrg has any
* left-going edges already processed, then eTopLeft must be the edge
* such that an imaginary upward vertical segment from vOrg would be
* contained between eTopLeft->Oprev and eTopLeft; otherwise eTopLeft
* should be NULL.
*/
{
	ActiveRegion *reg, *regPrev;
	TESShalfEdge *e, *ePrev;
	int firstTime = TRUE;

	/* Insert the new right-going edges in the dictionary */
	e = eFirst;
	do {
		assert( VertLeq( e->Org, e->Dst ));
		AddRegionBelow( tess, regUp, e->Sym );
		e = e->Onext;
	} while ( e != eLast );

	/* Walk *all* right-going edges from e->Org, in the dictionary order,
	* updating the winding numbers of each region, and re-linking the mesh
	* edges to match the dictionary ordering (if necessary).
	*/
	if( eTopLeft == NULL ) {
		eTopLeft = RegionBelow( regUp )->eUp->Rprev;
	}
	regPrev = regUp;
	ePrev = eTopLeft;
	for( ;; ) {
		reg = RegionBelow( regPrev );
		e = reg->eUp->Sym;
		if( e->Org != ePrev->Org ) break;

		if( e->Onext != ePrev ) {
			/* Unlink e from its current position, and relink below ePrev */
			if ( !tessMeshSplice( tess->mesh, e->Oprev, e ) ) longjmp(tess->env,1);
			if ( !tessMeshSplice( tess->mesh, ePrev->Oprev, e ) ) longjmp(tess->env,1);
		}
		/* Compute the winding number and "inside" flag for the new regions */
		reg->windingNumber = regPrev->windingNumber - e->winding;
		reg->inside = IsWindingInside( tess, reg->windingNumber );

		/* Check for two outgoing edges with same slope -- process these
		* before any intersection tests (see example in tessComputeInterior).
		*/
		regPrev->dirty = TRUE;
		if( ! firstTime && CheckForRightSplice( tess, regPrev )) {
			AddWinding( e, ePrev );
			DeleteRegion( tess, regPrev );
			if ( !tessMeshDelete( tess->mesh, ePrev ) ) longjmp(tess->env,1);
		}
		firstTime = FALSE;
		regPrev = reg;
		ePrev = e;
	}
	regPrev->dirty = TRUE;
	assert( regPrev->windingNumber - e->winding == reg->windingNumber );

	if( cleanUp ) {
		/* Check for intersections between newly adjacent edges. */
		WalkDirtyRegions( tess, regPrev );
	}
}