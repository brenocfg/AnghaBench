#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  inside; TYPE_1__* eUp; } ;
struct TYPE_7__ {TYPE_1__* anEdge; int /*<<< orphan*/  inside; } ;
struct TYPE_6__ {TYPE_2__* Lface; } ;
typedef  int /*<<< orphan*/  TESStesselator ;
typedef  TYPE_1__ TESShalfEdge ;
typedef  TYPE_2__ TESSface ;
typedef  TYPE_3__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteRegion (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void FinishRegion( TESStesselator *tess, ActiveRegion *reg )
/*
* Delete a region from the sweep line.  This happens when the upper
* and lower chains of a region meet (at a vertex on the sweep line).
* The "inside" flag is copied to the appropriate mesh face (we could
* not do this before -- since the structure of the mesh is always
* changing, this face may not have even existed until now).
*/
{
	TESShalfEdge *e = reg->eUp;
	TESSface *f = e->Lface;

	f->inside = reg->inside;
	f->anEdge = e;   /* optimization for tessMeshTessellateMonoRegion() */
	DeleteRegion( tess, reg );
}