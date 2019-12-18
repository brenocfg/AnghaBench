#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  inside; int /*<<< orphan*/  marked; int /*<<< orphan*/ * trail; TYPE_1__* anEdge; struct TYPE_7__* prev; struct TYPE_7__* next; } ;
struct TYPE_6__ {struct TYPE_6__* Lnext; TYPE_2__* Lface; } ;
typedef  TYPE_1__ TESShalfEdge ;
typedef  TYPE_2__ TESSface ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MakeFace( TESSface *newFace, TESShalfEdge *eOrig, TESSface *fNext )
{
	TESShalfEdge *e;
	TESSface *fPrev;
	TESSface *fNew = newFace;

	assert(fNew != NULL); 

	/* insert in circular doubly-linked list before fNext */
	fPrev = fNext->prev;
	fNew->prev = fPrev;
	fPrev->next = fNew;
	fNew->next = fNext;
	fNext->prev = fNew;

	fNew->anEdge = eOrig;
	fNew->trail = NULL;
	fNew->marked = FALSE;

	/* The new face is marked "inside" if the old one was.  This is a
	* convenience for the common case where a face has been split in two.
	*/
	fNew->inside = fNext->inside;

	/* fix other edges on this face loop */
	e = eOrig;
	do {
		e->Lface = fNew;
		e = e->Lnext;
	} while( e != eOrig );
}