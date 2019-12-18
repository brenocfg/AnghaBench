#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* next; struct TYPE_10__* prev; TYPE_2__* anEdge; } ;
struct TYPE_9__ {struct TYPE_9__* Lnext; TYPE_3__* Lface; } ;
struct TYPE_8__ {int /*<<< orphan*/  faceBucket; } ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESShalfEdge ;
typedef  TYPE_3__ TESSface ;

/* Variables and functions */
 int /*<<< orphan*/  bucketFree (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void KillFace( TESSmesh *mesh, TESSface *fDel, TESSface *newLface )
{
	TESShalfEdge *e, *eStart = fDel->anEdge;
	TESSface *fPrev, *fNext;

	/* change the left face of all affected edges */
	e = eStart;
	do {
		e->Lface = newLface;
		e = e->Lnext;
	} while( e != eStart );

	/* delete from circular doubly-linked list */
	fPrev = fDel->prev;
	fNext = fDel->next;
	fNext->prev = fPrev;
	fPrev->next = fNext;

	bucketFree( mesh->faceBucket, fDel );
}