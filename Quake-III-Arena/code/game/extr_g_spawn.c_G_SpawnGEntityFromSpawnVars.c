#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_11__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_12__ {int /*<<< orphan*/  origin; TYPE_1__ pos; } ;
struct TYPE_14__ {TYPE_3__ r; TYPE_2__ s; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_16__ {size_t integer; } ;
struct TYPE_15__ {int numSpawnVars; int /*<<< orphan*/ ** spawnVars; } ;

/* Variables and functions */
 size_t GT_FFA ; 
 size_t GT_MAX_GAME_TYPE ; 
 size_t GT_SINGLE_PLAYER ; 
 size_t GT_TEAM ; 
 int /*<<< orphan*/  G_CallSpawn (TYPE_4__*) ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_4__*) ; 
 int /*<<< orphan*/  G_ParseField (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* G_Spawn () ; 
 int /*<<< orphan*/  G_SpawnInt (char*,char*,int*) ; 
 scalar_t__ G_SpawnString (char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ g_gametype ; 
 TYPE_5__ level ; 
 char* strstr (char*,char*) ; 

void G_SpawnGEntityFromSpawnVars( void ) {
	int			i;
	gentity_t	*ent;
	char		*s, *value, *gametypeName;
	static char *gametypeNames[] = {"ffa", "tournament", "single", "team", "ctf", "oneflag", "obelisk", "harvester", "teamtournament"};

	// get the next free entity
	ent = G_Spawn();

	for ( i = 0 ; i < level.numSpawnVars ; i++ ) {
		G_ParseField( level.spawnVars[i][0], level.spawnVars[i][1], ent );
	}

	// check for "notsingle" flag
	if ( g_gametype.integer == GT_SINGLE_PLAYER ) {
		G_SpawnInt( "notsingle", "0", &i );
		if ( i ) {
			G_FreeEntity( ent );
			return;
		}
	}
	// check for "notteam" flag (GT_FFA, GT_TOURNAMENT, GT_SINGLE_PLAYER)
	if ( g_gametype.integer >= GT_TEAM ) {
		G_SpawnInt( "notteam", "0", &i );
		if ( i ) {
			G_FreeEntity( ent );
			return;
		}
	} else {
		G_SpawnInt( "notfree", "0", &i );
		if ( i ) {
			G_FreeEntity( ent );
			return;
		}
	}

#ifdef MISSIONPACK
	G_SpawnInt( "notta", "0", &i );
	if ( i ) {
		G_FreeEntity( ent );
		return;
	}
#else
	G_SpawnInt( "notq3a", "0", &i );
	if ( i ) {
		G_FreeEntity( ent );
		return;
	}
#endif

	if( G_SpawnString( "gametype", NULL, &value ) ) {
		if( g_gametype.integer >= GT_FFA && g_gametype.integer < GT_MAX_GAME_TYPE ) {
			gametypeName = gametypeNames[g_gametype.integer];

			s = strstr( value, gametypeName );
			if( !s ) {
				G_FreeEntity( ent );
				return;
			}
		}
	}

	// move editor origin to pos
	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.origin, ent->r.currentOrigin );

	// if we didn't get a classname, don't bother spawning anything
	if ( !G_CallSpawn( ent ) ) {
		G_FreeEntity( ent );
	}
}