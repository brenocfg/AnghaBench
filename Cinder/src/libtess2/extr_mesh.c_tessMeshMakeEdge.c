#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* Sym; } ;
struct TYPE_9__ {int /*<<< orphan*/  fHead; int /*<<< orphan*/  vHead; int /*<<< orphan*/  eHead; int /*<<< orphan*/  faceBucket; int /*<<< orphan*/  vertexBucket; } ;
typedef  int /*<<< orphan*/  TESSvertex ;
typedef  TYPE_1__ TESSmesh ;
typedef  TYPE_2__ TESShalfEdge ;
typedef  int /*<<< orphan*/  TESSface ;

/* Variables and functions */
 TYPE_2__* MakeEdge (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeFace (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeVertex (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ bucketAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bucketFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

TESShalfEdge *tessMeshMakeEdge( TESSmesh *mesh )
{
	TESSvertex *newVertex1 = (TESSvertex*)bucketAlloc(mesh->vertexBucket);
	TESSvertex *newVertex2 = (TESSvertex*)bucketAlloc(mesh->vertexBucket);
	TESSface *newFace = (TESSface*)bucketAlloc(mesh->faceBucket);
	TESShalfEdge *e;

	/* if any one is null then all get freed */
	if (newVertex1 == NULL || newVertex2 == NULL || newFace == NULL) {
		if (newVertex1 != NULL) bucketFree( mesh->vertexBucket, newVertex1 );
		if (newVertex2 != NULL) bucketFree( mesh->vertexBucket, newVertex2 );
		if (newFace != NULL) bucketFree( mesh->faceBucket, newFace );     
		return NULL;
	} 

	e = MakeEdge( mesh, &mesh->eHead );
	if (e == NULL) return NULL;

	MakeVertex( newVertex1, e, &mesh->vHead );
	MakeVertex( newVertex2, e->Sym, &mesh->vHead );
	MakeFace( newFace, e, &mesh->fHead );
	return e;
}