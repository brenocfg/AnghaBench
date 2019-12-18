#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  origin; int /*<<< orphan*/  frame; } ;
struct TYPE_13__ {TYPE_2__ e; } ;
typedef  TYPE_4__ trRefEntity_t ;
struct TYPE_14__ {int /*<<< orphan*/ * bounds; } ;
typedef  TYPE_5__ md3Frame_t ;
struct TYPE_17__ {scalar_t__ integer; } ;
struct TYPE_16__ {float value; } ;
struct TYPE_15__ {TYPE_3__* currentModel; } ;
struct TYPE_12__ {int numLods; TYPE_1__** md3; } ;
struct TYPE_10__ {int ofsFrames; } ;

/* Variables and functions */
 float ProjectRadius (float,int /*<<< orphan*/ ) ; 
 float RadiusFromBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int myftol (float) ; 
 TYPE_8__* r_lodbias ; 
 TYPE_7__* r_lodscale ; 
 TYPE_6__ tr ; 

int R_ComputeLOD( trRefEntity_t *ent ) {
	float radius;
	float flod, lodscale;
	float projectedRadius;
	md3Frame_t *frame;
	int lod;

	if ( tr.currentModel->numLods < 2 )
	{
		// model has only 1 LOD level, skip computations and bias
		lod = 0;
	}
	else
	{
		// multiple LODs exist, so compute projected bounding sphere
		// and use that as a criteria for selecting LOD

		frame = ( md3Frame_t * ) ( ( ( unsigned char * ) tr.currentModel->md3[0] ) + tr.currentModel->md3[0]->ofsFrames );

		frame += ent->e.frame;

		radius = RadiusFromBounds( frame->bounds[0], frame->bounds[1] );

		if ( ( projectedRadius = ProjectRadius( radius, ent->e.origin ) ) != 0 )
		{
			lodscale = r_lodscale->value;
			if (lodscale > 20) lodscale = 20;
			flod = 1.0f - projectedRadius * lodscale;
		}
		else
		{
			// object intersects near view plane, e.g. view weapon
			flod = 0;
		}

		flod *= tr.currentModel->numLods;
		lod = myftol( flod );

		if ( lod < 0 )
		{
			lod = 0;
		}
		else if ( lod >= tr.currentModel->numLods )
		{
			lod = tr.currentModel->numLods - 1;
		}
	}

	lod += r_lodbias->integer;
	
	if ( lod >= tr.currentModel->numLods )
		lod = tr.currentModel->numLods - 1;
	if ( lod < 0 )
		lod = 0;

	return lod;
}