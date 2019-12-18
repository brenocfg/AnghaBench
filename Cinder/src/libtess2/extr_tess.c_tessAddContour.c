#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int winding; } ;
struct TYPE_11__ {int winding; TYPE_6__* Sym; TYPE_1__* Org; struct TYPE_11__* Lnext; } ;
struct TYPE_10__ {int outOfMemory; int /*<<< orphan*/ * mesh; int /*<<< orphan*/  alloc; } ;
struct TYPE_9__ {int /*<<< orphan*/ * coords; } ;
typedef  TYPE_2__ TESStesselator ;
typedef  int /*<<< orphan*/  TESSreal ;
typedef  TYPE_3__ TESShalfEdge ;

/* Variables and functions */
 TYPE_3__* tessMeshMakeEdge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tessMeshNewMesh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tessMeshSplice (int /*<<< orphan*/ *,TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/ * tessMeshSplitEdge (int /*<<< orphan*/ *,TYPE_3__*) ; 

void tessAddContour( TESStesselator *tess, int size, const void* vertices,
					int stride, int numVertices )
{
	const unsigned char *src = (const unsigned char*)vertices;
	TESShalfEdge *e;
	int i;

	if ( tess->mesh == NULL )
	  	tess->mesh = tessMeshNewMesh( &tess->alloc );
 	if ( tess->mesh == NULL ) {
		tess->outOfMemory = 1;
		return;
	}

	if ( size < 2 )
		size = 2;
	if ( size > 3 )
		size = 3;

	e = NULL;

	for( i = 0; i < numVertices; ++i )
	{
		const TESSreal* coords = (const TESSreal*)src;
		src += stride;

		if( e == NULL ) {
			/* Make a self-loop (one vertex, one edge). */
			e = tessMeshMakeEdge( tess->mesh );
			if ( e == NULL ) {
				tess->outOfMemory = 1;
				return;
			}
			if ( !tessMeshSplice( tess->mesh, e, e->Sym ) ) {
				tess->outOfMemory = 1;
				return;
			}
		} else {
			/* Create a new vertex and edge which immediately follow e
			* in the ordering around the left face.
			*/
			if ( tessMeshSplitEdge( tess->mesh, e ) == NULL ) {
				tess->outOfMemory = 1;
				return;
			}
			e = e->Lnext;
		}

		/* The new vertex is now e->Org. */
		e->Org->coords[0] = coords[0];
		e->Org->coords[1] = coords[1];
		if ( size > 2 )
			e->Org->coords[2] = coords[2];
		else
			e->Org->coords[2] = 0;

		/* The winding of an edge says how the winding number changes as we
		* cross from the edge''s right face to its left face.  We add the
		* vertices in such an order that a CCW contour will add +1 to
		* the winding number of the region inside the contour.
		*/
		e->winding = 1;
		e->Sym->winding = -1;
	}
}