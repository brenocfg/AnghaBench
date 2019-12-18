#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* anEdge; struct TYPE_12__* next; } ;
struct TYPE_11__ {int /*<<< orphan*/  Onext; struct TYPE_11__* Lnext; } ;
struct TYPE_10__ {TYPE_4__ fHead; } ;
struct TYPE_9__ {int /*<<< orphan*/  mesh; } ;
typedef  TYPE_1__ TESStesselator ;
typedef  TYPE_2__ TESSmesh ;
typedef  TYPE_3__ TESShalfEdge ;
typedef  TYPE_4__ TESSface ;

/* Variables and functions */
 int /*<<< orphan*/  AddWinding (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tessMeshDelete (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int RemoveDegenerateFaces( TESStesselator *tess, TESSmesh *mesh )
/*
* Delete any degenerate faces with only two edges.  WalkDirtyRegions()
* will catch almost all of these, but it won't catch degenerate faces
* produced by splice operations on already-processed edges.
* The two places this can happen are in FinishLeftRegions(), when
* we splice in a "temporary" edge produced by ConnectRightVertex(),
* and in CheckForLeftSplice(), where we splice already-processed
* edges to ensure that our dictionary invariants are not violated
* by numerical errors.
*
* In both these cases it is *very* dangerous to delete the offending
* edge at the time, since one of the routines further up the stack
* will sometimes be keeping a pointer to that edge.
*/
{
	TESSface *f, *fNext;
	TESShalfEdge *e;

	/*LINTED*/
	for( f = mesh->fHead.next; f != &mesh->fHead; f = fNext ) {
		fNext = f->next;
		e = f->anEdge;
		assert( e->Lnext != e );

		if( e->Lnext->Lnext == e ) {
			/* A face with only two edges */
			AddWinding( e->Onext, e );
			if ( !tessMeshDelete( tess->mesh, e ) ) return 0;
		}
	}
	return 1;
}