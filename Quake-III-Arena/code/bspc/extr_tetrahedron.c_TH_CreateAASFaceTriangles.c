#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {int front; } ;
typedef  TYPE_1__ th_triangle_t ;
struct TYPE_11__ {int numedges; } ;
typedef  TYPE_2__ aas_face_t ;
struct TYPE_12__ {TYPE_1__* triangles; } ;

/* Variables and functions */
 int /*<<< orphan*/  TH_AASFaceVertex (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TH_AddTriangleToList (TYPE_1__**,TYPE_1__*) ; 
 scalar_t__ TH_Colinear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TH_CreateTriangle (int*) ; 
 int /*<<< orphan*/  TH_FaceCenter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int TH_FindOrCreateVertex (int /*<<< orphan*/ ) ; 
 TYPE_3__ thworld ; 

th_triangle_t *TH_CreateAASFaceTriangles(aas_face_t *face)
{
	int i, first, verts[3], trinum;
	vec3_t p0, p1, p2, p3, p4, center;
	th_triangle_t *tri, *triangles;

	triangles = NULL;
	//find three points that are not colinear
	for (i = 0; i < face->numedges; i++)
	{
		TH_AASFaceVertex(face, (face->numedges + i-2)%face->numedges, p0);
		TH_AASFaceVertex(face, (face->numedges + i-1)%face->numedges, p1);
		TH_AASFaceVertex(face, (i  )%face->numedges, p2);
		if (TH_Colinear(p2, p0, p1)) continue;
		TH_AASFaceVertex(face, (i+1)%face->numedges, p3);
		TH_AASFaceVertex(face, (i+2)%face->numedges, p4);
		if (TH_Colinear(p2, p3, p4)) continue;
		break;
	} //end for
	//if there are three points that are not colinear
	if (i < face->numedges)
	{
		//normal triangulation
		first = i; //left and right most point of three non-colinear points
		TH_AASFaceVertex(face, first, p0);
		verts[0] = TH_FindOrCreateVertex(p0);
		for (i = 1; i < face->numedges-1; i++)
		{
			TH_AASFaceVertex(face, (first+i  )%face->numedges, p1);
			TH_AASFaceVertex(face, (first+i+1)%face->numedges, p2);
			verts[1] = TH_FindOrCreateVertex(p1);
			verts[2] = TH_FindOrCreateVertex(p2);
			trinum = TH_CreateTriangle(verts);
			tri = &thworld.triangles[trinum];
			tri->front = -1;
			TH_AddTriangleToList(&triangles, tri);
		} //end for
	} //end if
	else
	{
		//fan triangulation
		TH_FaceCenter(face, center);
		//
		verts[0] = TH_FindOrCreateVertex(center);
		for (i = 0; i < face->numedges; i++)
		{
			TH_AASFaceVertex(face, (i  )%face->numedges, p1);
			TH_AASFaceVertex(face, (i+1)%face->numedges, p2);
			if (TH_Colinear(center, p1, p2)) continue;
			verts[1] = TH_FindOrCreateVertex(p1);
			verts[2] = TH_FindOrCreateVertex(p2);
			trinum = TH_CreateTriangle(verts);
			tri = &thworld.triangles[trinum];
			tri->front = -1;
			TH_AddTriangleToList(&triangles, tri);
		} //end for
	} //end else
	return triangles;
}