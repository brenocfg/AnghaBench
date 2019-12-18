#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_6__ {int facenum; int /*<<< orphan*/ * start; } ;
typedef  TYPE_2__ aas_reachability_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_BSPModelMinsMaxsOrigin (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AAS_OriginOfMoverWithModelNum (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ *,double,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

void MoverBottomCenter(aas_reachability_t *reach, vec3_t bottomcenter)
{
	int modelnum;
	vec3_t mins, maxs, origin, mids;
	vec3_t angles = {0, 0, 0};

	modelnum = reach->facenum & 0x0000FFFF;
	//get some bsp model info
	AAS_BSPModelMinsMaxsOrigin(modelnum, angles, mins, maxs, origin);
	//
	if (!AAS_OriginOfMoverWithModelNum(modelnum, origin))
	{
		botimport.Print(PRT_MESSAGE, "no entity with model %d\n", modelnum);
	} //end if
	//get a point just above the plat in the bottom position
	VectorAdd(mins, maxs, mids);
	VectorMA(origin, 0.5, mids, bottomcenter);
	bottomcenter[2] = reach->start[2];
}