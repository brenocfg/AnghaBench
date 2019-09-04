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
typedef  int /*<<< orphan*/  CAPTUREPARMS ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVStreamMaster ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dstruct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwAudioBufferSize ; 
 int /*<<< orphan*/  dwIndexSize ; 
 int /*<<< orphan*/  dwMCIStartTime ; 
 int /*<<< orphan*/  dwMCIStopTime ; 
 int /*<<< orphan*/  dwRequestMicroSecPerFrame ; 
 int /*<<< orphan*/  fAbortLeftMouse ; 
 int /*<<< orphan*/  fAbortRightMouse ; 
 int /*<<< orphan*/  fCaptureAudio ; 
 int /*<<< orphan*/  fDisableWriteCache ; 
 int /*<<< orphan*/  fLimitEnabled ; 
 int /*<<< orphan*/  fMCIControl ; 
 int /*<<< orphan*/  fMakeUserHitOKToCapture ; 
 int /*<<< orphan*/  fStepCaptureAt2x ; 
 int /*<<< orphan*/  fStepMCIDevice ; 
 int /*<<< orphan*/  fUsingDOSMemory ; 
 int /*<<< orphan*/  fYield ; 
 int /*<<< orphan*/  vKeyAbort ; 
 int /*<<< orphan*/  wChunkGranularity ; 
 int /*<<< orphan*/  wNumAudioRequested ; 
 int /*<<< orphan*/  wNumVideoRequested ; 
 int /*<<< orphan*/  wPercentDropForError ; 
 int /*<<< orphan*/  wStepCaptureAverageFrames ; 
 int /*<<< orphan*/  wTimeLimit ; 

__attribute__((used)) static void dump_captureparms(AVFormatContext *s, CAPTUREPARMS *cparms)
{
    av_log(s, AV_LOG_DEBUG, "CAPTUREPARMS\n");
    dstruct(s, cparms, dwRequestMicroSecPerFrame, "lu");
    dstruct(s, cparms, fMakeUserHitOKToCapture, "d");
    dstruct(s, cparms, wPercentDropForError, "u");
    dstruct(s, cparms, fYield, "d");
    dstruct(s, cparms, dwIndexSize, "lu");
    dstruct(s, cparms, wChunkGranularity, "u");
    dstruct(s, cparms, fUsingDOSMemory, "d");
    dstruct(s, cparms, wNumVideoRequested, "u");
    dstruct(s, cparms, fCaptureAudio, "d");
    dstruct(s, cparms, wNumAudioRequested, "u");
    dstruct(s, cparms, vKeyAbort, "u");
    dstruct(s, cparms, fAbortLeftMouse, "d");
    dstruct(s, cparms, fAbortRightMouse, "d");
    dstruct(s, cparms, fLimitEnabled, "d");
    dstruct(s, cparms, wTimeLimit, "u");
    dstruct(s, cparms, fMCIControl, "d");
    dstruct(s, cparms, fStepMCIDevice, "d");
    dstruct(s, cparms, dwMCIStartTime, "lu");
    dstruct(s, cparms, dwMCIStopTime, "lu");
    dstruct(s, cparms, fStepCaptureAt2x, "d");
    dstruct(s, cparms, wStepCaptureAverageFrames, "u");
    dstruct(s, cparms, dwAudioBufferSize, "lu");
    dstruct(s, cparms, fDisableWriteCache, "d");
    dstruct(s, cparms, AVStreamMaster, "u");
}