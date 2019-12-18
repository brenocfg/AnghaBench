#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int eFlags; size_t clientNum; } ;
struct TYPE_17__ {TYPE_2__ currentState; } ;
typedef  TYPE_6__ centity_t ;
struct TYPE_20__ {TYPE_4__* snap; } ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_16__ {int /*<<< orphan*/  friendShader; int /*<<< orphan*/  medalCapture; int /*<<< orphan*/  medalAssist; int /*<<< orphan*/  medalDefend; int /*<<< orphan*/  medalGauntlet; int /*<<< orphan*/  medalExcellent; int /*<<< orphan*/  medalImpressive; int /*<<< orphan*/  balloonShader; int /*<<< orphan*/  connectionShader; } ;
struct TYPE_18__ {scalar_t__ gametype; TYPE_5__ media; TYPE_1__* clientinfo; } ;
struct TYPE_14__ {int* persistant; } ;
struct TYPE_15__ {TYPE_3__ ps; } ;
struct TYPE_12__ {int team; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_PlayerFloatSprite (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int EF_AWARD_ASSIST ; 
 int EF_AWARD_CAP ; 
 int EF_AWARD_DEFEND ; 
 int EF_AWARD_EXCELLENT ; 
 int EF_AWARD_GAUNTLET ; 
 int EF_AWARD_IMPRESSIVE ; 
 int EF_CONNECTION ; 
 int EF_DEAD ; 
 int EF_TALK ; 
 scalar_t__ GT_TEAM ; 
 size_t PERS_TEAM ; 
 TYPE_9__ cg ; 
 TYPE_8__ cg_drawFriend ; 
 TYPE_7__ cgs ; 

__attribute__((used)) static void CG_PlayerSprites( centity_t *cent ) {
	int		team;

	if ( cent->currentState.eFlags & EF_CONNECTION ) {
		CG_PlayerFloatSprite( cent, cgs.media.connectionShader );
		return;
	}

	if ( cent->currentState.eFlags & EF_TALK ) {
		CG_PlayerFloatSprite( cent, cgs.media.balloonShader );
		return;
	}

	if ( cent->currentState.eFlags & EF_AWARD_IMPRESSIVE ) {
		CG_PlayerFloatSprite( cent, cgs.media.medalImpressive );
		return;
	}

	if ( cent->currentState.eFlags & EF_AWARD_EXCELLENT ) {
		CG_PlayerFloatSprite( cent, cgs.media.medalExcellent );
		return;
	}

	if ( cent->currentState.eFlags & EF_AWARD_GAUNTLET ) {
		CG_PlayerFloatSprite( cent, cgs.media.medalGauntlet );
		return;
	}

	if ( cent->currentState.eFlags & EF_AWARD_DEFEND ) {
		CG_PlayerFloatSprite( cent, cgs.media.medalDefend );
		return;
	}

	if ( cent->currentState.eFlags & EF_AWARD_ASSIST ) {
		CG_PlayerFloatSprite( cent, cgs.media.medalAssist );
		return;
	}

	if ( cent->currentState.eFlags & EF_AWARD_CAP ) {
		CG_PlayerFloatSprite( cent, cgs.media.medalCapture );
		return;
	}

	team = cgs.clientinfo[ cent->currentState.clientNum ].team;
	if ( !(cent->currentState.eFlags & EF_DEAD) && 
		cg.snap->ps.persistant[PERS_TEAM] == team &&
		cgs.gametype >= GT_TEAM) {
		if (cg_drawFriend.integer) {
			CG_PlayerFloatSprite( cent, cgs.media.friendShader );
		}
		return;
	}
}