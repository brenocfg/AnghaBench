#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double x; double y; double z; } ;
struct TYPE_7__ {TYPE_1__ offset; int /*<<< orphan*/  renderHeight; int /*<<< orphan*/  renderWidth; } ;
typedef  TYPE_2__ VREyeParameters ;
typedef  int VRDisplayHandle ;
struct TYPE_8__ {int hasPosition; int hasExternalDisplay; int canPresent; int /*<<< orphan*/  maxLayers; } ;
typedef  TYPE_3__ VRDisplayCapabilities ;

/* Variables and functions */
 int /*<<< orphan*/  VREyeLeft ; 
 int /*<<< orphan*/  VREyeRight ; 
 int emscripten_vr_count_displays () ; 
 int /*<<< orphan*/  emscripten_vr_display_connected (int) ; 
 int /*<<< orphan*/  emscripten_vr_get_display_capabilities (int,TYPE_3__*) ; 
 int emscripten_vr_get_display_handle (int) ; 
 char* emscripten_vr_get_display_name (int) ; 
 int /*<<< orphan*/  emscripten_vr_get_eye_parameters (int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  emscripten_vr_ready () ; 
 int /*<<< orphan*/  emscripten_vr_set_display_render_loop (int,int /*<<< orphan*/ ) ; 
 int gDisplay ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  renderLoop ; 
 scalar_t__ renderLoopArgArg ; 
 int /*<<< orphan*/  renderLoopArgCalled ; 
 int renderLoopCalled ; 
 int /*<<< orphan*/  report_result (int) ; 

__attribute__((used)) static void mainloop() {
    static int loopcount = 0;

    if (!emscripten_vr_ready()) {
        printf("VR not ready\n");
        return;
    }

    if(gDisplay == -1) {
        int numDisplays = emscripten_vr_count_displays();
        if (numDisplays == 0) {
            printf("No VR displays found!\n");
            report_result(0);
            return;
        }

        printf("%d VR displays found\n", numDisplays);

        int id = -1;
        char *devName;
        for (int i = 0; i < numDisplays; ++i) {
            VRDisplayHandle handle = emscripten_vr_get_display_handle(i);
            if (gDisplay == -1) {
                /* Save first found display for more testing */
                gDisplay = handle;
                devName = emscripten_vr_get_display_name(handle);
                printf("Using VRDisplay '%s' (displayId '%d')\n", devName, gDisplay);

                VRDisplayCapabilities caps;
                if(!emscripten_vr_get_display_capabilities(handle, &caps)) {
                    printf("Error: failed to get display capabilities.\n");
                    report_result(1);
                    return;
                }
                if(!emscripten_vr_display_connected(gDisplay)) {
                    printf("Error: expected display to be connected.\n");
                    report_result(1);
                    return;
                }
                printf("Display Capabilities:\n"
                       "{hasPosition: %d, hasExternalDisplay: %d, canPresent: %d, maxLayers: %lu}\n",
                       caps.hasPosition, caps.hasExternalDisplay, caps.canPresent, caps.maxLayers);
            }
        }

        if (gDisplay == -1) {
            printf("Couln't find a VR display even though at least one was found.\n");
            report_result(1);
            return;
        }

        VREyeParameters leftParams, rightParams;
        emscripten_vr_get_eye_parameters(gDisplay, VREyeLeft, &leftParams);
        emscripten_vr_get_eye_parameters(gDisplay, VREyeRight, &rightParams);

        VREyeParameters* p = &leftParams;
        printf("Left eye params: {offset: [%f, %f, %f], renderWidth: %lu, renderHeight: %lu}\n", p->offset.x, p->offset.y, p->offset.z, p->renderWidth, p->renderHeight);

        p = &rightParams;
        printf("Right eye params: {offset: [%f, %f, %f], renderWidth: %lu, renderHeight: %lu}\n", p->offset.x, p->offset.y, p->offset.z, p->renderWidth, p->renderHeight);

        if (!emscripten_vr_set_display_render_loop(gDisplay, renderLoop)) {
            printf("Error: Failed to dereference handle while settings display render loop of device %d\n", gDisplay);
            report_result(1);
        }
    }

    if (loopcount++ > 10) {
        if (renderLoopCalled != 2) {
            printf("Render loop was not called twice (expected 2, was %d)\n", renderLoopCalled);
            report_result(1);
        }
        if (!renderLoopArgCalled) {
            printf("Render loop with argument was never called\n");
            report_result(1);
        }
        if ((int)renderLoopArgArg != 42) {
            printf("Argument to emscripten_vr_set_display_render_loop_arg was not passed on correctly\n");
            report_result(1);
        }
        report_result(0);
    }
}