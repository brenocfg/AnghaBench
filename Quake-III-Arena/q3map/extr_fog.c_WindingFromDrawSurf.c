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
struct TYPE_8__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ winding_t ;
struct TYPE_9__ {int numVerts; TYPE_1__* verts; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_7__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 TYPE_2__* AllocWinding (int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

winding_t	*WindingFromDrawSurf( mapDrawSurface_t *ds ) {
	winding_t	*w;
	int			i;

	w = AllocWinding( ds->numVerts );
	w->numpoints = ds->numVerts;
	for ( i = 0 ; i < ds->numVerts ; i++ ) {
		VectorCopy( ds->verts[i].xyz, w->p[i] );
	}
	return w;
}