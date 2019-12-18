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
struct TYPE_12__ {scalar_t__ inside; TYPE_3__* anEdge; struct TYPE_12__* next; } ;
struct TYPE_11__ {int /*<<< orphan*/ * Org; struct TYPE_11__* Lnext; TYPE_1__* Lprev; TYPE_4__* Lface; struct TYPE_11__* Sym; } ;
struct TYPE_10__ {TYPE_4__ fHead; } ;
struct TYPE_9__ {int /*<<< orphan*/  Org; } ;
typedef  int /*<<< orphan*/  TESSvertex ;
typedef  TYPE_2__ TESSmesh ;
typedef  TYPE_3__ TESShalfEdge ;
typedef  TYPE_4__ TESSface ;

/* Variables and functions */
 int CountFaceVerts (TYPE_4__*) ; 
 scalar_t__ VertCCW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tessMeshDelete (TYPE_2__*,TYPE_3__*) ; 

int tessMeshMergeConvexFaces( TESSmesh *mesh, int maxVertsPerFace )
{
	TESSface *f;
	TESShalfEdge *eCur, *eNext, *eSym;
	TESSvertex *vStart;
	int curNv, symNv;
	
	for( f = mesh->fHead.next; f != &mesh->fHead; f = f->next )
	{
		// Skip faces which are outside the result.
		if( !f->inside )
			continue;

		eCur = f->anEdge;
		vStart = eCur->Org;
			
		while (1)
		{
			eNext = eCur->Lnext;
			eSym = eCur->Sym;

			// Try to merge if the neighbour face is valid.
			if( eSym && eSym->Lface && eSym->Lface->inside )
			{
				// Try to merge the neighbour faces if the resulting polygons
				// does not exceed maximum number of vertices.
				curNv = CountFaceVerts( f );
				symNv = CountFaceVerts( eSym->Lface );
				if( (curNv+symNv-2) <= maxVertsPerFace )
				{
					// Merge if the resulting poly is convex.
					if( VertCCW( eCur->Lprev->Org, eCur->Org, eSym->Lnext->Lnext->Org ) &&
						VertCCW( eSym->Lprev->Org, eSym->Org, eCur->Lnext->Lnext->Org ) )
					{
						eNext = eSym->Lnext;
						if( !tessMeshDelete( mesh, eSym ) )
							return 0;
						eCur = 0;
					}
				}
			}
			
			if( eCur && eCur->Lnext->Org == vStart )
				break;
				
			// Continue to next edge.
			eCur = eNext;
		}
	}
	
	return 1;
}