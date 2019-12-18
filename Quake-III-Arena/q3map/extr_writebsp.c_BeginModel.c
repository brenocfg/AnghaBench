#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_11__ {int width; int height; TYPE_1__* verts; } ;
struct TYPE_12__ {TYPE_2__ mesh; struct TYPE_12__* next; } ;
typedef  TYPE_3__ parseMesh_t ;
struct TYPE_13__ {TYPE_6__* brushes; TYPE_3__* patches; } ;
typedef  TYPE_4__ entity_t ;
struct TYPE_14__ {int /*<<< orphan*/  firstBrush; int /*<<< orphan*/  firstSurface; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_5__ dmodel_t ;
struct TYPE_15__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  numsides; struct TYPE_15__* next; } ;
typedef  TYPE_6__ bspbrush_t ;
struct TYPE_10__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmitBrushes (TYPE_6__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_MODELS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* dmodels ; 
 TYPE_4__* entities ; 
 size_t entity_num ; 
 int /*<<< orphan*/  numDrawSurfaces ; 
 int /*<<< orphan*/  numbrushes ; 
 size_t nummodels ; 

void BeginModel( void ) {
	dmodel_t	*mod;
	bspbrush_t	*b;
	entity_t	*e;
	vec3_t		mins, maxs;
	parseMesh_t	*p;
	int			i;

	if ( nummodels == MAX_MAP_MODELS ) {
		Error( "MAX_MAP_MODELS" );
	}
	mod = &dmodels[nummodels];

	//
	// bound the brushes
	//
	e = &entities[entity_num];

	ClearBounds (mins, maxs);
	for ( b = e->brushes ; b ; b = b->next ) {
		if ( !b->numsides ) {
			continue;	// not a real brush (origin brush, etc)
		}
		AddPointToBounds (b->mins, mins, maxs);
		AddPointToBounds (b->maxs, mins, maxs);
	}

	for ( p = e->patches ; p ; p = p->next ) {
		for ( i = 0 ; i < p->mesh.width * p->mesh.height ; i++ ) {
			AddPointToBounds( p->mesh.verts[i].xyz, mins, maxs );
		}
	}

	VectorCopy (mins, mod->mins);
	VectorCopy (maxs, mod->maxs);

	mod->firstSurface = numDrawSurfaces;
	mod->firstBrush = numbrushes;

	EmitBrushes( e->brushes );
}