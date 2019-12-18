#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ clientNum; int /*<<< orphan*/  message; int /*<<< orphan*/  voiceOnly; int /*<<< orphan*/  cmd; int /*<<< orphan*/  snd; } ;
typedef  TYPE_3__ bufferedVoiceChat_t ;
struct TYPE_17__ {size_t voiceChatBufferOut; scalar_t__ time; TYPE_2__* snap; scalar_t__ intermissionStarted; } ;
struct TYPE_16__ {int /*<<< orphan*/  integer; } ;
struct TYPE_15__ {int /*<<< orphan*/  integer; } ;
struct TYPE_14__ {int acceptTask; scalar_t__ acceptLeader; int /*<<< orphan*/  acceptVoice; scalar_t__ acceptOrderTime; } ;
struct TYPE_13__ {scalar_t__ snd; } ;
struct TYPE_10__ {scalar_t__ clientNum; } ;
struct TYPE_11__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_AddToTeamChat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_ShowResponseHead () ; 
 int CG_ValidOrder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAN_VOICE ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_8__ cg ; 
 TYPE_7__ cg_noVoiceChats ; 
 TYPE_6__ cg_noVoiceText ; 
 TYPE_5__ cgs ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* voiceChatBuffer ; 

void CG_PlayVoiceChat( bufferedVoiceChat_t *vchat ) {
#ifdef MISSIONPACK
	// if we are going into the intermission, don't start any voices
	if ( cg.intermissionStarted ) {
		return;
	}

	if ( !cg_noVoiceChats.integer ) {
		trap_S_StartLocalSound( vchat->snd, CHAN_VOICE);
		if (vchat->clientNum != cg.snap->ps.clientNum) {
			int orderTask = CG_ValidOrder(vchat->cmd);
			if (orderTask > 0) {
				cgs.acceptOrderTime = cg.time + 5000;
				Q_strncpyz(cgs.acceptVoice, vchat->cmd, sizeof(cgs.acceptVoice));
				cgs.acceptTask = orderTask;
				cgs.acceptLeader = vchat->clientNum;
			}
			// see if this was an order
			CG_ShowResponseHead();
		}
	}
	if (!vchat->voiceOnly && !cg_noVoiceText.integer) {
		CG_AddToTeamChat( vchat->message );
		CG_Printf( "%s\n", vchat->message );
	}
	voiceChatBuffer[cg.voiceChatBufferOut].snd = 0;
#endif
}