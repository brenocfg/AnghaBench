#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  callback ;
struct TYPE_3__ {int /*<<< orphan*/ * inputProcRefCon; int /*<<< orphan*/ * inputProc; } ;
typedef  scalar_t__ OSStatus ;
typedef  TYPE_1__ AURenderCallbackStruct ;

/* Variables and functions */
 scalar_t__ AudioOutputUnitStop (int /*<<< orphan*/ ) ; 
 scalar_t__ AudioUnitSetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ AudioUnitUninitialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseComponent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kAudioUnitProperty_SetRenderCallback ; 
 int /*<<< orphan*/  kAudioUnitScope_Input ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  outputAU ; 

__attribute__((used)) static void SNDMacDeInit(void) {
    OSStatus error;
    AURenderCallbackStruct callback;

    /* Stop the Audio Unit from playing any further */
    error = AudioOutputUnitStop(outputAU);

    if(error != noErr)
        return;

    /* Clear the callback */
    callback.inputProc = NULL;
    callback.inputProcRefCon = NULL;

    error = AudioUnitSetProperty(outputAU, kAudioUnitProperty_SetRenderCallback,
                                 kAudioUnitScope_Input, 0, &callback,
                                 sizeof(callback));

    if(error != noErr)
        return;

    /* Uninitialize the Audio Unit, now that we're done with it */
    error = AudioUnitUninitialize(outputAU);

    if(error != noErr)
        return;

    /* Close it, we're done */
    CloseComponent(outputAU);
}