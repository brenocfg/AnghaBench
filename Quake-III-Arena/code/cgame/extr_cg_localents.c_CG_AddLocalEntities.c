#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ endTime; int leType; struct TYPE_17__* prev; } ;
typedef  TYPE_1__ localEntity_t ;
struct TYPE_18__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_AddExplosion (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddFadeRGB (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddFallScaleFade (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddFragment (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddInvulnerabilityImpact (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddInvulnerabilityJuiced (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddKamikaze (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddMoveScaleFade (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddRefEntity (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddScaleFade (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddScorePlum (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_AddSpriteExplosion (TYPE_1__*) ; 
 int /*<<< orphan*/  CG_Error (char*,int) ; 
 int /*<<< orphan*/  CG_FreeLocalEntity (TYPE_1__*) ; 
#define  LE_EXPLOSION 140 
#define  LE_FADE_RGB 139 
#define  LE_FALL_SCALE_FADE 138 
#define  LE_FRAGMENT 137 
#define  LE_INVULIMPACT 136 
#define  LE_INVULJUICED 135 
#define  LE_KAMIKAZE 134 
#define  LE_MARK 133 
#define  LE_MOVE_SCALE_FADE 132 
#define  LE_SCALE_FADE 131 
#define  LE_SCOREPLUM 130 
#define  LE_SHOWREFENTITY 129 
#define  LE_SPRITE_EXPLOSION 128 
 TYPE_3__ cg ; 
 TYPE_1__ cg_activeLocalEntities ; 

void CG_AddLocalEntities( void ) {
	localEntity_t	*le, *next;

	// walk the list backwards, so any new local entities generated
	// (trails, marks, etc) will be present this frame
	le = cg_activeLocalEntities.prev;
	for ( ; le != &cg_activeLocalEntities ; le = next ) {
		// grab next now, so if the local entity is freed we
		// still have it
		next = le->prev;

		if ( cg.time >= le->endTime ) {
			CG_FreeLocalEntity( le );
			continue;
		}
		switch ( le->leType ) {
		default:
			CG_Error( "Bad leType: %i", le->leType );
			break;

		case LE_MARK:
			break;

		case LE_SPRITE_EXPLOSION:
			CG_AddSpriteExplosion( le );
			break;

		case LE_EXPLOSION:
			CG_AddExplosion( le );
			break;

		case LE_FRAGMENT:			// gibs and brass
			CG_AddFragment( le );
			break;

		case LE_MOVE_SCALE_FADE:		// water bubbles
			CG_AddMoveScaleFade( le );
			break;

		case LE_FADE_RGB:				// teleporters, railtrails
			CG_AddFadeRGB( le );
			break;

		case LE_FALL_SCALE_FADE: // gib blood trails
			CG_AddFallScaleFade( le );
			break;

		case LE_SCALE_FADE:		// rocket trails
			CG_AddScaleFade( le );
			break;

		case LE_SCOREPLUM:
			CG_AddScorePlum( le );
			break;

#ifdef MISSIONPACK
		case LE_KAMIKAZE:
			CG_AddKamikaze( le );
			break;
		case LE_INVULIMPACT:
			CG_AddInvulnerabilityImpact( le );
			break;
		case LE_INVULJUICED:
			CG_AddInvulnerabilityJuiced( le );
			break;
		case LE_SHOWREFENTITY:
			CG_AddRefEntity( le );
			break;
#endif
		}
	}
}