#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_5__ {int planenum; int /*<<< orphan*/ * winding; int /*<<< orphan*/ * backarea; int /*<<< orphan*/ * frontarea; } ;
typedef  TYPE_1__ tmp_face_t ;
typedef  int /*<<< orphan*/  tmp_area_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AddFaceSideToArea (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AAS_RemoveFaceFromArea (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReverseWinding (int /*<<< orphan*/ *) ; 

void AAS_FlipFace(tmp_face_t *face)
{
	tmp_area_t *frontarea, *backarea;
	winding_t *w;

	frontarea = face->frontarea;
	backarea = face->backarea;
	//must have an area at both sides before flipping is allowed
	if (!frontarea || !backarea) return;
	//flip the face winding
	w = face->winding;
	face->winding = ReverseWinding(w);
	FreeWinding(w);
	//flip the face plane
	face->planenum ^= 1;
	//flip the face areas
	AAS_RemoveFaceFromArea(face, frontarea);
	AAS_RemoveFaceFromArea(face, backarea);
	AAS_AddFaceSideToArea(face, 1, frontarea);
	AAS_AddFaceSideToArea(face, 0, backarea);
}