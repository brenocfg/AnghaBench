#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_4__ {int* color; int /*<<< orphan*/  origin; } ;
typedef  TYPE_1__ srfFlare_t ;
typedef  int byte ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_AddQuadStampExt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ *) ; 
 TYPE_2__* r_ignore ; 

void RB_SurfaceFlare( srfFlare_t *surf ) {
#if 0
	vec3_t		left, up;
	byte		color[4];

	color[0] = surf->color[0] * 255;
	color[1] = surf->color[1] * 255;
	color[2] = surf->color[2] * 255;
	color[3] = 255;

	VectorClear( left );
	VectorClear( up );

	left[0] = r_ignore->value;

	up[1] = r_ignore->value;
	
	RB_AddQuadStampExt( surf->origin, left, up, color, 0, 0, 1, 1 );
#endif
}