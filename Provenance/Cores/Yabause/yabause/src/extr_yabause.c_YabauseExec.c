#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ FrameAdvanceVariable ; 
 int LagFrameFlag ; 
 scalar_t__ NeedAdvance ; 
 scalar_t__ Paused ; 
 scalar_t__ RunNormal ; 
 int /*<<< orphan*/  SCSP_MUTE_SYSTEM ; 
 int /*<<< orphan*/  ScspMuteAudio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScspUnMuteAudio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YabauseEmulate () ; 

int YabauseExec(void) {

	//automatically advance lag frames, this should be optional later
	if (FrameAdvanceVariable > 0 && LagFrameFlag == 1){
		FrameAdvanceVariable = NeedAdvance; //advance a frame
		YabauseEmulate();
		FrameAdvanceVariable = Paused; //pause next time
		return(0);
	}

	if (FrameAdvanceVariable == Paused){
		ScspMuteAudio(SCSP_MUTE_SYSTEM);
		return(0);
	}

	if (FrameAdvanceVariable == NeedAdvance){  //advance a frame
		FrameAdvanceVariable = Paused; //pause next time
		ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
		YabauseEmulate();
	}

	if (FrameAdvanceVariable == RunNormal ) { //run normally
		ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
		YabauseEmulate();
	}
	return 0;
}