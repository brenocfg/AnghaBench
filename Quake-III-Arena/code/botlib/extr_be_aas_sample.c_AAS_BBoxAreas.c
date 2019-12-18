#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {int areanum; struct TYPE_4__* next_area; } ;
typedef  TYPE_1__ aas_link_t ;

/* Variables and functions */
 TYPE_1__* AAS_AASLinkEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AAS_UnlinkFromAreas (TYPE_1__*) ; 

int AAS_BBoxAreas(vec3_t absmins, vec3_t absmaxs, int *areas, int maxareas)
{
	aas_link_t *linkedareas, *link;
	int num;

	linkedareas = AAS_AASLinkEntity(absmins, absmaxs, -1);
	num = 0;
	for (link = linkedareas; link; link = link->next_area)
	{
		areas[num] = link->areanum;
		num++;
		if (num >= maxareas)
			break;
	} //end for
	AAS_UnlinkFromAreas(linkedareas);
	return num;
}