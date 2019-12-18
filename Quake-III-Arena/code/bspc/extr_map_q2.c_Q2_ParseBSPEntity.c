#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_6__ {int modelnum; scalar_t__ areaportalnum; int /*<<< orphan*/  origin; scalar_t__ numbrushes; void* firstbrush; } ;
typedef  TYPE_1__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  GetVectorForKey (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q2_ParseBSPBrushes (TYPE_1__*) ; 
 char* ValueForKey (TYPE_1__*,char*) ; 
 int atoi (char*) ; 
 scalar_t__ c_areaportals ; 
 TYPE_1__* entities ; 
 void* nummapbrushes ; 
 int nummapbrushsides ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

qboolean Q2_ParseBSPEntity(int entnum)
{
	entity_t	*mapent;
	char *model;
	int startbrush, startsides;

	startbrush = nummapbrushes;
	startsides = nummapbrushsides;

	mapent = &entities[entnum];//num_entities];
	mapent->firstbrush = nummapbrushes;
	mapent->numbrushes = 0;
	mapent->modelnum = -1;	//-1 = no model

	model = ValueForKey(mapent, "model");
	if (model && strlen(model))
	{
		if (*model != '*')
		{
			Error("Q2_ParseBSPEntity: model number without leading *");
		} //end if
		//get the model number of this entity (skip the leading *)
		mapent->modelnum = atoi(&model[1]);
	} //end if

	GetVectorForKey(mapent, "origin", mapent->origin);

	//if this is the world entity it has model number zero
	//the world entity has no model key
	if (!strcmp("worldspawn", ValueForKey(mapent, "classname")))
	{
		mapent->modelnum = 0;
	} //end if
	//if the map entity has a BSP model (a modelnum of -1 is used for
	//entities that aren't using a BSP model)
	if (mapent->modelnum >= 0)
	{
		//parse the bsp brushes
		Q2_ParseBSPBrushes(mapent);
	} //end if
	//
	//the origin of the entity is already taken into account
	//
	//func_group entities can't be in the bsp file
	//
	//check out the func_areaportal entities
	if (!strcmp ("func_areaportal", ValueForKey (mapent, "classname")))
	{
		c_areaportals++;
		mapent->areaportalnum = c_areaportals;
		return true;
	} //end if
	return true;
}