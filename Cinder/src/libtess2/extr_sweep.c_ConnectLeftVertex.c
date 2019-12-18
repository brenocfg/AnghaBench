#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_34__ {TYPE_3__* Sym; } ;
struct TYPE_33__ {scalar_t__ fixUpperEdge; scalar_t__ inside; TYPE_3__* eUp; } ;
struct TYPE_32__ {struct TYPE_32__* Sym; struct TYPE_32__* Dnext; TYPE_7__* Lnext; int /*<<< orphan*/  Dst; int /*<<< orphan*/  Org; } ;
struct TYPE_31__ {int /*<<< orphan*/  env; int /*<<< orphan*/  mesh; int /*<<< orphan*/  dict; } ;
struct TYPE_30__ {TYPE_7__* anEdge; } ;
typedef  TYPE_1__ TESSvertex ;
typedef  TYPE_2__ TESStesselator ;
typedef  TYPE_3__ TESShalfEdge ;
typedef  TYPE_4__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  AddRegionBelow (TYPE_2__*,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  AddRightEdges (TYPE_2__*,TYPE_4__*,TYPE_7__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComputeWinding (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConnectLeftDegenerate (TYPE_2__*,TYPE_4__*,TYPE_1__*) ; 
 scalar_t__ EdgeSign (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FixUpperEdge (TYPE_2__*,TYPE_4__*,TYPE_3__*) ; 
 TYPE_4__* RegionBelow (TYPE_4__*) ; 
 int /*<<< orphan*/  SweepEvent (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VertLeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dictKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictSearch (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* tessMeshConnect (int /*<<< orphan*/ ,TYPE_3__*,TYPE_7__*) ; 

__attribute__((used)) static void ConnectLeftVertex( TESStesselator *tess, TESSvertex *vEvent )
/*
* Purpose: connect a "left" vertex (one where both edges go right)
* to the processed portion of the mesh.  Let R be the active region
* containing vEvent, and let U and L be the upper and lower edge
* chains of R.  There are two possibilities:
*
* - the normal case: split R into two regions, by connecting vEvent to
*   the rightmost vertex of U or L lying to the left of the sweep line
*
* - the degenerate case: if vEvent is close enough to U or L, we
*   merge vEvent into that edge chain.  The subcases are:
*	- merging with the rightmost vertex of U or L
*	- merging with the active edge of U or L
*	- merging with an already-processed portion of U or L
*/
{
	ActiveRegion *regUp, *regLo, *reg;
	TESShalfEdge *eUp, *eLo, *eNew;
	ActiveRegion tmp;

	/* assert( vEvent->anEdge->Onext->Onext == vEvent->anEdge ); */

	/* Get a pointer to the active region containing vEvent */
	tmp.eUp = vEvent->anEdge->Sym;
	/* __GL_DICTLISTKEY */ /* tessDictListSearch */
	regUp = (ActiveRegion *)dictKey( dictSearch( tess->dict, &tmp ));
	regLo = RegionBelow( regUp );
	eUp = regUp->eUp;
	eLo = regLo->eUp;

	/* Try merging with U or L first */
	if( EdgeSign( eUp->Dst, vEvent, eUp->Org ) == 0 ) {
		ConnectLeftDegenerate( tess, regUp, vEvent );
		return;
	}

	/* Connect vEvent to rightmost processed vertex of either chain.
	* e->Dst is the vertex that we will connect to vEvent.
	*/
	reg = VertLeq( eLo->Dst, eUp->Dst ) ? regUp : regLo;

	if( regUp->inside || reg->fixUpperEdge) {
		if( reg == regUp ) {
			eNew = tessMeshConnect( tess->mesh, vEvent->anEdge->Sym, eUp->Lnext );
			if (eNew == NULL) longjmp(tess->env,1);
		} else {
			TESShalfEdge *tempHalfEdge= tessMeshConnect( tess->mesh, eLo->Dnext, vEvent->anEdge);
			if (tempHalfEdge == NULL) longjmp(tess->env,1);

			eNew = tempHalfEdge->Sym;
		}
		if( reg->fixUpperEdge ) {
			if ( !FixUpperEdge( tess, reg, eNew ) ) longjmp(tess->env,1);
		} else {
			ComputeWinding( tess, AddRegionBelow( tess, regUp, eNew ));
		}
		SweepEvent( tess, vEvent );
	} else {
		/* The new vertex is in a region which does not belong to the polygon.
		* We don''t need to connect this vertex to the rest of the mesh.
		*/
		AddRightEdges( tess, regUp, vEvent->anEdge, vEvent->anEdge, NULL, TRUE );
	}
}