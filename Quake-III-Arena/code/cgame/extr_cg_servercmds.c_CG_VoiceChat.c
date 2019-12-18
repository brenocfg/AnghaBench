#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* qboolean ;
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 char* CG_Argv (int) ; 
 int /*<<< orphan*/  CG_VoiceChatLocal (int,void*,int,int,char const*) ; 
 int /*<<< orphan*/  VOICECHAT_DEATHINSULT ; 
 int /*<<< orphan*/  VOICECHAT_KILLGAUNTLET ; 
 int /*<<< orphan*/  VOICECHAT_KILLINSULT ; 
 int /*<<< orphan*/  VOICECHAT_PRAISE ; 
 int /*<<< orphan*/  VOICECHAT_TAUNT ; 
 void* atoi (char*) ; 
 TYPE_1__ cg_noTaunt ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

void CG_VoiceChat( int mode ) {
#ifdef MISSIONPACK
	const char *cmd;
	int clientNum, color;
	qboolean voiceOnly;

	voiceOnly = atoi(CG_Argv(1));
	clientNum = atoi(CG_Argv(2));
	color = atoi(CG_Argv(3));
	cmd = CG_Argv(4);

	if (cg_noTaunt.integer != 0) {
		if (!strcmp(cmd, VOICECHAT_KILLINSULT)  || !strcmp(cmd, VOICECHAT_TAUNT) || \
			!strcmp(cmd, VOICECHAT_DEATHINSULT) || !strcmp(cmd, VOICECHAT_KILLGAUNTLET) || \
			!strcmp(cmd, VOICECHAT_PRAISE)) {
			return;
		}
	}

	CG_VoiceChatLocal( mode, voiceOnly, clientNum, color, cmd );
#endif
}