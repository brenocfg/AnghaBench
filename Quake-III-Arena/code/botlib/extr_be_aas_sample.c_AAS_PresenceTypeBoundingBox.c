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
struct TYPE_7__ {int member_0; int member_1; int member_2; } ;
typedef  TYPE_1__ vec3_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int PRESENCE_CROUCH ; 
 int PRESENCE_NORMAL ; 
 int /*<<< orphan*/  PRT_FATAL ; 
 int /*<<< orphan*/  VectorCopy (TYPE_1__,TYPE_1__) ; 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void AAS_PresenceTypeBoundingBox(int presencetype, vec3_t mins, vec3_t maxs)
{
	int index;
	//bounding box size for each presence type
	vec3_t boxmins[3] = {{0, 0, 0}, {-15, -15, -24}, {-15, -15, -24}};
	vec3_t boxmaxs[3] = {{0, 0, 0}, { 15,  15,  32}, { 15,  15,   8}};

	if (presencetype == PRESENCE_NORMAL) index = 1;
	else if (presencetype == PRESENCE_CROUCH) index = 2;
	else
	{
		botimport.Print(PRT_FATAL, "AAS_PresenceTypeBoundingBox: unknown presence type\n");
		index = 2;
	} //end if
	VectorCopy(boxmins[index], mins);
	VectorCopy(boxmaxs[index], maxs);
}