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
struct TYPE_5__ {struct TYPE_5__** prev; struct TYPE_5__** next; TYPE_2__* frontarea; TYPE_2__* backarea; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_6__ {TYPE_1__* tmpfaces; } ;
typedef  TYPE_2__ tmp_area_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 

void AAS_AddFaceSideToArea(tmp_face_t *tmpface, int side, tmp_area_t *tmparea)
{
	int tmpfaceside;

	if (side)
	{
		if (tmpface->backarea) Error("AAS_AddFaceSideToArea: already a back area\n");
	} //end if
	else
	{
		if (tmpface->frontarea) Error("AAS_AddFaceSideToArea: already a front area\n");
	} //end else

	if (side) tmpface->backarea = tmparea;
	else tmpface->frontarea = tmparea;

	if (tmparea->tmpfaces)
	{
		tmpfaceside = tmparea->tmpfaces->frontarea != tmparea;
		tmparea->tmpfaces->prev[tmpfaceside] = tmpface;
	} //end if
	tmpface->next[side] = tmparea->tmpfaces;
	tmpface->prev[side] = NULL;
	tmparea->tmpfaces = tmpface;
}