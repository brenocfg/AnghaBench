#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* next; } ;
typedef  TYPE_2__ th_triangle_t ;
struct TYPE_12__ {int faceflags; } ;
typedef  TYPE_3__ aas_face_t ;
struct TYPE_13__ {int numareas; TYPE_3__* faces; TYPE_1__* areas; int /*<<< orphan*/ * faceindex; } ;
struct TYPE_10__ {int numfaces; int firstface; } ;

/* Variables and functions */
 int FACE_SOLID ; 
 int /*<<< orphan*/  TH_AddTriangleToList (TYPE_2__**,TYPE_2__*) ; 
 TYPE_2__* TH_CreateAASFaceTriangles (TYPE_3__*) ; 
 TYPE_4__ aasworld ; 
 int abs (int /*<<< orphan*/ ) ; 

th_triangle_t *TH_AASToTriangleMesh(void)
{
	int i, j, facenum, otherareanum;
	aas_face_t *face;
	th_triangle_t *tri, *nexttri, *triangles;

	triangles = NULL;
	for (i = 1; i < aasworld.numareas; i++)
	{
		//if (!(aasworld.areasettings[i].presencetype & PRESENCE_NORMAL)) continue;
		for (j = 0; j < aasworld.areas[i].numfaces; j++)
		{
			facenum = abs(aasworld.faceindex[aasworld.areas[i].firstface + j]);
			face = &aasworld.faces[facenum];
			//only convert solid faces into triangles
			if (!(face->faceflags & FACE_SOLID))
			{
				/*
				if (face->frontarea == i) otherareanum = face->backarea;
				else otherareanum = face->frontarea;
				if (aasworld.areasettings[otherareanum].presencetype & PRESENCE_NORMAL) continue;
				*/
				continue;
			} //end if
			//
			tri = TH_CreateAASFaceTriangles(face);
			for (; tri; tri = nexttri)
			{
				nexttri = tri->next;
				TH_AddTriangleToList(&triangles, tri);
			} //end for
		} //end if
	} //end for
	return triangles;
}