#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_29__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_35__ {int* normal; } ;
struct TYPE_39__ {size_t entityNum; int* endpos; int surfaceFlags; TYPE_3__ plane; } ;
typedef  TYPE_7__ trace_t ;
typedef  void* qboolean ;
struct TYPE_38__ {size_t ownerNum; double* mins; double* maxs; int* currentOrigin; } ;
struct TYPE_33__ {int* trDelta; scalar_t__ trType; int /*<<< orphan*/  trBase; } ;
struct TYPE_36__ {int eFlags; scalar_t__ weapon; scalar_t__ eType; int* angles; TYPE_29__ pos; int /*<<< orphan*/  number; int /*<<< orphan*/  otherEntityNum; int /*<<< orphan*/  origin; } ;
struct TYPE_40__ {scalar_t__ health; scalar_t__ nextthink; int* movedir; TYPE_5__* client; TYPE_6__ r; int /*<<< orphan*/  splashMethodOfDeath; int /*<<< orphan*/  splashRadius; scalar_t__ splashDamage; TYPE_18__* parent; TYPE_4__ s; void* freeAfterEvent; scalar_t__ takedamage; int /*<<< orphan*/  think; struct TYPE_40__* enemy; int /*<<< orphan*/  classname; int /*<<< orphan*/  die; int /*<<< orphan*/  methodOfDeath; scalar_t__ damage; struct TYPE_40__* target_ent; } ;
typedef  TYPE_8__ gentity_t ;
struct TYPE_37__ {scalar_t__ invulnerabilityTime; int /*<<< orphan*/  accuracy_hits; } ;
struct TYPE_32__ {int* grapplePoint; int /*<<< orphan*/  pm_flags; } ;
struct TYPE_34__ {TYPE_1__ ps; } ;
struct TYPE_31__ {TYPE_2__* client; } ;
struct TYPE_30__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectoryDelta (TYPE_29__*,scalar_t__,int*) ; 
 int DirToByte (int*) ; 
 int EF_BOUNCE ; 
 int EF_BOUNCE_HALF ; 
 void* ET_GENERAL ; 
 scalar_t__ ET_GRAPPLE ; 
 scalar_t__ ET_PLAYER ; 
 int /*<<< orphan*/  EV_GRENADE_BOUNCE ; 
 int /*<<< orphan*/  EV_MISSILE_HIT ; 
 int /*<<< orphan*/  EV_MISSILE_MISS ; 
 int /*<<< orphan*/  EV_MISSILE_MISS_METAL ; 
 int /*<<< orphan*/  EV_PROXIMITY_MINE_STICK ; 
 scalar_t__ FRAMETIME ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  G_BounceMissile (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  G_Damage (TYPE_8__*,TYPE_8__*,TYPE_8__*,int*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ G_InvulnerabilityEffect (TYPE_8__*,int*,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ G_RadiusDamage (int*,TYPE_18__*,scalar_t__,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SetOrigin (TYPE_8__*,int*) ; 
 TYPE_8__* G_Spawn () ; 
 scalar_t__ LogAccuracyHit (TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  PMF_GRAPPLE_PULL ; 
 int /*<<< orphan*/  ProximityMine_Activate ; 
 int /*<<< orphan*/  ProximityMine_Die ; 
 int /*<<< orphan*/  ProximityMine_Player (TYPE_8__*,TYPE_8__*) ; 
 int SURF_METALSTEPS ; 
 int /*<<< orphan*/  SnapVectorTowards (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ TR_GRAVITY ; 
 scalar_t__ TR_STATIONARY ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 scalar_t__ VectorLength (int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorSet (double*,int,int,int) ; 
 scalar_t__ WP_PROX_LAUNCHER ; 
 int /*<<< orphan*/  Weapon_HookThink ; 
 TYPE_8__* g_entities ; 
 TYPE_10__ level ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_8__*) ; 
 int /*<<< orphan*/  vectoangles (int*,int*) ; 

void G_MissileImpact( gentity_t *ent, trace_t *trace ) {
	gentity_t		*other;
	qboolean		hitClient = qfalse;
#ifdef MISSIONPACK
	vec3_t			forward, impactpoint, bouncedir;
	int				eFlags;
#endif
	other = &g_entities[trace->entityNum];

	// check for bounce
	if ( !other->takedamage &&
		( ent->s.eFlags & ( EF_BOUNCE | EF_BOUNCE_HALF ) ) ) {
		G_BounceMissile( ent, trace );
		G_AddEvent( ent, EV_GRENADE_BOUNCE, 0 );
		return;
	}

#ifdef MISSIONPACK
	if ( other->takedamage ) {
		if ( ent->s.weapon != WP_PROX_LAUNCHER ) {
			if ( other->client && other->client->invulnerabilityTime > level.time ) {
				//
				VectorCopy( ent->s.pos.trDelta, forward );
				VectorNormalize( forward );
				if (G_InvulnerabilityEffect( other, forward, ent->s.pos.trBase, impactpoint, bouncedir )) {
					VectorCopy( bouncedir, trace->plane.normal );
					eFlags = ent->s.eFlags & EF_BOUNCE_HALF;
					ent->s.eFlags &= ~EF_BOUNCE_HALF;
					G_BounceMissile( ent, trace );
					ent->s.eFlags |= eFlags;
				}
				ent->target_ent = other;
				return;
			}
		}
	}
#endif
	// impact damage
	if (other->takedamage) {
		// FIXME: wrong damage direction?
		if ( ent->damage ) {
			vec3_t	velocity;

			if( LogAccuracyHit( other, &g_entities[ent->r.ownerNum] ) ) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
				hitClient = qtrue;
			}
			BG_EvaluateTrajectoryDelta( &ent->s.pos, level.time, velocity );
			if ( VectorLength( velocity ) == 0 ) {
				velocity[2] = 1;	// stepped on a grenade
			}
			G_Damage (other, ent, &g_entities[ent->r.ownerNum], velocity,
				ent->s.origin, ent->damage, 
				0, ent->methodOfDeath);
		}
	}

#ifdef MISSIONPACK
	if( ent->s.weapon == WP_PROX_LAUNCHER ) {
		if( ent->s.pos.trType != TR_GRAVITY ) {
			return;
		}

		// if it's a player, stick it on to them (flag them and remove this entity)
		if( other->s.eType == ET_PLAYER && other->health > 0 ) {
			ProximityMine_Player( ent, other );
			return;
		}

		SnapVectorTowards( trace->endpos, ent->s.pos.trBase );
		G_SetOrigin( ent, trace->endpos );
		ent->s.pos.trType = TR_STATIONARY;
		VectorClear( ent->s.pos.trDelta );

		G_AddEvent( ent, EV_PROXIMITY_MINE_STICK, trace->surfaceFlags );

		ent->think = ProximityMine_Activate;
		ent->nextthink = level.time + 2000;

		vectoangles( trace->plane.normal, ent->s.angles );
		ent->s.angles[0] += 90;

		// link the prox mine to the other entity
		ent->enemy = other;
		ent->die = ProximityMine_Die;
		VectorCopy(trace->plane.normal, ent->movedir);
		VectorSet(ent->r.mins, -4, -4, -4);
		VectorSet(ent->r.maxs, 4, 4, 4);
		trap_LinkEntity(ent);

		return;
	}
#endif

	if (!strcmp(ent->classname, "hook")) {
		gentity_t *nent;
		vec3_t v;

		nent = G_Spawn();
		if ( other->takedamage && other->client ) {

			G_AddEvent( nent, EV_MISSILE_HIT, DirToByte( trace->plane.normal ) );
			nent->s.otherEntityNum = other->s.number;

			ent->enemy = other;

			v[0] = other->r.currentOrigin[0] + (other->r.mins[0] + other->r.maxs[0]) * 0.5;
			v[1] = other->r.currentOrigin[1] + (other->r.mins[1] + other->r.maxs[1]) * 0.5;
			v[2] = other->r.currentOrigin[2] + (other->r.mins[2] + other->r.maxs[2]) * 0.5;

			SnapVectorTowards( v, ent->s.pos.trBase );	// save net bandwidth
		} else {
			VectorCopy(trace->endpos, v);
			G_AddEvent( nent, EV_MISSILE_MISS, DirToByte( trace->plane.normal ) );
			ent->enemy = NULL;
		}

		SnapVectorTowards( v, ent->s.pos.trBase );	// save net bandwidth

		nent->freeAfterEvent = qtrue;
		// change over to a normal entity right at the point of impact
		nent->s.eType = ET_GENERAL;
		ent->s.eType = ET_GRAPPLE;

		G_SetOrigin( ent, v );
		G_SetOrigin( nent, v );

		ent->think = Weapon_HookThink;
		ent->nextthink = level.time + FRAMETIME;

		ent->parent->client->ps.pm_flags |= PMF_GRAPPLE_PULL;
		VectorCopy( ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);

		trap_LinkEntity( ent );
		trap_LinkEntity( nent );

		return;
	}

	// is it cheaper in bandwidth to just remove this ent and create a new
	// one, rather than changing the missile into the explosion?

	if ( other->takedamage && other->client ) {
		G_AddEvent( ent, EV_MISSILE_HIT, DirToByte( trace->plane.normal ) );
		ent->s.otherEntityNum = other->s.number;
	} else if( trace->surfaceFlags & SURF_METALSTEPS ) {
		G_AddEvent( ent, EV_MISSILE_MISS_METAL, DirToByte( trace->plane.normal ) );
	} else {
		G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( trace->plane.normal ) );
	}

	ent->freeAfterEvent = qtrue;

	// change over to a normal entity right at the point of impact
	ent->s.eType = ET_GENERAL;

	SnapVectorTowards( trace->endpos, ent->s.pos.trBase );	// save net bandwidth

	G_SetOrigin( ent, trace->endpos );

	// splash damage (doesn't apply to person directly hit)
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( trace->endpos, ent->parent, ent->splashDamage, ent->splashRadius, 
			other, ent->splashMethodOfDeath ) ) {
			if( !hitClient ) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
			}
		}
	}

	trap_LinkEntity( ent );
}