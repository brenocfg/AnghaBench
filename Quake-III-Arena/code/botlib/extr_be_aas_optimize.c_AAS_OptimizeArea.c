#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int faceindexsize; int* faceindex; TYPE_2__* areas; } ;
typedef  TYPE_1__ optimized_t ;
struct TYPE_9__ {int numfaces; int firstface; } ;
typedef  TYPE_2__ aas_area_t ;
struct TYPE_10__ {int* faceindex; TYPE_2__* areas; } ;

/* Variables and functions */
 int AAS_OptimizeFace (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Com_Memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_3__ aasworld ; 

void AAS_OptimizeArea(optimized_t *optimized, int areanum)
{
	int i, facenum, optfacenum;
	aas_area_t *area, *optarea;

	area = &aasworld.areas[areanum];
	optarea = &optimized->areas[areanum];
	Com_Memcpy(optarea, area, sizeof(aas_area_t));

	optarea->numfaces = 0;
	optarea->firstface = optimized->faceindexsize;
	for (i = 0; i < area->numfaces; i++)
	{
		facenum = aasworld.faceindex[area->firstface + i];
		optfacenum = AAS_OptimizeFace(optimized, facenum);
		if (optfacenum)
		{
			optimized->faceindex[optarea->firstface + optarea->numfaces] = optfacenum;
			optarea->numfaces++;
			optimized->faceindexsize++;
		} //end if
	} //end for
}