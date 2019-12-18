#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_7__ {scalar_t__ faceflags; scalar_t__ frontarea; scalar_t__ backarea; size_t planenum; int /*<<< orphan*/  num; int /*<<< orphan*/ * winding; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_8__ {int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_FreeTmpFace (TYPE_1__*) ; 
 int /*<<< orphan*/  AAS_RemoveFaceFromArea (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_Write (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MergeWindings (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TryMergeWinding (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* mapplanes ; 

int AAS_TryMergeFaces(tmp_face_t *face1, tmp_face_t *face2)
{
	winding_t *neww;

#ifdef DEBUG
	if (!face1->winding) Error("face1 %d without winding", face1->num);
	if (!face2->winding) Error("face2 %d without winding", face2->num);
#endif //DEBUG
	//
	if (face1->faceflags != face2->faceflags) return false;
	//NOTE: if the front or back area is zero this doesn't mean there's
	//a real area. It means there's solid at that side of the face
	//if both faces have the same front area
	if (face1->frontarea == face2->frontarea)
	{
		//if both faces have the same back area
		if (face1->backarea == face2->backarea)
		{
			//if the faces are in the same plane
			if (face1->planenum == face2->planenum)
			{
				//if they have both a front and a back area (no solid on either side)
				if (face1->frontarea && face1->backarea)
				{
					neww = MergeWindings(face1->winding, face2->winding,
								mapplanes[face1->planenum].normal);
				} //end if
				else
				{
					//this function is to be found in l_poly.c
					neww = TryMergeWinding(face1->winding, face2->winding,
									mapplanes[face1->planenum].normal);
				} //end else
				if (neww)
				{
					FreeWinding(face1->winding);
					face1->winding = neww;
					if (face2->frontarea) AAS_RemoveFaceFromArea(face2, face2->frontarea);
					if (face2->backarea) AAS_RemoveFaceFromArea(face2, face2->backarea);
					AAS_FreeTmpFace(face2);
					return true;
				} //end if
			} //end if
			else if ((face1->planenum & ~1) == (face2->planenum & ~1))
			{
				Log_Write("face %d and %d, same front and back area but flipped planes\r\n",
							face1->num, face2->num);
			} //end if
		} //end if
	} //end if
	return false;
}