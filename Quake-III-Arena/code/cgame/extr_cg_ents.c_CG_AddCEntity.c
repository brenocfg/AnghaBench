#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int eType; } ;
struct TYPE_17__ {TYPE_1__ currentState; } ;
typedef  TYPE_2__ centity_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Beam (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_CalcEntityLerpPositions (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_EntityEffects (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_Error (char*,int) ; 
 int /*<<< orphan*/  CG_General (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_Grapple (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_Item (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_Missile (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_Mover (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_Player (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_Portal (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_Speaker (TYPE_2__*) ; 
 int /*<<< orphan*/  CG_TeamBase (TYPE_2__*) ; 
#define  ET_BEAM 140 
 int ET_EVENTS ; 
#define  ET_GENERAL 139 
#define  ET_GRAPPLE 138 
#define  ET_INVISIBLE 137 
#define  ET_ITEM 136 
#define  ET_MISSILE 135 
#define  ET_MOVER 134 
#define  ET_PLAYER 133 
#define  ET_PORTAL 132 
#define  ET_PUSH_TRIGGER 131 
#define  ET_SPEAKER 130 
#define  ET_TEAM 129 
#define  ET_TELEPORT_TRIGGER 128 

__attribute__((used)) static void CG_AddCEntity( centity_t *cent ) {
	// event-only entities will have been dealt with already
	if ( cent->currentState.eType >= ET_EVENTS ) {
		return;
	}

	// calculate the current origin
	CG_CalcEntityLerpPositions( cent );

	// add automatic effects
	CG_EntityEffects( cent );

	switch ( cent->currentState.eType ) {
	default:
		CG_Error( "Bad entity type: %i\n", cent->currentState.eType );
		break;
	case ET_INVISIBLE:
	case ET_PUSH_TRIGGER:
	case ET_TELEPORT_TRIGGER:
		break;
	case ET_GENERAL:
		CG_General( cent );
		break;
	case ET_PLAYER:
		CG_Player( cent );
		break;
	case ET_ITEM:
		CG_Item( cent );
		break;
	case ET_MISSILE:
		CG_Missile( cent );
		break;
	case ET_MOVER:
		CG_Mover( cent );
		break;
	case ET_BEAM:
		CG_Beam( cent );
		break;
	case ET_PORTAL:
		CG_Portal( cent );
		break;
	case ET_SPEAKER:
		CG_Speaker( cent );
		break;
	case ET_GRAPPLE:
		CG_Grapple( cent );
		break;
	case ET_TEAM:
		CG_TeamBase( cent );
		break;
	}
}