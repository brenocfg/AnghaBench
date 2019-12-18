#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  Lface; int /*<<< orphan*/  Org; int /*<<< orphan*/  Dst; int /*<<< orphan*/  Lnext; struct TYPE_12__* Sym; } ;
struct TYPE_11__ {int /*<<< orphan*/  vertexBucket; } ;
typedef  int /*<<< orphan*/  TESSvertex ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESShalfEdge ;

/* Variables and functions */
 TYPE_2__* MakeEdge (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MakeVertex (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Splice (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bucketAlloc (int /*<<< orphan*/ ) ; 

TESShalfEdge *tessMeshAddEdgeVertex( TESSmesh *mesh, TESShalfEdge *eOrg )
{
	TESShalfEdge *eNewSym;
	TESShalfEdge *eNew = MakeEdge( mesh, eOrg );
	if (eNew == NULL) return NULL;

	eNewSym = eNew->Sym;

	/* Connect the new edge appropriately */
	Splice( eNew, eOrg->Lnext );

	/* Set the vertex and face information */
	eNew->Org = eOrg->Dst;
	{
		TESSvertex *newVertex= (TESSvertex*)bucketAlloc( mesh->vertexBucket );
		if (newVertex == NULL) return NULL;

		MakeVertex( newVertex, eNewSym, eNew->Org );
	}
	eNew->Lface = eNewSym->Lface = eOrg->Lface;

	return eNew;
}