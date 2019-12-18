#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  scalar_t__* vec3_t ;
struct TYPE_5__ {size_t planenum; int /*<<< orphan*/ * winding; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_6__ {scalar_t__* normal; scalar_t__ dist; } ;
typedef  TYPE_2__ plane_t ;

/* Variables and functions */
 float DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_Write (char*,int /*<<< orphan*/ ) ; 
 void* ReverseWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorInverse (scalar_t__*) ; 
 int /*<<< orphan*/  WindingPlane (int /*<<< orphan*/ *,scalar_t__*,float*) ; 
 double fabs (scalar_t__) ; 
 TYPE_2__* mapplanes ; 

void AAS_CheckFaceWindingPlane(tmp_face_t *face)
{
	float dist, sign1, sign2;
	vec3_t normal;
	plane_t *plane;
	winding_t *w;

	//check if the winding plane is the same as the face plane
	WindingPlane(face->winding, normal, &dist);
	plane = &mapplanes[face->planenum];
	//
	sign1 = DotProduct(plane->normal, normal);
	//
	if (fabs(dist - plane->dist) > 0.4 ||
			fabs(normal[0] - plane->normal[0]) > 0.0001 ||
			fabs(normal[1] - plane->normal[1]) > 0.0001 ||
			fabs(normal[2] - plane->normal[2]) > 0.0001)
	{
		VectorInverse(normal);
		dist = -dist;
		if (fabs(dist - plane->dist) > 0.4 ||
				fabs(normal[0] - plane->normal[0]) > 0.0001 ||
				fabs(normal[1] - plane->normal[1]) > 0.0001 ||
				fabs(normal[2] - plane->normal[2]) > 0.0001)
		{
			Log_Write("AAS_CheckFaceWindingPlane: face %d winding plane unequal to face plane\r\n",
									face->num);
			//
			sign2 = DotProduct(plane->normal, normal);
			if ((sign1 < 0 && sign2 > 0) ||
					(sign1 > 0 && sign2 < 0))
			{
				Log_Write("AAS_CheckFaceWindingPlane: face %d winding reversed\r\n",
									face->num);
				w = face->winding;
				face->winding = ReverseWinding(w);
				FreeWinding(w);
			} //end if
		} //end if
		else
		{
			Log_Write("AAS_CheckFaceWindingPlane: face %d winding reversed\r\n",
									face->num);
			w = face->winding;
			face->winding = ReverseWinding(w);
			FreeWinding(w);
		} //end else
	} //end if
}