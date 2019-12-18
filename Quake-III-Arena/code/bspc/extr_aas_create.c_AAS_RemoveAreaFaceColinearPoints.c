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
struct TYPE_4__ {int /*<<< orphan*/  winding; TYPE_2__* frontarea; struct TYPE_4__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_5__ {TYPE_1__* tmpfaces; struct TYPE_5__* l_next; } ;
typedef  TYPE_2__ tmp_area_t ;
struct TYPE_6__ {TYPE_2__* areas; } ;

/* Variables and functions */
 int /*<<< orphan*/  RemoveColinearPoints (int /*<<< orphan*/ ) ; 
 TYPE_3__ tmpaasworld ; 

void AAS_RemoveAreaFaceColinearPoints(void)
{
	int side;
	tmp_face_t *face;
	tmp_area_t *tmparea;

	//FIXME: loop over the faces instead of area->faces
	for (tmparea = tmpaasworld.areas; tmparea; tmparea = tmparea->l_next)
	{
		for (face = tmparea->tmpfaces; face; face = face->next[side])
		{
			side = face->frontarea != tmparea;
			RemoveColinearPoints(face->winding);
//			RemoveEqualPoints(face->winding, 0.1);
		} //end for
	} //end for
}