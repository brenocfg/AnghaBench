#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_33__ {scalar_t__* origin; scalar_t__* angles; TYPE_8__* ent; int /*<<< orphan*/  deltayaw; } ;
typedef  TYPE_7__ pushed_t ;
struct TYPE_28__ {scalar_t__ trType; scalar_t__* trBase; } ;
struct TYPE_27__ {scalar_t__ trType; scalar_t__* trBase; } ;
struct TYPE_32__ {scalar_t__ eType; scalar_t__ groundEntityNum; scalar_t__ number; TYPE_2__ apos; TYPE_1__ pos; scalar_t__ loopSound; } ;
struct TYPE_31__ {scalar_t__* currentAngles; scalar_t__* currentOrigin; scalar_t__* absmin; scalar_t__* absmax; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
struct TYPE_34__ {TYPE_4__* client; TYPE_6__ s; TYPE_5__ r; int /*<<< orphan*/  physicsObject; int /*<<< orphan*/ * activator; struct TYPE_34__* enemy; int /*<<< orphan*/  classname; } ;
typedef  TYPE_8__ gentity_t ;
struct TYPE_29__ {scalar_t__* origin; int /*<<< orphan*/ * delta_angles; } ;
struct TYPE_30__ {TYPE_3__ ps; } ;

/* Variables and functions */
 scalar_t__ ET_ITEM ; 
 scalar_t__ ET_MISSILE ; 
 scalar_t__ ET_PLAYER ; 
 int /*<<< orphan*/  EV_PROXIMITY_MINE_TRIGGER ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CheckProxMinePosition (TYPE_8__*) ; 
 int /*<<< orphan*/  G_Damage (TYPE_8__*,TYPE_8__*,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_ExplodeMissile (TYPE_8__*) ; 
 int /*<<< orphan*/  G_FreeEntity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_TestEntityPosition (TYPE_8__*) ; 
 scalar_t__ G_TryPushingEntity (TYPE_8__*,TYPE_8__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  G_TryPushingProxMine (TYPE_8__*,TYPE_8__*,scalar_t__*,scalar_t__*) ; 
 int MAX_GENTITIES ; 
 int /*<<< orphan*/  MOD_CRUSH ; 
 float RadiusFromBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TR_SINE ; 
 int /*<<< orphan*/  VectorAdd (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 size_t YAW ; 
 TYPE_8__* g_entities ; 
 TYPE_7__* pushed ; 
 TYPE_7__* pushed_p ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int trap_EntitiesInBox (scalar_t__*,scalar_t__*,int*,int) ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_8__*) ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_8__*) ; 

qboolean G_MoverPush( gentity_t *pusher, vec3_t move, vec3_t amove, gentity_t **obstacle ) {
	int			i, e;
	gentity_t	*check;
	vec3_t		mins, maxs;
	pushed_t	*p;
	int			entityList[MAX_GENTITIES];
	int			listedEntities;
	vec3_t		totalMins, totalMaxs;

	*obstacle = NULL;


	// mins/maxs are the bounds at the destination
	// totalMins / totalMaxs are the bounds for the entire move
	if ( pusher->r.currentAngles[0] || pusher->r.currentAngles[1] || pusher->r.currentAngles[2]
		|| amove[0] || amove[1] || amove[2] ) {
		float		radius;

		radius = RadiusFromBounds( pusher->r.mins, pusher->r.maxs );
		for ( i = 0 ; i < 3 ; i++ ) {
			mins[i] = pusher->r.currentOrigin[i] + move[i] - radius;
			maxs[i] = pusher->r.currentOrigin[i] + move[i] + radius;
			totalMins[i] = mins[i] - move[i];
			totalMaxs[i] = maxs[i] - move[i];
		}
	} else {
		for (i=0 ; i<3 ; i++) {
			mins[i] = pusher->r.absmin[i] + move[i];
			maxs[i] = pusher->r.absmax[i] + move[i];
		}

		VectorCopy( pusher->r.absmin, totalMins );
		VectorCopy( pusher->r.absmax, totalMaxs );
		for (i=0 ; i<3 ; i++) {
			if ( move[i] > 0 ) {
				totalMaxs[i] += move[i];
			} else {
				totalMins[i] += move[i];
			}
		}
	}

	// unlink the pusher so we don't get it in the entityList
	trap_UnlinkEntity( pusher );

	listedEntities = trap_EntitiesInBox( totalMins, totalMaxs, entityList, MAX_GENTITIES );

	// move the pusher to it's final position
	VectorAdd( pusher->r.currentOrigin, move, pusher->r.currentOrigin );
	VectorAdd( pusher->r.currentAngles, amove, pusher->r.currentAngles );
	trap_LinkEntity( pusher );

	// see if any solid entities are inside the final position
	for ( e = 0 ; e < listedEntities ; e++ ) {
		check = &g_entities[ entityList[ e ] ];

#ifdef MISSIONPACK
		if ( check->s.eType == ET_MISSILE ) {
			// if it is a prox mine
			if ( !strcmp(check->classname, "prox mine") ) {
				// if this prox mine is attached to this mover try to move it with the pusher
				if ( check->enemy == pusher ) {
					if (!G_TryPushingProxMine( check, pusher, move, amove )) {
						//explode
						check->s.loopSound = 0;
						G_AddEvent( check, EV_PROXIMITY_MINE_TRIGGER, 0 );
						G_ExplodeMissile(check);
						if (check->activator) {
							G_FreeEntity(check->activator);
							check->activator = NULL;
						}
						//G_Printf("prox mine explodes\n");
					}
				}
				else {
					//check if the prox mine is crushed by the mover
					if (!G_CheckProxMinePosition( check )) {
						//explode
						check->s.loopSound = 0;
						G_AddEvent( check, EV_PROXIMITY_MINE_TRIGGER, 0 );
						G_ExplodeMissile(check);
						if (check->activator) {
							G_FreeEntity(check->activator);
							check->activator = NULL;
						}
						//G_Printf("prox mine explodes\n");
					}
				}
				continue;
			}
		}
#endif
		// only push items and players
		if ( check->s.eType != ET_ITEM && check->s.eType != ET_PLAYER && !check->physicsObject ) {
			continue;
		}

		// if the entity is standing on the pusher, it will definitely be moved
		if ( check->s.groundEntityNum != pusher->s.number ) {
			// see if the ent needs to be tested
			if ( check->r.absmin[0] >= maxs[0]
			|| check->r.absmin[1] >= maxs[1]
			|| check->r.absmin[2] >= maxs[2]
			|| check->r.absmax[0] <= mins[0]
			|| check->r.absmax[1] <= mins[1]
			|| check->r.absmax[2] <= mins[2] ) {
				continue;
			}
			// see if the ent's bbox is inside the pusher's final position
			// this does allow a fast moving object to pass through a thin entity...
			if (!G_TestEntityPosition (check)) {
				continue;
			}
		}

		// the entity needs to be pushed
		if ( G_TryPushingEntity( check, pusher, move, amove ) ) {
			continue;
		}

		// the move was blocked an entity

		// bobbing entities are instant-kill and never get blocked
		if ( pusher->s.pos.trType == TR_SINE || pusher->s.apos.trType == TR_SINE ) {
			G_Damage( check, pusher, pusher, NULL, NULL, 99999, 0, MOD_CRUSH );
			continue;
		}

		
		// save off the obstacle so we can call the block function (crush, etc)
		*obstacle = check;

		// move back any entities we already moved
		// go backwards, so if the same entity was pushed
		// twice, it goes back to the original position
		for ( p=pushed_p-1 ; p>=pushed ; p-- ) {
			VectorCopy (p->origin, p->ent->s.pos.trBase);
			VectorCopy (p->angles, p->ent->s.apos.trBase);
			if ( p->ent->client ) {
				p->ent->client->ps.delta_angles[YAW] = p->deltayaw;
				VectorCopy (p->origin, p->ent->client->ps.origin);
			}
			trap_LinkEntity (p->ent);
		}
		return qfalse;
	}

	return qtrue;
}