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
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ stereoFrame_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_20__ {scalar_t__ integer; } ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_18__ {scalar_t__ value; } ;
struct TYPE_17__ {scalar_t__ value; } ;
struct TYPE_16__ {float value; } ;
struct TYPE_15__ {int time; int /*<<< orphan*/  viewaxis; int /*<<< orphan*/  vieworg; int /*<<< orphan*/  areamask; } ;
struct TYPE_13__ {scalar_t__* stats; int /*<<< orphan*/  clientNum; } ;
struct TYPE_14__ {int snapFlags; TYPE_2__ ps; int /*<<< orphan*/  areamask; } ;
struct TYPE_12__ {scalar_t__ hModel; } ;
struct TYPE_11__ {int time; scalar_t__* infoScreenText; int renderingThirdPerson; scalar_t__ frametime; scalar_t__ oldTime; int /*<<< orphan*/  clientFrame; TYPE_4__ refdef; TYPE_3__* snap; TYPE_1__ testModelEntity; int /*<<< orphan*/  predictedPlayerState; int /*<<< orphan*/  hyperspace; int /*<<< orphan*/  zoomSensitivity; int /*<<< orphan*/  weaponSelect; int /*<<< orphan*/  demoPlayback; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_AddLagometerFrameInfo () ; 
 int /*<<< orphan*/  CG_AddLocalEntities () ; 
 int /*<<< orphan*/  CG_AddMarks () ; 
 int /*<<< orphan*/  CG_AddPacketEntities () ; 
 int /*<<< orphan*/  CG_AddParticles () ; 
 int /*<<< orphan*/  CG_AddTestModel () ; 
 int /*<<< orphan*/  CG_AddViewWeapon (int /*<<< orphan*/ *) ; 
 int CG_CalcViewValues () ; 
 int /*<<< orphan*/  CG_DamageBlendBlob () ; 
 int /*<<< orphan*/  CG_DrawActive (scalar_t__) ; 
 int /*<<< orphan*/  CG_DrawInformation () ; 
 int /*<<< orphan*/  CG_PlayBufferedSounds () ; 
 int /*<<< orphan*/  CG_PlayBufferedVoiceChats () ; 
 int /*<<< orphan*/  CG_PowerupTimerSounds () ; 
 int /*<<< orphan*/  CG_PredictPlayerState () ; 
 int /*<<< orphan*/  CG_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_ProcessSnapshots () ; 
 int /*<<< orphan*/  CG_UpdateCvars () ; 
 int SNAPFLAG_NOT_ACTIVE ; 
 size_t STAT_HEALTH ; 
 scalar_t__ STEREO_RIGHT ; 
 TYPE_10__ cg ; 
 TYPE_9__ cg_stats ; 
 TYPE_8__ cg_thirdPerson ; 
 TYPE_7__ cg_timescale ; 
 TYPE_6__ cg_timescaleFadeEnd ; 
 TYPE_5__ cg_timescaleFadeSpeed ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_R_ClearScene () ; 
 int /*<<< orphan*/  trap_S_ClearLoopingSounds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_S_Respatialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_SetUserCmdValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,scalar_t__) ; 

void CG_DrawActiveFrame( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback ) {
	int		inwater;

	cg.time = serverTime;
	cg.demoPlayback = demoPlayback;

	// update cvars
	CG_UpdateCvars();

	// if we are only updating the screen as a loading
	// pacifier, don't even try to read snapshots
	if ( cg.infoScreenText[0] != 0 ) {
		CG_DrawInformation();
		return;
	}

	// any looped sounds will be respecified as entities
	// are added to the render list
	trap_S_ClearLoopingSounds(qfalse);

	// clear all the render lists
	trap_R_ClearScene();

	// set up cg.snap and possibly cg.nextSnap
	CG_ProcessSnapshots();

	// if we haven't received any snapshots yet, all
	// we can draw is the information screen
	if ( !cg.snap || ( cg.snap->snapFlags & SNAPFLAG_NOT_ACTIVE ) ) {
		CG_DrawInformation();
		return;
	}

	// let the client system know what our weapon and zoom settings are
	trap_SetUserCmdValue( cg.weaponSelect, cg.zoomSensitivity );

	// this counter will be bumped for every valid scene we generate
	cg.clientFrame++;

	// update cg.predictedPlayerState
	CG_PredictPlayerState();

	// decide on third person view
	cg.renderingThirdPerson = cg_thirdPerson.integer || (cg.snap->ps.stats[STAT_HEALTH] <= 0);

	// build cg.refdef
	inwater = CG_CalcViewValues();

	// first person blend blobs, done after AnglesToAxis
	if ( !cg.renderingThirdPerson ) {
		CG_DamageBlendBlob();
	}

	// build the render lists
	if ( !cg.hyperspace ) {
		CG_AddPacketEntities();			// adter calcViewValues, so predicted player state is correct
		CG_AddMarks();
		CG_AddParticles ();
		CG_AddLocalEntities();
	}
	CG_AddViewWeapon( &cg.predictedPlayerState );

	// add buffered sounds
	CG_PlayBufferedSounds();

	// play buffered voice chats
	CG_PlayBufferedVoiceChats();

	// finish up the rest of the refdef
	if ( cg.testModelEntity.hModel ) {
		CG_AddTestModel();
	}
	cg.refdef.time = cg.time;
	memcpy( cg.refdef.areamask, cg.snap->areamask, sizeof( cg.refdef.areamask ) );

	// warning sounds when powerup is wearing off
	CG_PowerupTimerSounds();

	// update audio positions
	trap_S_Respatialize( cg.snap->ps.clientNum, cg.refdef.vieworg, cg.refdef.viewaxis, inwater );

	// make sure the lagometerSample and frame timing isn't done twice when in stereo
	if ( stereoView != STEREO_RIGHT ) {
		cg.frametime = cg.time - cg.oldTime;
		if ( cg.frametime < 0 ) {
			cg.frametime = 0;
		}
		cg.oldTime = cg.time;
		CG_AddLagometerFrameInfo();
	}
	if (cg_timescale.value != cg_timescaleFadeEnd.value) {
		if (cg_timescale.value < cg_timescaleFadeEnd.value) {
			cg_timescale.value += cg_timescaleFadeSpeed.value * ((float)cg.frametime) / 1000;
			if (cg_timescale.value > cg_timescaleFadeEnd.value)
				cg_timescale.value = cg_timescaleFadeEnd.value;
		}
		else {
			cg_timescale.value -= cg_timescaleFadeSpeed.value * ((float)cg.frametime) / 1000;
			if (cg_timescale.value < cg_timescaleFadeEnd.value)
				cg_timescale.value = cg_timescaleFadeEnd.value;
		}
		if (cg_timescaleFadeSpeed.value) {
			trap_Cvar_Set("timescale", va("%f", cg_timescale.value));
		}
	}

	// actually issue the rendering calls
	CG_DrawActive( stereoView );

	if ( cg_stats.integer ) {
		CG_Printf( "cg.clientFrame:%i\n", cg.clientFrame );
	}


}