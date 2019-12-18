#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int numpoints; int /*<<< orphan*/  points; } ;
typedef  TYPE_2__ winding_t ;
struct TYPE_17__ {int numpoints; int /*<<< orphan*/  points; } ;
struct TYPE_19__ {float photons; float* emitColor; TYPE_4__* si; int /*<<< orphan*/ * color; int /*<<< orphan*/  origin; int /*<<< orphan*/  type; int /*<<< orphan*/  twosided; int /*<<< orphan*/ * normal; int /*<<< orphan*/ * plane; TYPE_1__ w; } ;
typedef  TYPE_3__ vlight_t ;
typedef  float* vec3_t ;
struct TYPE_20__ {float value; float* color; int contents; int backsplashFraction; int /*<<< orphan*/  backsplashDistance; } ;
typedef  TYPE_4__ shaderInfo_t ;
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int CONTENTS_FOG ; 
 int /*<<< orphan*/  ClipWindingEpsilon (TYPE_2__*,float*,float,int /*<<< orphan*/ ,TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/  DotProduct (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_2__*) ; 
 int /*<<< orphan*/  LIGHT_POINTFAKESURFACE ; 
 int /*<<< orphan*/  LIGHT_POINTRADIAL ; 
 int /*<<< orphan*/  ON_EPSILON ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 float WindingArea (TYPE_2__*) ; 
 int /*<<< orphan*/  WindingBounds (TYPE_2__*,float*,float*) ; 
 int /*<<< orphan*/  WindingCenter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 float lightAreaScale ; 
 float lightFormFactorValueScale ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numvlights ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__** vlights ; 

void VL_SubdivideAreaLight( shaderInfo_t *ls, winding_t *w, vec3_t normal, 
						float areaSubdivide, qboolean backsplash ) {
	float			area, value, intensity;
	vlight_t			*dl, *dl2;
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
			VL_SubdivideAreaLight( ls, front, normal, areaSubdivide, qfalse );
			VL_SubdivideAreaLight( ls, back, normal, areaSubdivide, qfalse );
			FreeWinding( w );
			return;
		}
	}

	// create a light from this
	area = WindingArea (w);
	if ( area <= 0 || area > 20000000 ) {
		return;
	}

	dl = malloc(sizeof(*dl));
	memset (dl, 0, sizeof(*dl));
	dl->type = LIGHT_POINTFAKESURFACE;

	WindingCenter( w, dl->origin );
	memcpy(dl->w.points, w->points, sizeof(vec3_t) * w->numpoints);
	dl->w.numpoints = w->numpoints;
	VectorCopy ( normal, dl->normal);
	VectorCopy ( normal, dl->plane);
	dl->plane[3] = DotProduct( dl->origin, normal );

	value = ls->value;
	intensity = value * area * lightAreaScale;
	VectorAdd( dl->origin, dl->normal, dl->origin );

	VectorCopy( ls->color, dl->color );

	dl->photons = intensity;

	// emitColor is irrespective of the area
	VectorScale( ls->color, value*lightFormFactorValueScale*lightAreaScale, dl->emitColor );
	//
	VectorCopy(dl->emitColor, dl->color);

	dl->si = ls;

	if ( ls->contents & CONTENTS_FOG ) {
		dl->twosided = qtrue;
	}

	vlights[numvlights++] = dl;

	// optionally create a point backsplash light
	if ( backsplash && ls->backsplashFraction > 0 ) {

		dl2 = malloc(sizeof(*dl));
		memset (dl2, 0, sizeof(*dl2));
		dl2->type = LIGHT_POINTRADIAL;

		VectorMA( dl->origin, ls->backsplashDistance, normal, dl2->origin );

		VectorCopy( ls->color, dl2->color );

		dl2->photons = dl->photons * ls->backsplashFraction;
		dl2->si = ls;

		vlights[numvlights++] = dl2;
	}
}