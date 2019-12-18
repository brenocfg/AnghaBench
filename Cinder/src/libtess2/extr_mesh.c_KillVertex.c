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
struct TYPE_10__ {struct TYPE_10__* Onext; TYPE_1__* Org; } ;
struct TYPE_9__ {int /*<<< orphan*/  vertexBucket; } ;
struct TYPE_8__ {struct TYPE_8__* next; struct TYPE_8__* prev; TYPE_3__* anEdge; } ;
typedef  TYPE_1__ TESSvertex ;
typedef  TYPE_2__ TESSmesh ;
typedef  TYPE_3__ TESShalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  bucketFree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void KillVertex( TESSmesh *mesh, TESSvertex *vDel, TESSvertex *newOrg )
{
	TESShalfEdge *e, *eStart = vDel->anEdge;
	TESSvertex *vPrev, *vNext;

	/* change the origin of all affected edges */
	e = eStart;
	do {
		e->Org = newOrg;
		e = e->Onext;
	} while( e != eStart );

	/* delete from circular doubly-linked list */
	vPrev = vDel->prev;
	vNext = vDel->next;
	vNext->prev = vPrev;
	vPrev->next = vNext;

	bucketFree( mesh->vertexBucket, vDel );
}