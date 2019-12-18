#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {TYPE_4__* eUp; } ;
struct TYPE_34__ {scalar_t__ Dst; TYPE_2__* Sym; struct TYPE_34__* Onext; int /*<<< orphan*/  Lprev; struct TYPE_34__* Oprev; int /*<<< orphan*/  Org; } ;
struct TYPE_33__ {int /*<<< orphan*/  env; int /*<<< orphan*/  mesh; int /*<<< orphan*/  event; } ;
struct TYPE_32__ {TYPE_1__* activeRegion; } ;
struct TYPE_31__ {void* fixUpperEdge; } ;
typedef  TYPE_3__ TESStesselator ;
typedef  TYPE_4__ TESShalfEdge ;
typedef  TYPE_5__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  AddRightEdges (TYPE_3__*,TYPE_5__*,TYPE_4__*,TYPE_4__*,TYPE_4__*,void*) ; 
 int /*<<< orphan*/  CheckForIntersect (TYPE_3__*,TYPE_5__*) ; 
 void* FALSE ; 
 TYPE_4__* FinishLeftRegions (TYPE_3__*,TYPE_5__*,TYPE_5__*) ; 
 TYPE_5__* RegionBelow (TYPE_5__*) ; 
 void* TRUE ; 
 TYPE_5__* TopLeftRegion (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ VertEq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VertLeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalkDirtyRegions (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* tessMeshConnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  tessMeshSplice (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 

__attribute__((used)) static void ConnectRightVertex( TESStesselator *tess, ActiveRegion *regUp,
							   TESShalfEdge *eBottomLeft )
/*
* Purpose: connect a "right" vertex vEvent (one where all edges go left)
* to the unprocessed portion of the mesh.  Since there are no right-going
* edges, two regions (one above vEvent and one below) are being merged
* into one.  "regUp" is the upper of these two regions.
*
* There are two reasons for doing this (adding a right-going edge):
*  - if the two regions being merged are "inside", we must add an edge
*    to keep them separated (the combined region would not be monotone).
*  - in any case, we must leave some record of vEvent in the dictionary,
*    so that we can merge vEvent with features that we have not seen yet.
*    For example, maybe there is a vertical edge which passes just to
*    the right of vEvent; we would like to splice vEvent into this edge.
*
* However, we don't want to connect vEvent to just any vertex.  We don''t
* want the new edge to cross any other edges; otherwise we will create
* intersection vertices even when the input data had no self-intersections.
* (This is a bad thing; if the user's input data has no intersections,
* we don't want to generate any false intersections ourselves.)
*
* Our eventual goal is to connect vEvent to the leftmost unprocessed
* vertex of the combined region (the union of regUp and regLo).
* But because of unseen vertices with all right-going edges, and also
* new vertices which may be created by edge intersections, we don''t
* know where that leftmost unprocessed vertex is.  In the meantime, we
* connect vEvent to the closest vertex of either chain, and mark the region
* as "fixUpperEdge".  This flag says to delete and reconnect this edge
* to the next processed vertex on the boundary of the combined region.
* Quite possibly the vertex we connected to will turn out to be the
* closest one, in which case we won''t need to make any changes.
*/
{
	TESShalfEdge *eNew;
	TESShalfEdge *eTopLeft = eBottomLeft->Onext;
	ActiveRegion *regLo = RegionBelow(regUp);
	TESShalfEdge *eUp = regUp->eUp;
	TESShalfEdge *eLo = regLo->eUp;
	int degenerate = FALSE;

	if( eUp->Dst != eLo->Dst ) {
		(void) CheckForIntersect( tess, regUp );
	}

	/* Possible new degeneracies: upper or lower edge of regUp may pass
	* through vEvent, or may coincide with new intersection vertex
	*/
	if( VertEq( eUp->Org, tess->event )) {
		if ( !tessMeshSplice( tess->mesh, eTopLeft->Oprev, eUp ) ) longjmp(tess->env,1);
		regUp = TopLeftRegion( tess, regUp );
		if (regUp == NULL) longjmp(tess->env,1);
		eTopLeft = RegionBelow( regUp )->eUp;
		FinishLeftRegions( tess, RegionBelow(regUp), regLo );
		degenerate = TRUE;
	}
	if( VertEq( eLo->Org, tess->event )) {
		if ( !tessMeshSplice( tess->mesh, eBottomLeft, eLo->Oprev ) ) longjmp(tess->env,1);
		eBottomLeft = FinishLeftRegions( tess, regLo, NULL );
		degenerate = TRUE;
	}
	if( degenerate ) {
		AddRightEdges( tess, regUp, eBottomLeft->Onext, eTopLeft, eTopLeft, TRUE );
		return;
	}

	/* Non-degenerate situation -- need to add a temporary, fixable edge.
	* Connect to the closer of eLo->Org, eUp->Org.
	*/
	if( VertLeq( eLo->Org, eUp->Org )) {
		eNew = eLo->Oprev;
	} else {
		eNew = eUp;
	}
	eNew = tessMeshConnect( tess->mesh, eBottomLeft->Lprev, eNew );
	if (eNew == NULL) longjmp(tess->env,1);

	/* Prevent cleanup, otherwise eNew might disappear before we've even
	* had a chance to mark it as a temporary edge.
	*/
	AddRightEdges( tess, regUp, eNew, eNew->Onext, eNew->Onext, FALSE );
	eNew->Sym->activeRegion->fixUpperEdge = TRUE;
	WalkDirtyRegions( tess, regUp );
}