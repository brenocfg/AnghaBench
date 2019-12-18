#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_21__ {int dirty; int /*<<< orphan*/  inside; TYPE_4__* eUp; } ;
struct TYPE_20__ {TYPE_2__* Rface; struct TYPE_20__* Sym; struct TYPE_20__* Lnext; int /*<<< orphan*/  Org; int /*<<< orphan*/  Dst; TYPE_1__* Lface; } ;
struct TYPE_19__ {int /*<<< orphan*/  env; int /*<<< orphan*/  mesh; } ;
struct TYPE_18__ {int /*<<< orphan*/  inside; } ;
struct TYPE_17__ {int /*<<< orphan*/  inside; } ;
struct TYPE_16__ {int dirty; } ;
typedef  TYPE_3__ TESStesselator ;
typedef  TYPE_4__ TESShalfEdge ;
typedef  TYPE_5__ ActiveRegion ;

/* Variables and functions */
 scalar_t__ EdgeSign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 TYPE_12__* RegionAbove (TYPE_5__*) ; 
 TYPE_5__* RegionBelow (TYPE_5__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  VertEq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VertLeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tessMeshSplice (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* tessMeshSplitEdge (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static int CheckForLeftSplice( TESStesselator *tess, ActiveRegion *regUp )
/*
* Check the upper and lower edge of "regUp", to make sure that the
* eUp->Dst is above eLo, or eLo->Dst is below eUp (depending on which
* destination is rightmost).
*
* Theoretically, this should always be true.  However, splitting an edge
* into two pieces can change the results of previous tests.  For example,
* suppose at one point we checked eUp and eLo, and decided that eUp->Dst
* is barely above eLo.  Then later, we split eLo into two edges (eg. from
* a splice operation like this one).  This can change the result of
* the test so that now eUp->Dst is incident to eLo, or barely below it.
* We must correct this condition to maintain the dictionary invariants
* (otherwise new edges might get inserted in the wrong place in the
* dictionary, and bad stuff will happen).
*
* We fix the problem by just splicing the offending vertex into the
* other edge.
*/
{
	ActiveRegion *regLo = RegionBelow(regUp);
	TESShalfEdge *eUp = regUp->eUp;
	TESShalfEdge *eLo = regLo->eUp;
	TESShalfEdge *e;

	assert( ! VertEq( eUp->Dst, eLo->Dst ));

	if( VertLeq( eUp->Dst, eLo->Dst )) {
		if( EdgeSign( eUp->Dst, eLo->Dst, eUp->Org ) < 0 ) return FALSE;

		/* eLo->Dst is above eUp, so splice eLo->Dst into eUp */
		RegionAbove(regUp)->dirty = regUp->dirty = TRUE;
		e = tessMeshSplitEdge( tess->mesh, eUp );
		if (e == NULL) longjmp(tess->env,1);
		if ( !tessMeshSplice( tess->mesh, eLo->Sym, e ) ) longjmp(tess->env,1);
		e->Lface->inside = regUp->inside;
	} else {
		if( EdgeSign( eLo->Dst, eUp->Dst, eLo->Org ) > 0 ) return FALSE;

		/* eUp->Dst is below eLo, so splice eUp->Dst into eLo */
		regUp->dirty = regLo->dirty = TRUE;
		e = tessMeshSplitEdge( tess->mesh, eLo );
		if (e == NULL) longjmp(tess->env,1);    
		if ( !tessMeshSplice( tess->mesh, eUp->Lnext, eLo->Sym ) ) longjmp(tess->env,1);
		e->Rface->inside = regUp->inside;
	}
	return TRUE;
}