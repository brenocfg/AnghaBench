#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int meshEdgeBucketSize; int meshVertexBucketSize; int meshFaceBucketSize; int /*<<< orphan*/  userData; scalar_t__ (* memalloc ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_12__ {void* inside; void* marked; int /*<<< orphan*/ * trail; int /*<<< orphan*/ * anEdge; struct TYPE_12__* prev; struct TYPE_12__* next; } ;
struct TYPE_11__ {int /*<<< orphan*/ * activeRegion; scalar_t__ winding; int /*<<< orphan*/ * Lface; int /*<<< orphan*/ * Org; int /*<<< orphan*/ * Lnext; int /*<<< orphan*/ * Onext; struct TYPE_11__* Sym; struct TYPE_11__* next; } ;
struct TYPE_9__ {int /*<<< orphan*/ * anEdge; struct TYPE_9__* prev; struct TYPE_9__* next; } ;
struct TYPE_10__ {TYPE_3__ eHeadSym; TYPE_3__ eHead; TYPE_4__ fHead; TYPE_1__ vHead; void* faceBucket; void* vertexBucket; void* edgeBucket; } ;
typedef  TYPE_1__ TESSvertex ;
typedef  TYPE_2__ TESSmesh ;
typedef  TYPE_3__ TESShalfEdge ;
typedef  TYPE_4__ TESSface ;
typedef  TYPE_5__ TESSalloc ;
typedef  int /*<<< orphan*/  EdgePair ;

/* Variables and functions */
 void* FALSE ; 
 void* createBucketAlloc (TYPE_5__*,char*,int,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 

TESSmesh *tessMeshNewMesh( TESSalloc* alloc )
{
	TESSvertex *v;
	TESSface *f;
	TESShalfEdge *e;
	TESShalfEdge *eSym;
	TESSmesh *mesh = (TESSmesh *)alloc->memalloc( alloc->userData, sizeof( TESSmesh ));
	if (mesh == NULL) {
		return NULL;
	}
	
	if (alloc->meshEdgeBucketSize < 16)
		alloc->meshEdgeBucketSize = 16;
	if (alloc->meshEdgeBucketSize > 4096)
		alloc->meshEdgeBucketSize = 4096;
	
	if (alloc->meshVertexBucketSize < 16)
		alloc->meshVertexBucketSize = 16;
	if (alloc->meshVertexBucketSize > 4096)
		alloc->meshVertexBucketSize = 4096;
	
	if (alloc->meshFaceBucketSize < 16)
		alloc->meshFaceBucketSize = 16;
	if (alloc->meshFaceBucketSize > 4096)
		alloc->meshFaceBucketSize = 4096;

	mesh->edgeBucket = createBucketAlloc( alloc, "Mesh Edges", sizeof(EdgePair), alloc->meshEdgeBucketSize );
	mesh->vertexBucket = createBucketAlloc( alloc, "Mesh Vertices", sizeof(TESSvertex), alloc->meshVertexBucketSize );
	mesh->faceBucket = createBucketAlloc( alloc, "Mesh Faces", sizeof(TESSface), alloc->meshFaceBucketSize );

	v = &mesh->vHead;
	f = &mesh->fHead;
	e = &mesh->eHead;
	eSym = &mesh->eHeadSym;

	v->next = v->prev = v;
	v->anEdge = NULL;

	f->next = f->prev = f;
	f->anEdge = NULL;
	f->trail = NULL;
	f->marked = FALSE;
	f->inside = FALSE;

	e->next = e;
	e->Sym = eSym;
	e->Onext = NULL;
	e->Lnext = NULL;
	e->Org = NULL;
	e->Lface = NULL;
	e->winding = 0;
	e->activeRegion = NULL;

	eSym->next = eSym;
	eSym->Sym = e;
	eSym->Onext = NULL;
	eSym->Lnext = NULL;
	eSym->Org = NULL;
	eSym->Lface = NULL;
	eSym->winding = 0;
	eSym->activeRegion = NULL;

	return mesh;
}