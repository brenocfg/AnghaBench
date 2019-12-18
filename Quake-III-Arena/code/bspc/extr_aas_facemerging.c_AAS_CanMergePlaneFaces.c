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
struct TYPE_4__ {int planenum; int faceflags; TYPE_2__* backarea; TYPE_2__* frontarea; struct TYPE_4__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_5__ {TYPE_1__* tmpfaces; } ;
typedef  TYPE_2__ tmp_area_t ;

/* Variables and functions */

int AAS_CanMergePlaneFaces(tmp_area_t *tmparea, int planenum)
{
	tmp_area_t *frontarea, *backarea;
	tmp_face_t *face1;
	int side1, merge, faceflags;

	frontarea = backarea = NULL;
	merge = false;
	for (face1 = tmparea->tmpfaces; face1; face1 = face1->next[side1])
	{
		side1 = face1->frontarea != tmparea;
		if ((face1->planenum & ~1) != (planenum & ~1)) continue;
		if (!frontarea && !backarea)
		{
			frontarea = face1->frontarea;
			backarea = face1->backarea;
			faceflags = face1->faceflags;
		} //end if
		else
		{
			if (frontarea != face1->frontarea) return false;
			if (backarea != face1->backarea) return false;
			if (faceflags != face1->faceflags) return false;
			merge = true;
		} //end else
	} //end for
	return merge;
}