#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* anEdge; } ;
struct TYPE_17__ {int /*<<< orphan*/  anEdge; } ;
struct TYPE_16__ {int /*<<< orphan*/  Oprev; struct TYPE_16__* Onext; TYPE_9__* Org; TYPE_7__* Lface; TYPE_7__* Rface; struct TYPE_16__* Sym; } ;
struct TYPE_15__ {int /*<<< orphan*/  faceBucket; } ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESShalfEdge ;
typedef  int /*<<< orphan*/  TESSface ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KillEdge (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  KillFace (TYPE_1__*,TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  KillVertex (TYPE_1__*,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeFace (int /*<<< orphan*/ *,TYPE_2__*,TYPE_7__*) ; 
 int /*<<< orphan*/  Splice (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ bucketAlloc (int /*<<< orphan*/ ) ; 

int tessMeshDelete( TESSmesh *mesh, TESShalfEdge *eDel )
{
	TESShalfEdge *eDelSym = eDel->Sym;
	int joiningLoops = FALSE;

	/* First step: disconnect the origin vertex eDel->Org.  We make all
	* changes to get a consistent mesh in this "intermediate" state.
	*/
	if( eDel->Lface != eDel->Rface ) {
		/* We are joining two loops into one -- remove the left face */
		joiningLoops = TRUE;
		KillFace( mesh, eDel->Lface, eDel->Rface );
	}

	if( eDel->Onext == eDel ) {
		KillVertex( mesh, eDel->Org, NULL );
	} else {
		/* Make sure that eDel->Org and eDel->Rface point to valid half-edges */
		eDel->Rface->anEdge = eDel->Oprev;
		eDel->Org->anEdge = eDel->Onext;

		Splice( eDel, eDel->Oprev );
		if( ! joiningLoops ) {
			TESSface *newFace= (TESSface*)bucketAlloc( mesh->faceBucket );
			if (newFace == NULL) return 0; 

			/* We are splitting one loop into two -- create a new loop for eDel. */
			MakeFace( newFace, eDel, eDel->Lface );
		}
	}

	/* Claim: the mesh is now in a consistent state, except that eDel->Org
	* may have been deleted.  Now we disconnect eDel->Dst.
	*/
	if( eDelSym->Onext == eDelSym ) {
		KillVertex( mesh, eDelSym->Org, NULL );
		KillFace( mesh, eDelSym->Lface, NULL );
	} else {
		/* Make sure that eDel->Dst and eDel->Lface point to valid half-edges */
		eDel->Lface->anEdge = eDelSym->Oprev;
		eDelSym->Org->anEdge = eDelSym->Onext;
		Splice( eDelSym, eDelSym->Oprev );
	}

	/* Any isolated vertices or faces have already been freed. */
	KillEdge( mesh, eDel );

	return 1;
}