#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
struct TYPE_20__ {char* string; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_21__ {size_t planenum; int /*<<< orphan*/  texinfo; } ;
typedef  TYPE_2__ side_t ;
typedef  int /*<<< orphan*/  script_t ;
typedef  int qboolean ;
struct TYPE_22__ {int numsides; int /*<<< orphan*/  contents; TYPE_2__* original_sides; } ;
typedef  TYPE_3__ mapbrush_t ;
struct TYPE_23__ {struct TYPE_23__* next; } ;
typedef  TYPE_4__ epair_t ;
struct TYPE_24__ {int firstbrush; int numbrushes; int areaportalnum; scalar_t__* origin; TYPE_4__* epairs; } ;
typedef  TYPE_5__ entity_t ;
struct TYPE_25__ {int /*<<< orphan*/  normal; scalar_t__ dist; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENTS_AREAPORTAL ; 
 scalar_t__ DotProduct (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 size_t FindFloatPlane (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GetVectorForKey (TYPE_5__*,char*,scalar_t__*) ; 
 size_t MAX_MAP_ENTITIES ; 
 int /*<<< orphan*/  MakeBrushWindings (TYPE_3__*) ; 
 int /*<<< orphan*/  PS_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PS_UnreadLastToken (int /*<<< orphan*/ *) ; 
 TYPE_4__* ParseEpair (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q2_MoveBrushesToWorld (TYPE_5__*) ; 
 int /*<<< orphan*/  Q2_ParseBrush (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  SetKeyValue (TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  TexinfoForBrushTexture (TYPE_7__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 char* ValueForKey (TYPE_5__*,char*) ; 
 TYPE_2__* brushsides ; 
 int c_areaportals ; 
 TYPE_5__* entities ; 
 TYPE_3__* mapbrushes ; 
 TYPE_7__* mapplanes ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 size_t num_entities ; 
 int nummapbrushes ; 
 int nummapbrushsides ; 
 int /*<<< orphan*/ * side_brushtextures ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

qboolean	Q2_ParseMapEntity(script_t *script)
{
	entity_t	*mapent;
	epair_t *e;
	side_t *s;
	int i, j;
	int startbrush, startsides;
	vec_t newdist;
	mapbrush_t *b;
	token_t token;

	if (!PS_ReadToken(script, &token)) return false;

	if (strcmp(token.string, "{") )
		Error ("ParseEntity: { not found");
	
	if (num_entities == MAX_MAP_ENTITIES)
		Error ("num_entities == MAX_MAP_ENTITIES");

	startbrush = nummapbrushes;
	startsides = nummapbrushsides;

	mapent = &entities[num_entities];
	num_entities++;
	memset (mapent, 0, sizeof(*mapent));
	mapent->firstbrush = nummapbrushes;
	mapent->numbrushes = 0;
//	mapent->portalareas[0] = -1;
//	mapent->portalareas[1] = -1;

	do
	{
		if (!PS_ReadToken(script, &token))
		{
			Error("ParseEntity: EOF without closing brace");
		} //end if
		if (!strcmp(token.string, "}")) break;
		if (!strcmp(token.string, "{"))
		{
			Q2_ParseBrush(script, mapent);
		} //end if
		else
		{
			PS_UnreadLastToken(script);
			e = ParseEpair(script);
			e->next = mapent->epairs;
			mapent->epairs = e;
		} //end else
	} while(1);

	GetVectorForKey(mapent, "origin", mapent->origin);

	//
	// if there was an origin brush, offset all of the planes and texinfo
	//
	if (mapent->origin[0] || mapent->origin[1] || mapent->origin[2])
	{
		for (i=0 ; i<mapent->numbrushes ; i++)
		{
			b = &mapbrushes[mapent->firstbrush + i];
			for (j=0 ; j<b->numsides ; j++)
			{
				s = &b->original_sides[j];
				newdist = mapplanes[s->planenum].dist -
					DotProduct (mapplanes[s->planenum].normal, mapent->origin);
				s->planenum = FindFloatPlane (mapplanes[s->planenum].normal, newdist);
				s->texinfo = TexinfoForBrushTexture (&mapplanes[s->planenum],
					&side_brushtextures[s-brushsides], mapent->origin);
			}
			MakeBrushWindings (b);
		}
	}

	// group entities are just for editor convenience
	// toss all brushes into the world entity
	if (!strcmp ("func_group", ValueForKey (mapent, "classname")))
	{
		Q2_MoveBrushesToWorld (mapent);
		mapent->numbrushes = 0;
		return true;
	}

	// areaportal entities move their brushes, but don't eliminate
	// the entity
	if (!strcmp ("func_areaportal", ValueForKey (mapent, "classname")))
	{
		char	str[128];

		if (mapent->numbrushes != 1)
			Error ("Entity %i: func_areaportal can only be a single brush", num_entities-1);

		b = &mapbrushes[nummapbrushes-1];
		b->contents = CONTENTS_AREAPORTAL;
		c_areaportals++;
		mapent->areaportalnum = c_areaportals;
		// set the portal number as "style"
		sprintf (str, "%i", c_areaportals);
		SetKeyValue (mapent, "style", str);
		Q2_MoveBrushesToWorld (mapent);
		return true;
	}

	return true;
}