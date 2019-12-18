#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * activeRegion; scalar_t__ winding; int /*<<< orphan*/ * Lface; int /*<<< orphan*/ * Org; struct TYPE_8__* Lnext; struct TYPE_8__* Onext; struct TYPE_8__* Sym; struct TYPE_8__* next; } ;
struct TYPE_9__ {TYPE_2__ eSym; TYPE_2__ e; } ;
struct TYPE_7__ {int /*<<< orphan*/  edgeBucket; } ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESShalfEdge ;
typedef  TYPE_3__ EdgePair ;

/* Variables and functions */
 scalar_t__ bucketAlloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TESShalfEdge *MakeEdge( TESSmesh* mesh, TESShalfEdge *eNext )
{
	TESShalfEdge *e;
	TESShalfEdge *eSym;
	TESShalfEdge *ePrev;
	EdgePair *pair = (EdgePair *)bucketAlloc( mesh->edgeBucket );
	if (pair == NULL) return NULL;

	e = &pair->e;
	eSym = &pair->eSym;

	/* Make sure eNext points to the first edge of the edge pair */
	if( eNext->Sym < eNext ) { eNext = eNext->Sym; }

	/* Insert in circular doubly-linked list before eNext.
	* Note that the prev pointer is stored in Sym->next.
	*/
	ePrev = eNext->Sym->next;
	eSym->next = ePrev;
	ePrev->Sym->next = e;
	e->next = eNext;
	eNext->Sym->next = eSym;

	e->Sym = eSym;
	e->Onext = e;
	e->Lnext = eSym;
	e->Org = NULL;
	e->Lface = NULL;
	e->winding = 0;
	e->activeRegion = NULL;

	eSym->Sym = e;
	eSym->Onext = eSym;
	eSym->Lnext = e;
	eSym->Org = NULL;
	eSym->Lface = NULL;
	eSym->winding = 0;
	eSym->activeRegion = NULL;

	return e;
}