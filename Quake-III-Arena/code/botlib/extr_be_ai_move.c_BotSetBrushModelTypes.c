#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*) ;} ;

/* Variables and functions */
 int AAS_NextBSPEntity (int) ; 
 int /*<<< orphan*/  AAS_ValueForBSPEpairKey (int,char*,char*,int) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int MAX_EPAIRKEY ; 
 int MAX_MODELS ; 
 int /*<<< orphan*/  MODELTYPE_FUNC_BOB ; 
 int /*<<< orphan*/  MODELTYPE_FUNC_DOOR ; 
 int /*<<< orphan*/  MODELTYPE_FUNC_PLAT ; 
 int /*<<< orphan*/  MODELTYPE_FUNC_STATIC ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int atoi (char*) ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/ * modeltypes ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 

void BotSetBrushModelTypes(void)
{
	int ent, modelnum;
	char classname[MAX_EPAIRKEY], model[MAX_EPAIRKEY];

	Com_Memset(modeltypes, 0, MAX_MODELS * sizeof(int));
	//
	for (ent = AAS_NextBSPEntity(0); ent; ent = AAS_NextBSPEntity(ent))
	{
		if (!AAS_ValueForBSPEpairKey(ent, "classname", classname, MAX_EPAIRKEY)) continue;
		if (!AAS_ValueForBSPEpairKey(ent, "model", model, MAX_EPAIRKEY)) continue;
		if (model[0]) modelnum = atoi(model+1);
		else modelnum = 0;

		if (modelnum < 0 || modelnum > MAX_MODELS)
		{
			botimport.Print(PRT_MESSAGE, "entity %s model number out of range\n", classname);
			continue;
		} //end if

		if (!Q_stricmp(classname, "func_bobbing"))
			modeltypes[modelnum] = MODELTYPE_FUNC_BOB;
		else if (!Q_stricmp(classname, "func_plat"))
			modeltypes[modelnum] = MODELTYPE_FUNC_PLAT;
		else if (!Q_stricmp(classname, "func_door"))
			modeltypes[modelnum] = MODELTYPE_FUNC_DOOR;
		else if (!Q_stricmp(classname, "func_static"))
			modeltypes[modelnum] = MODELTYPE_FUNC_STATIC;
	} //end for
}