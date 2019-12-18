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
 scalar_t__ Paused ; 
 scalar_t__ RunNormal ; 
 int /*<<< orphan*/  SCSP_MUTE_SYSTEM ; 
 int /*<<< orphan*/  ScspMuteAudio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScspUnMuteAudio (int /*<<< orphan*/ ) ; 

void PauseOrUnpause(void) {

	if(FrameAdvanceVariable == RunNormal) {
		FrameAdvanceVariable=Paused;
		ScspMuteAudio(SCSP_MUTE_SYSTEM);
	}
	else {
		FrameAdvanceVariable=RunNormal;	
		ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
	}
}