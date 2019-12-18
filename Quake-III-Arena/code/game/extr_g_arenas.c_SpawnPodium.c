#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_11__ {int /*<<< orphan*/ * trBase; } ;
struct TYPE_12__ {TYPE_2__ apos; int /*<<< orphan*/  modelindex; TYPE_4__* number; int /*<<< orphan*/  eType; } ;
struct TYPE_10__ {int /*<<< orphan*/  currentOrigin; void* contents; } ;
struct TYPE_13__ {char* classname; scalar_t__ nextthink; int /*<<< orphan*/  think; TYPE_3__ s; TYPE_1__ r; void* clipmask; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_14__ {scalar_t__ time; int /*<<< orphan*/  intermission_origin; int /*<<< orphan*/  intermission_angle; } ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* CONTENTS_SOLID ; 
 int /*<<< orphan*/  ET_GENERAL ; 
 int /*<<< orphan*/  G_ModelIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SetOrigin (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* G_Spawn () ; 
 int /*<<< orphan*/  PodiumPlacementThink ; 
 int /*<<< orphan*/  SP_PODIUM_MODEL ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t YAW ; 
 int g_entities ; 
 TYPE_6__ level ; 
 scalar_t__ trap_Cvar_VariableIntegerValue (char*) ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_4__*) ; 
 int /*<<< orphan*/  vectoyaw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gentity_t *SpawnPodium( void ) {
	gentity_t	*podium;
	vec3_t		vec;
	vec3_t		origin;

	podium = G_Spawn();
	if ( !podium ) {
		return NULL;
	}

	podium->classname = "podium";
	podium->s.eType = ET_GENERAL;
	podium->s.number = podium - g_entities;
	podium->clipmask = CONTENTS_SOLID;
	podium->r.contents = CONTENTS_SOLID;
	podium->s.modelindex = G_ModelIndex( SP_PODIUM_MODEL );

	AngleVectors( level.intermission_angle, vec, NULL, NULL );
	VectorMA( level.intermission_origin, trap_Cvar_VariableIntegerValue( "g_podiumDist" ), vec, origin );
	origin[2] -= trap_Cvar_VariableIntegerValue( "g_podiumDrop" );
	G_SetOrigin( podium, origin );

	VectorSubtract( level.intermission_origin, podium->r.currentOrigin, vec );
	podium->s.apos.trBase[YAW] = vectoyaw( vec );
	trap_LinkEntity (podium);

	podium->think = PodiumPlacementThink;
	podium->nextthink = level.time + 100;
	return podium;
}