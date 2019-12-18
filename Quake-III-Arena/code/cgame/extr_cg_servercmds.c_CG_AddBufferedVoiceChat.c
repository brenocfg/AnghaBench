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
typedef  int /*<<< orphan*/  bufferedVoiceChat_t ;
struct TYPE_2__ {size_t voiceChatBufferIn; int voiceChatBufferOut; scalar_t__ intermissionStarted; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_PlayVoiceChat (int /*<<< orphan*/ *) ; 
 int MAX_VOICECHATBUFFER ; 
 TYPE_1__ cg ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * voiceChatBuffer ; 

void CG_AddBufferedVoiceChat( bufferedVoiceChat_t *vchat ) {
#ifdef MISSIONPACK
	// if we are going into the intermission, don't start any voices
	if ( cg.intermissionStarted ) {
		return;
	}

	memcpy(&voiceChatBuffer[cg.voiceChatBufferIn], vchat, sizeof(bufferedVoiceChat_t));
	cg.voiceChatBufferIn = (cg.voiceChatBufferIn + 1) % MAX_VOICECHATBUFFER;
	if (cg.voiceChatBufferIn == cg.voiceChatBufferOut) {
		CG_PlayVoiceChat( &voiceChatBuffer[cg.voiceChatBufferOut] );
		cg.voiceChatBufferOut++;
	}
#endif
}