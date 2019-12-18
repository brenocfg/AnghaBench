#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voiceChatList_t ;
typedef  int /*<<< orphan*/  sfxHandle_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ clientInfo_t ;
struct TYPE_8__ {int clientNum; int /*<<< orphan*/  message; int /*<<< orphan*/  cmd; int /*<<< orphan*/  voiceOnly; int /*<<< orphan*/  snd; } ;
typedef  TYPE_2__ bufferedVoiceChat_t ;
struct TYPE_11__ {scalar_t__ intermissionStarted; } ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;
struct TYPE_9__ {int currentVoiceClient; TYPE_1__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_AddBufferedVoiceChat (TYPE_2__*) ; 
 scalar_t__ CG_GetVoiceChat (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * CG_VoiceChatListForClient (int) ; 
 int /*<<< orphan*/  Com_sprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  Q_COLOR_ESCAPE ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char const*,int) ; 
 int SAY_TEAM ; 
 int SAY_TELL ; 
 TYPE_5__ cg ; 
 TYPE_4__ cg_teamChatsOnly ; 
 TYPE_3__ cgs ; 

void CG_VoiceChatLocal( int mode, qboolean voiceOnly, int clientNum, int color, const char *cmd ) {
#ifdef MISSIONPACK
	char *chat;
	voiceChatList_t *voiceChatList;
	clientInfo_t *ci;
	sfxHandle_t snd;
	bufferedVoiceChat_t vchat;

	// if we are going into the intermission, don't start any voices
	if ( cg.intermissionStarted ) {
		return;
	}

	if ( clientNum < 0 || clientNum >= MAX_CLIENTS ) {
		clientNum = 0;
	}
	ci = &cgs.clientinfo[ clientNum ];

	cgs.currentVoiceClient = clientNum;

	voiceChatList = CG_VoiceChatListForClient( clientNum );

	if ( CG_GetVoiceChat( voiceChatList, cmd, &snd, &chat ) ) {
		//
		if ( mode == SAY_TEAM || !cg_teamChatsOnly.integer ) {
			vchat.clientNum = clientNum;
			vchat.snd = snd;
			vchat.voiceOnly = voiceOnly;
			Q_strncpyz(vchat.cmd, cmd, sizeof(vchat.cmd));
			if ( mode == SAY_TELL ) {
				Com_sprintf(vchat.message, sizeof(vchat.message), "[%s]: %c%c%s", ci->name, Q_COLOR_ESCAPE, color, chat);
			}
			else if ( mode == SAY_TEAM ) {
				Com_sprintf(vchat.message, sizeof(vchat.message), "(%s): %c%c%s", ci->name, Q_COLOR_ESCAPE, color, chat);
			}
			else {
				Com_sprintf(vchat.message, sizeof(vchat.message), "%s: %c%c%s", ci->name, Q_COLOR_ESCAPE, color, chat);
			}
			CG_AddBufferedVoiceChat(&vchat);
		}
	}
#endif
}