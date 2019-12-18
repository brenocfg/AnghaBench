#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* anEdge; } ;
struct TYPE_14__ {struct TYPE_14__* next; struct TYPE_14__* prev; TYPE_2__* anEdge; } ;
struct TYPE_13__ {int /*<<< orphan*/  Oprev; struct TYPE_13__* Onext; TYPE_9__* Org; struct TYPE_13__* Sym; int /*<<< orphan*/ * Rface; int /*<<< orphan*/ * Lface; struct TYPE_13__* Lnext; } ;
struct TYPE_12__ {int /*<<< orphan*/  faceBucket; } ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESShalfEdge ;
typedef  TYPE_3__ TESSface ;

/* Variables and functions */
 int /*<<< orphan*/  KillEdge (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  KillVertex (TYPE_1__*,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Splice (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bucketFree (int /*<<< orphan*/ ,TYPE_3__*) ; 

void tessMeshZapFace( TESSmesh *mesh, TESSface *fZap )
{
	TESShalfEdge *eStart = fZap->anEdge;
	TESShalfEdge *e, *eNext, *eSym;
	TESSface *fPrev, *fNext;

	/* walk around face, deleting edges whose right face is also NULL */
	eNext = eStart->Lnext;
	do {
		e = eNext;
		eNext = e->Lnext;

		e->Lface = NULL;
		if( e->Rface == NULL ) {
			/* delete the edge -- see TESSmeshDelete above */

			if( e->Onext == e ) {
				KillVertex( mesh, e->Org, NULL );
			} else {
				/* Make sure that e->Org points to a valid half-edge */
				e->Org->anEdge = e->Onext;
				Splice( e, e->Oprev );
			}
			eSym = e->Sym;
			if( eSym->Onext == eSym ) {
				KillVertex( mesh, eSym->Org, NULL );
			} else {
				/* Make sure that eSym->Org points to a valid half-edge */
				eSym->Org->anEdge = eSym->Onext;
				Splice( eSym, eSym->Oprev );
			}
			KillEdge( mesh, e );
		}
	} while( e != eStart );

	/* delete from circular doubly-linked list */
	fPrev = fZap->prev;
	fNext = fZap->next;
	fNext->prev = fPrev;
	fPrev->next = fNext;

	bucketFree( mesh->faceBucket, fZap );
}