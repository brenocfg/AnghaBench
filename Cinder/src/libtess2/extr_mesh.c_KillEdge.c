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
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* Sym; } ;
struct TYPE_6__ {int /*<<< orphan*/  edgeBucket; } ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESShalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  bucketFree (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void KillEdge( TESSmesh *mesh, TESShalfEdge *eDel )
{
	TESShalfEdge *ePrev, *eNext;

	/* Half-edges are allocated in pairs, see EdgePair above */
	if( eDel->Sym < eDel ) { eDel = eDel->Sym; }

	/* delete from circular doubly-linked list */
	eNext = eDel->next;
	ePrev = eDel->Sym->next;
	eNext->Sym->next = ePrev;
	ePrev->Sym->next = eNext;

	bucketFree( mesh->edgeBucket, eDel );
}