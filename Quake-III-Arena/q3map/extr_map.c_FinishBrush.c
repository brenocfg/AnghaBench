#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_10__ {int entitynum; struct TYPE_10__* next; struct TYPE_10__* original; int /*<<< orphan*/  brushnum; } ;
typedef  TYPE_1__ bspbrush_t ;
struct TYPE_13__ {int contents; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  detail; } ;
struct TYPE_12__ {int /*<<< orphan*/  origin; } ;
struct TYPE_11__ {TYPE_1__* brushes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackSides () ; 
 int /*<<< orphan*/  AddBrushBevels () ; 
 int CONTENTS_AREAPORTAL ; 
 int CONTENTS_MONSTERCLIP ; 
 int CONTENTS_ORIGIN ; 
 int CONTENTS_PLAYERCLIP ; 
 TYPE_1__* CopyBrush (TYPE_4__*) ; 
 int /*<<< orphan*/  CreateBrushWindings (TYPE_4__*) ; 
 int /*<<< orphan*/  SetKeyValue (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (scalar_t__*,double,scalar_t__*) ; 
 int /*<<< orphan*/  _printf (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* buildBrush ; 
 int /*<<< orphan*/  c_detail ; 
 TYPE_3__* entities ; 
 int /*<<< orphan*/  entitySourceBrushes ; 
 TYPE_2__* mapent ; 
 int num_entities ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

bspbrush_t *FinishBrush( void ) {
	bspbrush_t	*b;

	// liquids may need to have extra sides created for back sides
	AddBackSides();

	// create windings for sides and bounds for brush
	if ( !CreateBrushWindings( buildBrush ) ) {
		// don't keep this brush
		return NULL;
	}

	// brushes that will not be visible at all are forced to be detail
	if ( buildBrush->contents & (CONTENTS_PLAYERCLIP|CONTENTS_MONSTERCLIP) )
	{
		buildBrush->detail = qtrue;
		c_detail++;
	}

	//
	// origin brushes are removed, but they set
	// the rotation origin for the rest of the brushes
	// in the entity.  After the entire entity is parsed,
	// the planenums and texinfos will be adjusted for
	// the origin brush
	//
	if ( buildBrush->contents & CONTENTS_ORIGIN )
	{
		char	string[32];
		vec3_t	origin;

		if (num_entities == 1) {
			_printf ("Entity %i, Brush %i: origin brushes not allowed in world\n"
				,  num_entities - 1, entitySourceBrushes);
			return NULL;
		}

		VectorAdd (buildBrush->mins, buildBrush->maxs, origin);
		VectorScale (origin, 0.5, origin);

		sprintf (string, "%i %i %i", (int)origin[0], (int)origin[1], (int)origin[2]);
		SetKeyValue (&entities[num_entities - 1], "origin", string);

		VectorCopy (origin, entities[num_entities - 1].origin);

		// don't keep this brush
		return NULL;
	}

	if ( buildBrush->contents & CONTENTS_AREAPORTAL ) {
		if (num_entities != 1) {
			_printf ("Entity %i, Brush %i: areaportals only allowed in world\n"
				,  num_entities - 1, entitySourceBrushes);
			return NULL;
		}
	}

	AddBrushBevels ();

	// keep it
	b = CopyBrush( buildBrush );

	b->entitynum = num_entities-1;
	b->brushnum = entitySourceBrushes;

	b->original = b;

	b->next = mapent->brushes;
	mapent->brushes = b;

	return b;
}