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
struct TYPE_4__ {struct TYPE_4__* l_next; } ;
typedef  TYPE_1__ tmp_area_t ;
struct TYPE_5__ {TYPE_1__* areas; } ;

/* Variables and functions */
 scalar_t__ AAS_MeltFaceWindingsOfArea (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 TYPE_2__ tmpaasworld ; 

void AAS_MeltAreaFaceWindings(void)
{
	tmp_area_t *tmparea;
	int num_windingsplits = 0;

	Log_Write("AAS_MeltAreaFaceWindings\r\n");
	qprintf("%6d edges melted", num_windingsplits);
	//NOTE: first convex area (zero) is a dummy
	for (tmparea = tmpaasworld.areas; tmparea; tmparea = tmparea->l_next)
	{
		num_windingsplits += AAS_MeltFaceWindingsOfArea(tmparea);
		qprintf("\r%6d", num_windingsplits);
	} //end for
	qprintf("\n");
	Log_Write("%6d edges melted\r\n", num_windingsplits);
}