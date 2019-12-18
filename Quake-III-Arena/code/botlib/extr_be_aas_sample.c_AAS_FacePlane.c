#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ aas_plane_t ;
struct TYPE_6__ {TYPE_1__* faces; TYPE_2__* planes; } ;
struct TYPE_4__ {size_t planenum; } ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ aasworld ; 

void AAS_FacePlane(int facenum, vec3_t normal, float *dist)
{
	aas_plane_t *plane;

	plane = &aasworld.planes[aasworld.faces[facenum].planenum];
	VectorCopy(plane->normal, normal);
	*dist = plane->dist;
}