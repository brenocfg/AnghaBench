#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  float* vec3_t ;
struct TYPE_6__ {float value; float* color; int contents; int backsplashFraction; int /*<<< orphan*/  backsplashDistance; } ;
typedef  TYPE_1__ shaderInfo_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_7__ {float photons; TYPE_1__* si; int /*<<< orphan*/  color; int /*<<< orphan*/  origin; int /*<<< orphan*/  type; void* next; int /*<<< orphan*/  twosided; int /*<<< orphan*/  emitColor; int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; int /*<<< orphan*/ * w; } ;
typedef  TYPE_2__ light_t ;

/* Variables and functions */
 int CONTENTS_FOG ; 
 int /*<<< orphan*/  ClipWindingEpsilon (int /*<<< orphan*/ *,float*,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DotProduct (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ON_EPSILON ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (float*,float,int /*<<< orphan*/ ) ; 
 float WindingArea (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WindingBounds (int /*<<< orphan*/ *,float*,float*) ; 
 int /*<<< orphan*/  WindingCenter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 float areaScale ; 
 int /*<<< orphan*/  emit_area ; 
 int /*<<< orphan*/  emit_point ; 
 float formFactorValueScale ; 
 void* lights ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numAreaLights ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void SubdivideAreaLight( shaderInfo_t *ls, winding_t *w, vec3_t normal, 
						float areaSubdivide, qboolean backsplash ) {
	float			area, value, intensity;
	light_t			*dl, *dl2;
	vec3_t			mins, maxs;
	int				axis;
	winding_t		*front, *back;
	vec3_t			planeNormal;
	float			planeDist;

	if ( !w ) {
		return;
	}

	WindingBounds( w, mins, maxs );

	// check for subdivision
	for ( axis = 0 ; axis < 3 ; axis++ ) {
		if ( maxs[axis] - mins[axis] > areaSubdivide ) {
			VectorClear( planeNormal );
			planeNormal[axis] = 1;
			planeDist = ( maxs[axis] + mins[axis] ) * 0.5;
			ClipWindingEpsilon ( w, planeNormal, planeDist, ON_EPSILON, &front, &back );
			SubdivideAreaLight( ls, front, normal, areaSubdivide, qfalse );
			SubdivideAreaLight( ls, back, normal, areaSubdivide, qfalse );
			FreeWinding( w );
			return;
		}
	}

	// create a light from this
	area = WindingArea (w);
	if ( area <= 0 || area > 20000000 ) {
		return;
	}

	numAreaLights++;
	dl = malloc(sizeof(*dl));
	memset (dl, 0, sizeof(*dl));
	dl->next = lights;
	lights = dl;
	dl->type = emit_area;

	WindingCenter( w, dl->origin );
	dl->w = w;
	VectorCopy ( normal, dl->normal);
	dl->dist = DotProduct( dl->origin, normal );

	value = ls->value;
	intensity = value * area * areaScale;
	VectorAdd( dl->origin, dl->normal, dl->origin );

	VectorCopy( ls->color, dl->color );

	dl->photons = intensity;

	// emitColor is irrespective of the area
	VectorScale( ls->color, value*formFactorValueScale*areaScale, dl->emitColor );

	dl->si = ls;

	if ( ls->contents & CONTENTS_FOG ) {
		dl->twosided = qtrue;
	}

	// optionally create a point backsplash light
	if ( backsplash && ls->backsplashFraction > 0 ) {
		dl2 = malloc(sizeof(*dl));
		memset (dl2, 0, sizeof(*dl2));
		dl2->next = lights;
		lights = dl2;
		dl2->type = emit_point;

		VectorMA( dl->origin, ls->backsplashDistance, normal, dl2->origin );

		VectorCopy( ls->color, dl2->color );

		dl2->photons = dl->photons * ls->backsplashFraction;
		dl2->si = ls;
	}
}