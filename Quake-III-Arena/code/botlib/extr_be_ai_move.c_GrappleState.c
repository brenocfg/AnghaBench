#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int moveflags; } ;
typedef  TYPE_1__ bot_movestate_t ;
typedef  int /*<<< orphan*/  aas_reachability_t ;
struct TYPE_8__ {int weapon; } ;
typedef  TYPE_2__ aas_entityinfo_t ;
struct TYPE_10__ {scalar_t__ value; } ;
struct TYPE_9__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_EntityInfo (int,TYPE_2__*) ; 
 int AAS_EntityType (int) ; 
 int AAS_NextEntity (int) ; 
 int MFL_GRAPPLEPULL ; 
 TYPE_4__* entitytypemissile ; 
 TYPE_3__* weapindex_grapple ; 

int GrappleState(bot_movestate_t *ms, aas_reachability_t *reach)
{
	int i;
	aas_entityinfo_t entinfo;

	//if the grapple hook is pulling
	if (ms->moveflags & MFL_GRAPPLEPULL)
		return 2;
	//check for a visible grapple missile entity
	//or visible grapple entity
	for (i = AAS_NextEntity(0); i; i = AAS_NextEntity(i))
	{
		if (AAS_EntityType(i) == (int) entitytypemissile->value)
		{
			AAS_EntityInfo(i, &entinfo);
			if (entinfo.weapon == (int) weapindex_grapple->value)
			{
				return 1;
			} //end if
		} //end if
	} //end for
	//no valid grapple at all
	return 0;
}