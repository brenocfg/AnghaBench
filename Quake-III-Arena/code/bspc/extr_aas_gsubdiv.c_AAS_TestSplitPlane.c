#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_9__ {int planenum; int faceflags; TYPE_1__* winding; TYPE_3__* frontarea; struct TYPE_9__** next; } ;
typedef  TYPE_2__ tmp_face_t ;
struct TYPE_10__ {TYPE_2__* tmpfaces; } ;
typedef  TYPE_3__ tmp_area_t ;

/* Variables and functions */
 TYPE_1__* AAS_SplitWinding (TYPE_3__*,int) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float FACECLIP_EPSILON ; 
 float FACE_EPSILON ; 
 int FACE_GROUND ; 
 int FindFloatPlane (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 

int AAS_TestSplitPlane(tmp_area_t *tmparea, vec3_t normal, float dist,
							int *facesplits, int *groundsplits, int *epsilonfaces)
{
	int j, side, front, back, planenum;
	float d, d_front, d_back;
	tmp_face_t *face;
	winding_t *w;

	*facesplits = *groundsplits = *epsilonfaces = 0;

	planenum = FindFloatPlane(normal, dist);

	w = AAS_SplitWinding(tmparea, planenum);
	if (!w) return false;
	FreeWinding(w);
	//
	for (face = tmparea->tmpfaces; face; face = face->next[side])
	{
		//side of the face the area is on
		side = face->frontarea != tmparea;

		if ((face->planenum & ~1) == (planenum & ~1))
		{
			Log_Print("AAS_TestSplitPlane: tried face plane as splitter\n");
			return false;
		} //end if
		w = face->winding;
		//reset distance at front and back side of plane
		d_front = d_back = 0;
		//reset front and back flags
		front = back = 0;
		for (j = 0; j < w->numpoints; j++)
		{
			d = DotProduct(w->p[j], normal) - dist;
			if (d > d_front) d_front = d;
			if (d < d_back) d_back = d;

			if (d > 0.4) // PLANESIDE_EPSILON)
				front = 1;
			if (d < -0.4) // PLANESIDE_EPSILON)
				back = 1;
		} //end for
		//check for an epsilon face
		if ( (d_front > FACECLIP_EPSILON && d_front < FACE_EPSILON)
			|| (d_back < -FACECLIP_EPSILON && d_back > -FACE_EPSILON) )
		{
			(*epsilonfaces)++;
		} //end if
		//if the face has points at both sides of the plane
		if (front && back)
		{
			(*facesplits)++;
			if (face->faceflags & FACE_GROUND)
			{
				(*groundsplits)++;
			} //end if
		} //end if
	} //end for
	return true;
}