#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_8__ {int planenum; TYPE_1__* winding; } ;
typedef  TYPE_2__ tmp_face_t ;
struct TYPE_9__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;

/* Variables and functions */
 scalar_t__ CONVEX_EPSILON ; 
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* mapplanes ; 

int NonConvex(tmp_face_t *face1, tmp_face_t *face2, int side1, int side2)
{
	int i;
	winding_t *w1, *w2;
	plane_t *plane1, *plane2;
	
	w1 = face1->winding;
	w2 = face2->winding;

	plane1 = &mapplanes[face1->planenum ^ side1];
	plane2 = &mapplanes[face2->planenum ^ side2];

	//check if one of the points of face1 is at the back of the plane of face2
	for (i = 0; i < w1->numpoints; i++)
	{
		if (DotProduct(plane2->normal, w1->p[i]) - plane2->dist < -CONVEX_EPSILON) return true;
	} //end for
	//check if one of the points of face2 is at the back of the plane of face1
	for (i = 0; i < w2->numpoints; i++)
	{
		if (DotProduct(plane1->normal, w2->p[i]) - plane1->dist < -CONVEX_EPSILON) return true;
	} //end for

	return false;
}